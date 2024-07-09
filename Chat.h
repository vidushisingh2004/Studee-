#ifndef __CHAT_H__
#define __CHAT_H__
#include <string>
#include <vector>
using namespace std;

class ChatRoom{
    protected:
        //10 users in a char
        int ids[10], num_participants;
        //chat history (record the device time?)
        vector<string> history;
        //chat context (userID_time_context); reset every 30 texts
        vector<string> context;
    public:
        //methods: starting the chat, stopping the chat, deleting the history
        ChatRoom(int* id){
            int len = 0;
            while (id[len]){len++;}
            for (int i = 0; i < len; i ++){
                ids[i] = id[i];
            }
            num_participants = sizeof(ids) / sizeof(int);
        }
};

#endif