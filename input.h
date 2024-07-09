#ifndef INPUT_H
#define INPUT_H
#include<string>
#include<vector>
#include "User.h"
using namespace std;


struct qa{
    int quest_id, sub_id;
    string question;
};

void inputUser(string filename, vector<User> &a);  

void inputStudentTutor(string filename, vector<vector<int>> &a);

int save_user(User a);

void inputSubject(string filename, vector<string> &a);

void save_student(Student a);

void inputQuestion(string filename, vector<qa> &a);

void inputStudyGroup(string filename, vector<pair<string,int>> &a);

void save_question(int id, int sub,string q);

void save_tutor(int id, int sub_id, int sn);

void inputRequest(vector<int>&b, vector<pair<string,int>> &a);

void inputAnswer(vector<pair<int,string>> &a);

void save_answer(int id,string q);

#endif
