#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include"/usr/local/cs/cs251/react.h"
#include"User.h"
#include"Tutor.h"
#include"Student.h"
#include"input.h"
using namespace std;

//Global variables1
bool react {false};
//Initialize with curly brackets
const int input_index = 2, prompt_index = 100;
string username, password, full_name, level, facebook, twitter;
int age, quest_pos, subjectId, ID, group_pos, student_ID = 0, stu_num = 0, tutor_id = 0;
bool camera, microphone;

vector<User> returning_users;
vector<vector<int>> returning_students;
vector<vector<int>> returning_tutors;
vector<int> subject_tutors;
vector<pair<string,int>> study_group;
vector<string> subjects;
vector<qa> questions;
vector<pair<int, string>> answers;
vector<pair<string,int>> student_request;
vector<int> tutor_request;

string answer;

string app_state = "initial", user_state = "user";

bool login_succesfully = true;
bool app_running = true;
bool tutoring= false;
bool button = false;
bool sound = true;
bool dark = false;
int pos;

//running
string text[51];
int prev_screen = 0;
const int limit = 100;
User* curr = 0;

class State {
    int screen_num;
public:
    State(istream &is) { 
        is >> screen_num >> username >> password >> full_name >> level >> age >> camera >> microphone >> facebook >> twitter >> app_state >> user_state >> ID >> subjectId >> quest_pos >> answer >> group_pos >> stu_num >> tutor_id >> sound >> dark;
    }
    
    int get_screen_num() const { 
        return screen_num;
    }

    void write_to(ostream &os) const { 
        os << screen_num << ' ' << username << ' ' << password << ' ' << full_name << ' ' << level << ' ' << age << ' ' << camera << ' ' << microphone << ' ' << facebook << ' ' << twitter << ' ' << app_state << ' ' << user_state << ' ' << ID << ' ' << subjectId << ' ' << quest_pos << ' ' << answer << ' ' << group_pos << ' ' << stu_num << ' ' << tutor_id << ' ' << sound << ' ' << dark;
    }

    void update(string input, istream &is);

    bool student_check(int id){
    for (int i = 0; i < returning_students.size(); i++){
        if(returning_students[i][0] == id){
            curr = new Student(*curr, returning_students[i][1], returning_students[i][2]);
            subjectId = returning_students[i][2];
            tutor_id = returning_students[i][1];
            return true;
        }
    }
    return false;
}

bool tutor_check(int id){
    for (int i = 0; i < returning_tutors.size(); i++){
        if(returning_tutors[i][0] == id){
            curr = new Tutor(*curr, returning_tutors[i][1], returning_tutors[i][2]);
            subjectId = returning_tutors[i][1];
            stu_num = returning_tutors[i][2];
            return true;
        }
    }
    return false;
}

};



void read_text_data() {
  ifstream fs("main.txt");
  string comment;
  for (int i = 0; i < 51; ++i) {
	getline(fs, text[i], '#');
	text[i].pop_back();
	getline(fs, comment);
  }
  inputUser("users.csv", returning_users);
  inputSubject("subject.csv", subjects);
  inputStudentTutor("students.csv", returning_students);
  inputStudentTutor("tutors.csv",returning_tutors);
  inputQuestion("qa.csv", questions);
  inputStudyGroup("studygroup.csv", study_group);
  inputRequest(tutor_request, student_request);
  inputAnswer(answers);
}

void display(const State &state, ostream &os) {
    int n = state.get_screen_num();
    if (react) {
        if(!dark)
        _add_yaml("studee.yaml", {{"prompt_index", prompt_index},
                    {"input_index", input_index}});
        else
        _add_yaml("studee_dark.yaml", {{"prompt_index", prompt_index},
                    {"input_index", input_index}});
        os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";   
    } else os << "\033c";
  
    

    if (n == 40){
        os << "                   "         << text[n] << questions[quest_pos].question << "\nInput your answer: ";
    }

    else if (n == 41){
        os << "                   "         << text[n] << questions[quest_pos].question << "\n" << "Answer: " << answer;
    }
    
    //Print all the subjects available
    else if(n == 24){
        string subject = "";
        for(int i = 0; i < subjects.size(); i++){
            subject += to_string(i+1) + ". " + subjects[i] + '\n';
        }
        os << "                   "         << text[n] << endl << subject;
    }

    else if(n == 25){
       os << "                   "         << text[n] << "[" << subjects[subjectId-1] <<"] "; 
    }
    else if(n == 39){
        string question = "";
        for(int i = 0; i < questions.size(); i++)
            question += to_string(i + 1)  + ". " + questions[i].question + '\n';
        os << "                   "         << text[n] << endl << question;
    }
    else if(n == 43){
        string studygroup = "";
        for(int i = 0; i < study_group.size(); i++){
            studygroup += to_string(i+1) + ". " + study_group[i].first + '\n';
        }
        os << "                   "         << text[n] << endl << studygroup;
    }

    else if(n == 32){
        string qu32 = "";
        for (int i = 0; i < questions.size(); i++){
            qu32 += to_string(i + 1) + " [" + subjects[questions[i].sub_id - 1] + "] " + questions[i].question + "\nAnswers:\n";
            for (int j = 0; j < answers.size(); j++){
                if(answers[j].first == i + 1)
                    qu32 += "* " + answers[j].second + "\n"; 
            }
            qu32 += "\n";
        }
        os << "                   "         << text[n]  << qu32;
    }

    else if(n == 30){
        os << "                   "         << text[n] << study_group[group_pos].first << " with " << study_group[group_pos].second << " other peers. Stay Focus and Finish Your Work! Press enter to come back!" << endl;
    }

    else if(n == 44){
        os << "                   "         << text[n] << subjects[subjectId - 1] << endl;
    }

    //Choosing a tutor that tutors the subject
    else if(n == 27){
        string tutors = "";
        for (int i = 0; i < returning_tutors.size(); i++){
            if (returning_tutors[i][1] == subjectId){
                tutors += to_string(returning_tutors[i][0]) + ": " + returning_users[returning_tutors[i][0] - 1].get_full_name() + "\nLevel: " + returning_users[returning_tutors[i][0] - 1].get_level() + "\nFacebook:" + returning_users[returning_tutors[i][0] - 1].get_facebook() +  "\nTwitter:" + returning_users[returning_tutors[i][0] - 1].get_twitter() + "\n";
            }
        }
        os << "                   "    	    << text[n] << tutors;
    }

    else if(n == 45){
        string info = " " + subjects[subjectId - 1] + "\nTutor: ";
        if (tutor_id != 0){
            info += returning_users[tutor_id - 1].get_full_name() + " Facebook: " +  returning_users[tutor_id - 1].get_facebook() + " Twitter: " + returning_users[tutor_id - 1].get_twitter();
        }
        os << "                   "    	    << text[n] << info;
    }

    else if(n == 49){
        string s = "";
        if(sound){
            s = "On";
        }
        else{
            s = "Off";
        }
        os << "                   " << text[n] << s;
    }

    else if(n == 33){
        string tutor;
        for(int i = 0; i < returning_tutors.size(); i++){
            if(returning_tutors[i][0] == ID){
                tutor =  to_string(returning_tutors[i][0]) + ": " + returning_users[returning_tutors[i][0] - 1].get_full_name() + "\nLevel: " + returning_users[returning_tutors[i][0] - 1].get_level() + "\nFacebook:" + returning_users[returning_tutors[i][0] - 1].get_facebook() +  "\nTwitter:" + returning_users[returning_tutors[i][0] - 1].get_twitter() + "\n";
                break;
            }
        }
        os << "                   " << text[n] << tutor;
    }

    else if(n == 35){
        string requests = "";
        for (int i = 0; i < tutor_request.size(); i++){
            if (tutor_request[i] == ID){
                requests += "Student ID: " + to_string(student_request[i].second) + " Name: " + returning_users[student_request[i].second - 1].get_full_name() + "\nMessage: " + student_request[i].first + "\n"; 
            }
        }
        os << "                   " << text[n] << requests;
    }

    else if(n == 50){
        string students = "";
        for (int i = 0; i < returning_students.size(); i++){
            if (returning_students[i][1] == ID){
                students += "Student ID: " + to_string(returning_students[i][0]) + " Name: " + returning_users[returning_students[i][0] - 1].get_full_name() + "\nLevel: " + returning_users[returning_students[i][0] - 1].get_level() + "\n"; 
            }
        }
        os << "                   " << text[n] << students;
    }
    else{
    os << "                   " << text[n];
    }
    if (react) os << '\0';  // provide ending null-byte
    if (n >= limit) exit(0);
}

bool authorization(string u, string p){
    int i = 0;
    while (i < returning_users.size()){
        if (returning_users[i].get_username() == u && returning_users[i].get_password() == p){
            curr = &returning_users[i];
            return true;
        }
        else if (returning_users[i].get_username() == u){
            return false;
        }
        i++;
    }
    return false;
}

vector<pair<string,int>> requested (int ID){
    vector<pair<string,int>> res;
    for (int i = 0; i < tutor_request.size(); i++){
        if(tutor_request[i] == ID){
            res.push_back(make_pair(student_request[i].first, student_request[i].second));
        }
    }
    return res;
}
//Update screen function
void State::update(string input, istream &is) {
    if (react && _received_event()) {
            // get input from the stream
            is.get(); 
            is.get();  
            // skip first two ~s
            //cannot use getline with const string
            if ('~' != is.peek()) getline(is, input, '\0');         
        
    }
    if (user_state == "user")
        curr = new User(ID, full_name, age, username, password, level, camera, microphone,twitter,facebook);
    else if (user_state == "tutor")
        curr = new Tutor(User(ID, full_name, age, username, password, level, camera, microphone,twitter,facebook), subjectId, stu_num);
    else if (user_state == "student")
        curr = new Student(User(ID, full_name, age, username, password, level, camera, microphone,twitter,facebook), subjectId, tutor_id);

    switch(screen_num){
        case 0:
            screen_num = 1;
            break;
        //Welcome page
        case 1:
            if (input == "1"){
                screen_num = 2;
            }
            else if (input == "2"){
            //New User
                screen_num = 6;
            }
            else{
                screen_num = 15;
            }
            break;
        //Sign In Page
        case 2:
            if(input != ""){
                username = input;
                screen_num = 3;
            }
            else{
                screen_num = 2;
            }
            break;

        case 3:
            password = input;
            login_succesfully = authorization(username, password);
            if(login_succesfully){
                full_name = (*curr).get_full_name();
                age = (*curr).get_age();
                level = (*curr).get_level();
                ID = (*curr).get_ID();
                camera = (*curr).get_camera();
                microphone = (*curr).get_microphone();
                facebook = (*curr).get_facebook();
                twitter = (*curr).get_twitter();
                screen_num = 4; //Success
            }     
            else
                screen_num = 5; //Failed
            break;
        
        case 4:
            screen_num = 17; //Move to the main menu
            break;
        
        case 5:
            screen_num = 2;
            break;

        case 6:
            full_name = input;
            screen_num = 7;
            break;
        
        case 7:
            try {
                age = stoi(input);
                screen_num = 9;
            } catch (const std::invalid_argument& e) {
                // Handle the case where input is not a valid integer
                prev_screen = 7;
                screen_num = 8;
            }
            break;       
        
        case 8:
        //invalid input
            screen_num = prev_screen;
            break;
        
        case 9:
            username = input;
            screen_num = 10;
            break;
        
        case 10: 
            password = input;
            screen_num = 11;
            break;
        
        case 11:
            level = input;
            screen_num = 12;
            break;

        case 12:
            if (app_state == "setting"){
                if(input == "1"){
                    camera = true;
                }
                else if(input == "2"){
                        camera = false;
                    }
                screen_num = 38;
                break;
            }
            if(input == "1"){
                camera = true;
                screen_num = 13;
                break;
            }
            else if(input == "2"){
                camera = false;
                screen_num = 13;
                break;
            }
            prev_screen = 12;
            screen_num = 8;
            break;

        case 13:
            if (app_state == "setting"){
                if(input == "1"){
                    microphone = true;
                }
                else if(input == "2"){
                    microphone = false;
                }
                screen_num = 38;
                break;
            }
            if(input == "1"){
                microphone = true;
                screen_num = 14;
                break;
            }
            else if(input == "2"){
                microphone = false;
                screen_num = 14;
                break;
            }

            prev_screen = 13;
            screen_num = 8;
            break;

        case 14:
            twitter = input;
            screen_num = 15;
            break;
        
        case 15:
            facebook = input;
            screen_num = 16;
            break;
        
        case 16:
            curr = new User(full_name, age, username, password, level, camera, microphone,twitter,facebook);
            returning_users.push_back(*curr);
            ID = save_user(*curr);
            screen_num = 17;
            break;

        case 17:
            if(input == "1"){
                user_state = "tutor";
                app_state = "main_menu";
            }
            else if(input == "2"){
                user_state = "student";
                app_state = "main_menu";
            }
            else if(input == "3"){
                user_state = "group";
            }
            else if(input == "4"){
                app_state = "setting";
            }
            else if(input == "5"){
                screen_num = 29;
                break;
            }
            
            if (app_state == "main_menu" && (user_state == "student" || user_state == "tutor")){             
                screen_num = 18;
                break;
            }
            else if(user_state == "group"){
                app_state = "study buddies";
                screen_num = 43;
                break;
            }
            else if(app_state == "setting"){
                screen_num = 38;
                break;
            }
            break;

        case 18:
            app_state = "main_menu";
            //FORUM
            if(input == "1"){
                app_state = "forum";
                screen_num = 31;
            }

            //TUTORING
            else if(input == "2"){
                if (user_state == "student"){
                    app_state = "tutoring";
                    if (student_check(curr -> get_ID()))
                    //If they already logged in as a student before
                        screen_num = 23;
                    else
                    //New student so direct them to choose a subject
                        screen_num = 24;
                }
                else if (user_state == "tutor"){
                    app_state = "tutoring";
                    if(tutor_check(curr -> get_ID()))
                    //If they already logged in as a tutor before
                        screen_num = 20;
                    else
                    //New tutor so direct them to choose a subject
                        screen_num = 19;
                }    
            }

            //BACK TO MAIN MENU
            else if(input == "3"){
                screen_num = 17;
            }    
            break;
        case 19:
        //Tutor
            screen_num = 24;
            break;

        case 20:
            if (input == "1")
                screen_num = 24;
            else if(input == "2")
                screen_num = 50;
            else if(input == "3"){
                vector<pair<string,int>> requests = requested(ID);
                if(requests.size() == 0)
                    screen_num = 34;
                else
                    screen_num = 35;
            }  
            else if(input == "4"){
                screen_num = 18;
            }      
            break;

        case 21:
            if(input == "1"){
                screen_num = 23;
            }
            else if(input == "2"){
                screen_num = 24;
            }
            else if(stoi(input) == 3){
                screen_num = 25;
            }
            else{
                screen_num = 21;
            }
            break;
        
        case 22:
            screen_num = 27;
            break;

        case 23:
        //Student menu
            if(input == "1"){
                screen_num = 27;
            }
            else if(input == "2"){
                screen_num = 24;
            }
            else if (input == "3"){
                screen_num = 45;
            }
            else if (input == "4"){
                screen_num = 18;
            }
            break;

        case 24:
        //Subject menu
            if (stoi(input)){
                int prev = subjectId;
                subjectId = stoi(input); 
                if(app_state == "forum"){
                    if(user_state == "student"){
                        screen_num = 25;
                        break; 
                    }              
                }
                else if (app_state == "tutoring"){
                    if(user_state == "student"){
                        if(prev == 0){
                            Student a(*curr, subjectId, tutor_id);
                            save_student(a);
                            screen_num = 22; 
                            break;  
                        }
                        else{
                            Student a(*curr, prev, tutor_id);
                            a.set_subject(subjectId);
                            screen_num = 23;
                        }    
                    }
                    else if (user_state == "tutor"){
                        
                        if(subjectId == 0){    
                            Tutor a(*curr, subjectId, 0);
                            save_tutor(a.get_ID(), subjectId, 0);
                            screen_num = 33; 
                            break;
                        }
                        else{
                            Tutor a(*curr, prev, stu_num);
                            a.set_subject(subjectId);
                            screen_num = 44;
                            break;
                        }
                    }
                }
                
            }
            else    
                screen_num = 24;
            break;
        case 25:
            save_question(questions.size()+1, subjectId, input);
            screen_num = 26;
            break;
        case 26:
            if (input == "1")
                screen_num = 24;
            else
                screen_num = 31;
            break;

        case 27:
            tutor_id = stoi(input);
            //Tutor a(*curr, subjectId, tutor_id);
            screen_num = 36;
            break;
        case 28:
            screen_num = 29;
            break;
        case 29:
            app_running = false;
            break;
        case 30:
            screen_num = 17;
            break;
        //FORUM selection
        case 31:
            if(input == "1"){
                if (user_state == "student")
                    screen_num = 24;
                else
                    screen_num = 31;
            }
            else if(input == "2"){
                screen_num = 32;
            }
            else if(input == "3"){
                screen_num = 39;
            }
            else if(input == "4"){
                screen_num = 18;
            }
            break;
        case 32:
            screen_num = 31;
            break;
        case 33:
            curr = new Tutor(*curr, subjectId, 0);
            //curr -> set_subject(subjectId);
            save_tutor(curr -> get_ID(), subjectId, 0);
            screen_num = 20;
            break; 
        case 34:
            screen_num = 20;
            break;
        case 35:
            screen_num = 20;
            break;
        case 36:
            screen_num = 37;
            break;
        case 37:
            screen_num = 23;
            break;
        case 38: 
            if (input == "6"){
                screen_num = 17;
            }
            else if(input == "1"){
                screen_num = 46;
            }
            else if(input == "2"){
                screen_num = 47;
            }
            else if(input == "3"){
                screen_num = 48;
            }
            else if(input == "4"){
                screen_num = 12;
            }
            else if(input == "5"){
                screen_num = 13;
            }
            break;
        case 39:
            quest_pos = stoi(input) - 1;
            screen_num = 40;
            break;
        case 40:
            answer = input;
            save_answer(quest_pos + 1, answer);
            screen_num = 41;
            break;
        case 41:
            screen_num = 42;
            break;
        case 42:
            if (input == "1")
                screen_num = 39;
            else if (input == "2")
                screen_num = 31;
            break;
        case 43:
            group_pos = stoi(input) - 1;
            screen_num = 30;
            break;
        case 44:
            screen_num = 17;
            break;
        case 45:
            screen_num = 23;
            break;

        case 46: 
            if (input == "1")
                sound = true;
            else if (input =="2")
                sound = false;
            screen_num = 49;
            break;
        case 47:
            screen_num = 38;
            break;
        case 48:
            if(input == "1"){
                dark = false;
            }
            else{
                dark = true;
            }
            screen_num = 38;
            break;
        case 49:
            screen_num = 38;
            break;
        case 50:
            screen_num = 20;
            break;
}
}

// -------- do not modify the code below -------
// ------- (except briefly for debugging) ------

int main(int argc, char **argv) {
  react = (argc > 1);
  read_text_data();

  bool just_starting = react ? _read_event_info() : true;
  while(app_running) {
    ifstream fs1(just_starting ? "initial_state" : "curr_state");
    State state(fs1);
    fs1.close();

    string input;
    if (just_starting) just_starting = false;
    else if (!react) getline(cin, input);

    ifstream fs2("incoming_text");
    state.update(input, fs2);

    ofstream fs3("outgoing_text"), fs4(react ? "end_state" : "curr_state");
    display(state, react ? fs3 : cout);
    state.write_to(fs4);

    if (react) {
      _write_react_yaml();
      break;
    }  
  }
}




