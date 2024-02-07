#include "Manger.h"
Manger::Manger() : at(new AVLTree()) {}
Manger::~Manger() { delete at; }


AVLTree* Manger::get_reference_tree() { return at; }

bool Manger::IsValidChoice(string num)
{
    bool IsNotValid = false;
    IsNotValid = false;
    try
    {
        for (int i = 0; i < num.size(); i++)
            if (!isdigit(num[i]))
            {
                IsNotValid = true;
                break;
            }

        if (IsNotValid)
            throw "Error";
    }
    catch (const char* str)
    {
        cerr << "-> Please, don't write letter. type only numbers :)\n";
        return false;
    }

    return true;
}

void Manger::checkVlidUser(string& userName , int& code , string message , string check) {
    
    do
    {
        getline(cin, userName);
        code = at->hashCode(userName);

        if (check == "addUser") {
            if (!at->search(code, at->ROOT())) return;
        }
        else {
            if (at->search(code, at->ROOT())) return;
        }
        
        cout << message;
    } while (true);
}

void Manger::addUser()
{
    AVLNode* an = new AVLNode();

    string userName;
    int code;

    cout << "Enter your user name: ";

    checkVlidUser(userName , code , "this user name is already taken please enter new one : " , "addUser");

    an->hashValue = code;
    an->user->setUserName(userName);
    cin >> *an->user;

    cin.ignore();

    at->Insert(an);
}

void Manger::removeUser()
{
    string userName;
    int code;

    cout << "Enter The user name you want to delete: ";
    
    checkVlidUser(userName, code, "No users found with this name please enter new one : " , "removeUser");

    char choice;
    bool validInput = false;

    do
    {
        cout << "ARE YOU SURE YOU WANT TO DELETE THIS USER? Y/N ";
        cin >> choice;

        cin.ignore();

        if (choice == 'Y' || choice == 'y')
        {
            cout << *at->search(code, at->ROOT())->user;
            at->Delete(code);
            cout << "--------->This User deleted successfully." << endl;
            validInput = true;
            system("pause");
        }
        else if (choice == 'N' || choice == 'n')
        {
            cout << "-> Deletion canceled." << endl;
            validInput = true;
            system("pause");
        }
        else
        {
            cout << "-> Invalid choice. Please enter Y or N." << endl;
        }
    } while (!validInput);
}

void Manger::updateUser()
{
    string userName;
    int code;

    cout << "Enter The user name you want to update: ";

    checkVlidUser(userName, code, "No users found to update with this name please enter new one : " , "updateUser");

    char ch;
    string pass = "";
    cout << "Enter the password: ";
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && !pass.empty()) {
            pass.pop_back();
            cout << "\b \b";
        }
        else if (ch != '\b') {
            cout << '*';
            pass += ch;
        }
    }
    cout << endl;

    if (at->search(code, at->ROOT())->user->getPassword() != pass) {
        cout << "-> Wrong password :(...Try again later." << endl;
        system("pause");
        return;
    }

    string email;
    string password;
    string gender;
    string birthday;
    string phoneNumber;

    // Handle menu
    auto color = [&](int cnt)-> void {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cnt);
    };

    auto menu = [&](int pos)-> void {
        int mx_size = 6;
        vector<string> v = { "Edit email .", "Edit password .", "Edit gender .","Edit birthday ." ,"Edit phone number ." , "Back ." };

        cout << "========================" << endl;
        cout << "                        " << endl;
        cout << "      Edit Menu         " << endl;
        cout << "                        " << endl;
        cout << "========================" << endl;
        for (auto i = 0; i < mx_size; ++i) {
            if (pos == i) {
                color(6);
                cout << "-->\t";
                cout << v[i] << endl;
                color(7);
            }
            else {
                cout << "\t" << v[i] << endl;
            }
        }
    };

    auto Menu = [&]()-> int {
        system("cls");
        int i = 0;
        char ch;
        menu(0);

        while (true) {

            ch = _getch();

            switch (ch) {
            case 27:
                exit(0);
                break;
            case 72: // UP
                system("cls");
                i = (i - 1 + 6) % 6;
                menu(i);
                break;
            case 80: // DOWN
                system("cls");
                i = (i + 1) % 6;
                menu(i);
                break;
            case '\r': // Enter
                return i;
            default:
                break;
            }
        }
        };

    while (true) {
        system("cls");

        int i = Menu();

        switch (i) {
        case 0:
            cout << "Enter the email: ";
            cin >> email;

            cin.ignore();
            at->search(code, at->ROOT())->user->setEmail(email);
            break;
        case 1:
            char ch;
            cout << "Enter the password: ";
            while ((ch = _getch()) != '\r')
            {
                if (ch == '\b' && !password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
                else if (ch != '\b') {
                    cout << '*';
                    password += ch;
                }
            }
            cout << endl;

            at->search(code, at->ROOT())->user->setPassword(password);
            break;
        case 2:
            char gen;
            do {
                cout << "Choose your gender (1-Male/2-Female) : ";
                cin >> gen;
                switch (gen)
                {
                case '1':
                    gender = "Male";
                    break;
                case '2':
                    gender = "Female";
                    break;
                case '3':
                    gender = "Civil Engineer";
                    break;
                default:
                    cout << "-> Invalid Choice...Please choose 1 or 2 only." << endl;
                    system("pause");
                    break;
                }
            } while (gen != '1' && gen != '2' && gen != '3');

            at->search(code, at->ROOT())->user->setGender(gender);
            break;
        case 3:
            cout << "Enter the birthday: ";
            cin >> birthday;

            cin.ignore();
            at->search(code, at->ROOT())->user->setBirth(birthday);
            break;
        case 4:
            cout << "Enter the phoneNumber: ";
            cin >> phoneNumber;

            cin.ignore();
            at->search(code, at->ROOT())->user->setPhoneNumber(phoneNumber);
            break;
        default:
            return;
        }
    }

    /*char choice;
    while (true) {
        system("cls");
        cout << "\t\t\t=======================" << endl;
        cout << "\t\t\t                           " << endl;
        cout << "\t\t\t\t  Edit menu  " << endl;
        cout << "\t\t\t                           " << endl;
        cout << "\t\t\t=======================" << endl;
        cout << "1- Edit email." << endl;
        cout << "2- Edit password." << endl;
        cout << "3- Edit gender." << endl;
        cout << "4- Edit birthday." << endl;
        cout << "5- Edit phone number." << endl;
        cout << "6- Back." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case '1':
            cout << "Enter the email: ";
            cin >> email;

            at->search(code, at->ROOT())->user->setEmail(email);
            break;
        case '2':
            char ch;
            cout << "Enter the password: ";
            while ((ch = _getch()) != '\r')
            {
                if (ch == '\b' && !password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
                else if (ch != '\b') {
                    cout << '*';
                    password += ch;
                }
            }
            cout << endl;

            at->search(code, at->ROOT())->user->setPassword(password);
            break;
        case '3':
            char gen;
            do {
                cout << "Choose your gender (1-Male/2-Female) : ";
                cin >> gen;
                switch (gen)
                {
                case '1':
                    gender = "Male";
                    break;
                case '2':
                    gender = "Female";
                    break;
                case '3':
                    gender = "Civil Engineer";
                    break;
                default:
                    cout << "-> Invalid Choice...Please choose 1 or 2 only." << endl;
                    system("pause");
                    break;
                }
            } while (gen != '1' && gen != '2' && gen != '3'); 

            at->search(code, at->ROOT())->user->setGender(gender);

            break;
        case '4':
            cout << "Enter the birthday: ";
            cin >> birthday;

            at->search(code, at->ROOT())->user->setBirth(birthday);
            break;
        case '5':
            cout << "Enter the phoneNumber: ";
            cin >> phoneNumber;
            at->search(code, at->ROOT())->user->setPhoneNumber(phoneNumber);
            break;
        case '6':
            return;
        default:
            cout << "-> Invalid choice...please choose from the list.";
            break;
        }
    }*/
}

void Manger::searchUser()
{
    string userName;
    int code;

    cout << "Enter The user name to search :";
   
    checkVlidUser(userName, code, "No users found with this name please enter new one: ", "searchUser");

    cout << *at->search(code, at->ROOT())->user;
    system("pause");
}


void Manger::printAllUser()
{
    at->print();
}


void Manger::Handle_users() {
    string choice;
    bool exitMenu = false;

    auto color = [&](int cnt)-> void {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cnt);
    };

    auto menu = [&](int pos)-> void {
        int mx_size = 6;
        vector<string> v = { "Add User .", "Remove User .", "Update User .","Search User ." ,"Print All Users ." , "Exit ."};

        cout << "Handle Users:" << endl;
        cout << "*************" << endl;
        for (auto i = 0; i < mx_size; ++i) {
            if (pos == i) {
                color(4);
                cout << "-->\t";
                cout << v[i] << endl;
                color(7);
            }
            else {
                cout << "\t" << v[i] << endl;
            }
        }
    };

    
    auto Menu = [&]()-> int {
        system("cls");
        int i = 0;
        char ch;
        menu(0);

        while (true) {

            ch = _getch();

            switch (ch) {
            case 27:
                exit(0);
                break;
            case 72: // UP
                system("cls");
                i = (i - 1 + 6) % 6;
                menu(i);
                break;
            case 80: // DOWN
                system("cls");
                i = (i + 1) % 6;
                menu(i);
                break;
            case '\r': // Enter
                return i;
            default:
                break;
            }
        }
    };

    while (true) {
        system("cls");

        int i = Menu();

        switch (i) {
        case 0:
            addUser();
            break;
        case 1:
            if (at->isEmpty()) {
                cout << "--> No user found . Please enter users first ." << endl;
                system("pause");
                break;
            }
            removeUser();
            break;
        case 2:
            if (at->isEmpty()) {
                cout << "--> No user found . Please enter users first ." << endl;
                system("pause");
                break;
            }
            updateUser();
            break;
        case 3:
            if (at->isEmpty()) {
                cout << "--> No user found . Please enter users first ." << endl;
                system("pause");
                break;
            }
            searchUser();
            break;
        case 4:
            if (at->isEmpty()) {
                cout << "--> No user found . Please enter users first ." << endl;
                system("pause");
                break;
            }
            system("cls");
            cout << " =================================  " << endl;
            cout << "|                                  |" << endl;
            cout << "|      Info Of All Users           |" << endl;
            cout << "|                                  |" << endl;
            cout << " ================================== " << endl;
            printAllUser();
            system("pause");
            break;
        default:
            return;
        }
    }

    /*while (!exitMenu) {
        system("cls");
        cout << "Handle Users:" << endl;
        cout << "*************" << endl;
        cout << "1) Add User ." << endl;
        cout << "2) Remove User" << endl;
        cout << "3) Update User" << endl;
        cout << "4) Search User" << endl;
        cout << "5) Print All Users" << endl;
        cout << "6) Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (!IsValidChoice(choice)) {
            system("pause");
            continue;
        }

        int cho = stoi(choice);

        if (at->isEmpty() && (cho >= 2 && cho <= 5)) {
            cout << "-> Manager is empty. Please add users first." << endl;
            system("pause");
            continue;
        }
        switch (cho) {
        case 1:
            addUser();
            break;
        case 2:
            removeUser();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            searchUser();
            break;
        case 5:
            system("cls");
            cout << " =================================  " << endl;
            cout << "|                                  |" << endl;
            cout << "|      Info Of All Users           |" << endl;
            cout << "|                                  |" << endl;
            cout << " ================================== " << endl;
            printAllUser();
            system("pause");
            break;
        case 6:
            exitMenu = true;
            cout << "-> Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "-> Invalid choice. Please enter a number between 1 and 6." << endl;
            system("pause");
        }
    }*/
}