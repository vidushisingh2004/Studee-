#ifndef __TUTOR_H__
#define __TUTOR_H__
#include <string>
#include "User.h"

class Tutor: public User{
    private:
        
        int student_num, subjectID;
        void update() {
        // Read existing entries from the CSV file
            vector<vector<int>> entries;
            ifstream file("tutors.csv");
            if (file.is_open()) {
                int id, sub, sn;
                while (file >> id >> sub >> sn) {
                    entries.push_back({id , sub , sn});
                }
                file.close();
            }

            int pos = -1;
            // Find and update the relevant entry
            for (int i = 0; i < entries.size(); i++){
                if (entries[i][0] == ID){
                    pos = i;
                    break;
                }
            }
            if (pos != -1) {
                // Update the existing entry
                int i = 0;
                entries[pos][1] = subjectID;
                entries[pos][2] = student_num;
            }

            // Rewrite the entire CSV file
            ofstream outFile("tutors.csv");
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
        //New tutor
        Tutor(const User& a): User(a),student_num(0){}
        //Returning tutor
        Tutor(const User& a, int c, int s): User(a), subjectID(c), student_num(s){
        }

        int get_student_num(){
            return student_num;
        }
        
        void set_subject(int id){
            if (subjectID == id){
                return;
            }
            else{    
                subjectID = id;
                student_num = 0;
                update();
                return;
            }
        }

        bool add_student(){
            if (student_num  == 5){
                return false;
            }
            else{
                student_num += 1;
                update();
                return true;
            }
        }
};

#endif