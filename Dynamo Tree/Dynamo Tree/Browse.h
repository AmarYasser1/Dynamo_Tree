// سبحان الله والحمد لله والله أكبر
#pragma once
#include "Manger.h"
#include <windows.h>
#include<unordered_map>
#include<vector>
#include<utility>
#include<algorithm>

enum ACITVITY { Like, Comment, Follow, Share, Create_post, View_Profile, log_out };

class Browse {
	Manger* mn;
	AVLTree* at;
	unordered_map<string, int> Hashtags;

public:
	Browse();

	~Browse();

	Manger* get_reference_manger();

	void Browse_user();

	void LIKE(int);

	void COMMENT(int);

	void FOLLOW(int);

	void SHARE(int);

	void CREATE_POST(int);

	void VIEW_PROFILE(int);

	void Statistics();

	void print_Treding();
};
