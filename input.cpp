#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include"User.h"
#include"Tutor.h"
#include"Student.h"
#include"input.h"
using namespace std;

int last_ID = 0;

void inputUser(string filename, vector<User> &a){
    ifstream f;
    f.open(filename);
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            int id, age;
            bool c, m;
            string n, u, p,t,f, l;
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string

            char* items = strtok(strToSplit, ",");
            int count = 0;

            while (items != nullptr) {
                if (count == 0) {
                    id = stoi(items);
                    last_ID = id;
                } else if (count == 1) {
                    n = items;
                } else if (count == 2) {
                    age = atoi(items);
                } else if (count == 3) {
                    u = items; // Convert C-style string to int
                }
                else if (count == 4){
                    p = items;
                }
                else if (count == 5){
                    l = items;
                }
                else if (count == 6){
                    c = items;
                }
                else if (count ==7){
                    m = items;
                }
                else if (count ==8){
                    t = items;
                }
                else {
                    f = items;
                }
                items = strtok(nullptr, ",");                         
                count++;
            }
            // Create a new User object and add it to the library
            a.push_back(User(id, n, age, u, p, l, c, m, t, f));
            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }
                                    
                        
}

void inputStudentTutor(string filename, vector<vector<int>> &a){
    ifstream f;
    f.open(filename);
    if(f.is_open()){
        string line;
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string

            char* items = strtok(strToSplit, ",");
            vector<int> b;
            while (items != nullptr) {
                b.push_back(stoi(items));
                items = strtok(nullptr, ",");                         
            }
            a.push_back(b);
            free(strToSplit); // Free the dynamically allocated memory
        }
        f.close(); // Close the file
        }
    else {
        cout << "Failed to open the file." << endl;
    }
}

int save_user(User a) {
    ofstream userFile("users.csv", ios::app); 
    if (userFile.is_open()) {
        userFile << ++last_ID << "," << a.get_full_name() << "," << a.get_age() << "," << a.get_username() << "," << a.get_password()
                    << "," << a.get_level() << "," << a.get_camera() << "," << a.get_microphone() << ","  << a.get_twitter() << "," << a.get_facebook() << endl;
        userFile.close();
        return last_ID;
    } else {
        cerr << "Error opening users.csv for writing." << endl;
        return 0;
    }
}

void inputSubject(string filename, vector<string> &a){
    ifstream f;
    f.open(filename);
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string

            char* items = strtok(strToSplit, ",");
            items = strtok(nullptr, ",");                         
            a.push_back(items);
            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }                      
}

void save_student(Student a){
    ofstream studentFile("students.csv", ios::app); 
    if (studentFile.is_open()) {
        studentFile << a.get_ID() << "," << a.get_tutor() << "," << a.get_subject();
        studentFile.close();
        return;
    } else {
        cerr << "Error opening students.csv for writing." << endl;
        return;
    }
}

void inputStudyGroup(string filename, vector<pair<string,int>> &a)
{
    ifstream f;
    f.open(filename);
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string
            int i;
            string n;
            char* items = strtok(strToSplit, ",");
            n = items;
            items = strtok(nullptr, ",");                         
            i = stoi(items);
            // Create a new User object and add it to the library
            a.push_back(make_pair(n,i));

            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }                      
}

void inputQuestion(string filename, vector<qa> &a){
    ifstream f;
    f.open(filename);
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string
            char* items = strtok(strToSplit, ","); 
            qa newQuestion;
            newQuestion.quest_id = stoi(items);
            items = strtok(nullptr, ",");
            newQuestion.sub_id = stoi(items);
            items = strtok(nullptr, ",");
            newQuestion.question = items;
            a.push_back(newQuestion);
            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }                      
}

void save_question(int id, int sub, string q){
    ofstream questionFile("qa.csv", ios::app); 
    if (questionFile.is_open()) {
        questionFile << id << "," << sub << "," << q << endl;
        questionFile.close();
        return;
    } else {
        cerr << "Error opening questions.csv for writing." << endl;
        return;
    }
}


void save_tutor(int id, int sub_id, int sn){
    ofstream tutorFile("tutors.csv", ios::app); 
    if (tutorFile.is_open()) {
        tutorFile << id << "," << sub_id << "," << sn << endl;
        tutorFile.close();
        return;
    } else {
        cerr << "Error opening tutors.csv for writing." << endl;
        return;
    }
}

void inputRequest(vector<int>&b, vector<pair<string,int>> &a)
{
    ifstream f;
    f.open("student_request.csv");
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string
            int i;
            string n;
            char* items = strtok(strToSplit, ",");
            b.push_back(stoi(items));
            items = strtok(nullptr, ",");     
            i = stoi(items);
            items = strtok(nullptr, ",");                         
            n = items;
            // Create a new User object and add it to the library
            a.push_back(make_pair(n,i));

            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }                      
}

void save_answer(int id, string ans){
   ofstream ansFile("answer.csv", ios::app); 
    if (ansFile.is_open()) {
        ansFile << id << "," << ans << endl;
        ansFile.close();
        return;
    } else {
        cerr << "Error opening answer.csv for writing." << endl;
        return;
    } 
}

void inputAnswer(vector<pair<int,string>> &a){

    ifstream f;
    f.open("answer.csv");
    if(f.is_open()){
        string line;
        getline(f, line); // Skip the first line
        while (getline(f, line)) {
            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string
            char* items = strtok(strToSplit, ","); 
            int n = stoi(items);
            items = strtok(nullptr, ",");
            string i = items;
            a.push_back(make_pair(n,i));
            free(strToSplit); // Free the dynamically allocated memory
    }
    f.close(); // Close the file
    } 
    else {
        cout << "Failed to open the file." << endl;
    }                      
}

