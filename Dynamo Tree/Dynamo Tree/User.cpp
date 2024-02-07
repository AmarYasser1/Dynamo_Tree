#include "User.h"
User::User() : dateRegistration(getCurrentTimeStamp()), FollowUp(new int[50]) {
	 userName = "";
	 password = "";
	 email = "";
	gender = "";
	 birthday = "";
	 phoneNumber = "";
	 Followers = 0;
	 idx = 0;
}

void User::setUserName(const string& userName) { this->userName = userName; }
void User::setPassword(const string& pass) { this->password = pass; }
void User::setEmail(const string& email) { this->email = email; }
void User::setGender(const string& gender) { this->gender = gender; }
void User::setBirth(const string& birthday) { this->birthday = birthday; }
void User::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setFollowers(const int& number) { this->Followers = number; }
void User::pushFollowed(const int& hashCode) {
	FollowUp[idx++] = hashCode;
}

bool User::checkFollowes(const int& hashCode) {
	for (auto i = 0; i < idx; ++i)
		if (FollowUp[i] == hashCode) return false;

	return true;
}
int User::increase_follower() { ++Followers; return Followers; }
int User::getFollowers() const { return this->Followers; }
string User::getUserName() const { return this->userName; }
string User::getPassword() const { return this->password; }
string User::getEmail() const { return this->email; }
string User::getGender() const { return this->gender; }
string User::getBirth() const { return this->birthday; }
string User::getPhoneNumber() const { return this->phoneNumber; }
string User::get_dateRegistration() const { return dateRegistration; }
string User::getCurrentTimeStamp() {
	auto now = chrono::system_clock::now();
	time_t currentTime = chrono::system_clock::to_time_t(now);

	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

	return buffer;
}

istream& operator >> (istream& in, User& user) {
	//cout << "Enter the userName : ";
	//in >> user.userName;

	cout << "Enter the email : ";
	in >> user.email;

	char ch;
	do {
		cout << "Enter the password: ";
Handle_empty_password:
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b' && !user.password.empty()) {
				user.password.pop_back();
				cout << "\b \b";
			}
			else if (ch != '\b') {
				cout << '*';
				user.password += ch;
			}
		}
		cout << endl;
		if (user.password.empty())
			goto Handle_empty_password;

		//password verfication!!
		string check_password = "";
		cout << "Password confirmation: ";

Handle_empty_password_verfication:
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b' && !check_password.empty()) {
				check_password.pop_back();
				cout << "\b \b";
			}
			else if (ch != '\b') {
				cout << '*';
				check_password += ch;
			}
		}
		cout << endl;

		if (check_password.empty())
			goto Handle_empty_password_verfication;

		if (user.password == check_password) {
			check_password.clear();
			break;
		}
		if (user.password != check_password) {
			cout << "-> Passwords don't match...Try again." << endl;
			user.password.clear();
			check_password.clear();
		}
	} while (true);
	char gen;
	do {
		cout << "Choose your gender (1-Male/2-Female) : ";
		cin >> gen;
		switch (gen)
		{
		case '1':
			user.gender = "Male";
			break;
		case '2':
			user.gender = "Female";
			break;
		case '3':
			user.gender = "Civil Engineer";
			break;
		default:
			cout << "-> Invalid Choice...Please choose 1 or 2 only." << endl;
			system("pause");
			break;
		}
	} while (gen != '1' && gen != '2' && gen != '3');

	cout << "Enter the birthday : ";
	in >> user.birthday;

	
Handle_PhoneNumber:
	bool check = false;
	cout << "Ente the phoneNumber : ";
	in >> user.phoneNumber;

	for (int i = 0; i < user.phoneNumber.size(); i++)
		if (!isdigit(user.phoneNumber[i]))
		{
			check = true;
			break;
		}
	if (check) {
		cout << "No letters allowed in the phone number...type numbers only."<<endl;
		user.phoneNumber.clear();
		goto Handle_PhoneNumber;
	}
	
	return in;
}
ostream& operator << (ostream& out, const User& user) {
	out << "* The username : " << user.userName << endl;
	out << "* The Email : " << user.email << endl;
	out << "* The Password : " << user.password << endl;
	out << "* The Gender : " << user.gender << endl;
	out << "* The Birthday : " << user.birthday << endl;
	out << "* The phoneNumber : " << user.phoneNumber << endl;
	out << "* The Followers : " << user.Followers << endl;
	out << "* Registration Date : " << user.dateRegistration << endl;
	return out;
}