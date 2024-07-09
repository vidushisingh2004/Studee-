#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <string>
#include "User.h"
#include <vector>
#include <algorithm>

using namespace std;

//Use csv file to store the User information.

class Student: public User{
    private:
        int subjectID;
        int tutorID;

        void update() {
        // Read existing entries from the CSV file
            vector<vector<int>> entries;
            ifstream file("students.csv");
            if (file.is_open()) {

                int id, tuID, subID;
                while (file >> id >> tuID >> subID) {
                    entries.push_back({id, tuID, subID});
                }
                file.close();
            }

            int pos = -1, i = 0;
            // Find and update the relevant entry
            for (int i = 0; i < entries.size(); i++){
                if (entries[i][0] == ID){
                    pos = i;
                }
            }
            if (pos != -1) {
                // Update the existing entry
                entries[i][1] = tutorID;
                entries[i][2] = subjectID;
            }

            // Rewrite the entire CSV file
            ofstream outFile("students.csv");
            if (outFile.is_open()) {
                for (const auto& entry : entries) {
                    outFile << entry[0] << "," << entry[1] << "," << entry[2] << endl;
                }
                outFile.close();
            } else {
                cerr << "Error writing to file." << endl;
            }
        }
    public:
        Student(const User &a, int s = -1, int t = -1): User(a), subjectID(s), tutorID(t){}

        int get_subject() const{
            return subjectID;
        }

        int get_tutor() const{
            return tutorID;
        }

        void set_subject(int id){
            if (subjectID == id){
                return;
            }
            else{    
                subjectID = id;
                //Change the subject then need to change to tutor
                tutorID = 0;
                //update();
                return;
            }
        }

        void set_tutor(int id){
            if (tutorID == id){
                return;
            }
            else{
                tutorID = id;
                //update();
                return;
            }
        }
};

#endif
