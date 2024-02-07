// سبحان الله وبحمده سبحان الله العظيم
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<conio.h>
#include <chrono>
#include <ctime>
using namespace std;

class User {
	string userName;
	string password;
	string email;
	string gender;
	string birthday;
	string phoneNumber;
	string dateRegistration;
	int* FollowUp;
	int idx;
	int Followers;

public:
	User();

	void setUserName(const string&);
	void setPassword(const string&);
	void setEmail(const string&);
	void setGender(const string&);
	void setBirth(const string&);
	void setPhoneNumber(const string&);
	void setFollowers(const int&);
	void pushFollowed(const int&);

	bool checkFollowes(const int&);
	int increase_follower();
	int getFollowers() const;
	string getUserName() const;
	string getPassword() const;
	string getEmail() const;
	string getGender() const;
	string getBirth() const;
	string getPhoneNumber() const;
	string get_dateRegistration() const;
	static string getCurrentTimeStamp();

	friend istream& operator >> (istream& is,User& user);
	friend ostream& operator << (ostream& os, const User& user);
};