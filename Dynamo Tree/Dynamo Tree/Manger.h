// لا حول ولا قوة إلا بالله
#pragma once
#ifndef MANGER_H
#define MANGER_H
#include "AVLTree.h"
#include<string>
#include <sstream>
#include <windows.h>
#include<vector>
class Manger
{
private:
    AVLTree *at;

public:
     Manger();
     ~Manger();

    void addUser();

    void removeUser();
    
    void updateUser();

    void searchUser();
  
    void printAllUser();

    void checkVlidUser(string& ,  int& , string , string);

    void Handle_users();

    bool IsValidChoice(string num);

    AVLTree* get_reference_tree();
};

#endif // MANGER_H

