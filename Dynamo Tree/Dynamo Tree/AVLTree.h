// لا إله إلا أنت سبحانك إني كنت من الظالمين
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<algorithm>
#include<assert.h>
#include "User.h"
#include "Queue.h"

#define DEBUG
#ifdef DEBUG

#define Amar(condition, message) \
    if (!(condition)) { \
        cerr << "Assertion failed: " << #condition << ". " << message << " [" << __FILE__ << ":" << __LINE__ << "]" << endl; \
        terminate(); \
    }

#else
#define Amar(condition, message)
#endif
using namespace std;

struct Activity {
    string type;
    string description;
    string timeStamp;

    Activity() : type(""), description("") {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

        timeStamp = buffer;
    }

    void print() {
        cout << "**************************" << endl;
        cout << "Type : " << type << endl;
        cout << "Description : " << description << endl;
        cout << "Timestamp : " << timeStamp << endl;
    }
};

struct ACTIVE {
    int Like = 0, Comment = 0,
        Follow = 0, Share = 0,
        Create_Post = 0, View_Profile = 0,
        log_out = 0, log_in = 0;
        

    void print_statistics_activity() {
        cout << "Logged in : " << log_in << endl;
        cout << "Like : " << Like << endl;
        cout << "Comment : " << Comment << endl;
        cout << "Follow : " << Follow << endl;
        cout << "Share : " << Share << endl;
        cout << "Posts Created : " << Create_Post << endl;
        cout << "View Profile : " << View_Profile << endl;
        cout << "Logged out : " << log_out << endl;
        cout << "***************************" << endl;
    }
};

struct AVLNode {
    User* user;
    Queue<Activity> Activities;
    ACTIVE act;
    int hashValue;
    
    int height;

    AVLNode* left;
    AVLNode* right;

    AVLNode() : left(nullptr), right(nullptr), user(new User()) {}
};

class AVLTree {
    AVLNode* root{};
    size_t mx_size = 1000;

public:
    AVLTree();

    AVLNode* ROOT();

    bool isEmpty();

    size_t Max_size();

    int ch_height(AVLNode* node);

    void update_height(AVLNode* node);

    int balanced_factor(AVLNode* node);

    int hashCode(string str, int INTERNAL_NUMBER = 27894);

    AVLNode* right_rotation(AVLNode*& Q);

    AVLNode* left_rotation(AVLNode*& Q);

    AVLNode* balance(AVLNode* node);

    AVLNode* insert_node(AVLNode* newNode, AVLNode* Troot = nullptr);

    AVLNode* min_node(AVLNode* node);

    AVLNode* delete_node(int hashCode, AVLNode* Troot = nullptr);
         
    void Insert(AVLNode* node);

    AVLNode* Delete(int hashValue);

    AVLNode* search(int hashCode, AVLNode* Troot = nullptr);

    void print(AVLNode* Troot = nullptr);

    void print_Statistics(AVLNode* Troot = nullptr);
};

