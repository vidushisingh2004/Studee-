#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <vector>

using namespace std;

class User{
    protected:
        string full_name, email_or_phone, password, level, twitter, facebook;
        int age, ID;
        bool microphone, camera;
        string chatGroup;
        virtual void update(){
            return;
        }
    public:
    //Default Constructor
        User(){}
        User(const User& other): full_name(other.full_name), email_or_phone(other.email_or_phone),
          password(other.password), level(other.level), twitter(other.twitter),
          facebook(other.facebook), age(other.age), ID(other.ID),
          microphone(other.microphone), camera(other.camera),
          chatGroup(other.chatGroup) {}

        User(int id, string n, int a, string e, string p, string l, bool c, bool m, string t, string f): ID(id), full_name(n), age(a),email_or_phone(e), password(p), level(l), microphone(m), camera(a), twitter(t), facebook(f){}
        User(string n, int a, string e, string p, string l, bool c, bool m, string t, string f): full_name(n), age(a),email_or_phone(e), password(p), level(l), microphone(m), camera(a), twitter(t), facebook(f){
            ID = 0;
        }
        
        void set_full_name(string n){
            full_name = n;
        }

        void set_age(int a){
            age = a;
        }
       
        void set_email_or_phone(string e){
            email_or_phone = e;
        }

        void set_password(string p){
            password = p;
        }

        void set_twitter(string t){
            twitter = t;
        }
        void set_facebook(string f){
            facebook = f;
       }

        //get information
        string get_username() const{
            return email_or_phone;
        }

        string get_password() const{
            return password;
        }

        string get_level() const{
            return level;
        }
        
        string get_full_name() const{
            return full_name;
        }

        int get_age() const{
            return age;
        } 

        int get_ID() const{
            return ID;
        }

        bool get_camera() const{
            return camera;
        }

        bool get_microphone() const{
            return microphone;
        }
        string get_twitter() const{
	        return twitter;
        }
        string get_facebook() const{
            return facebook;
        } 
};

#endif


