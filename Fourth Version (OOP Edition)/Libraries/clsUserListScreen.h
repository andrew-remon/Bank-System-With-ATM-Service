#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include <iomanip>
using namespace std;

class clsUserListScreen : protected clsScreen
{
private:
    static void _printUserData(clsBankUser userData)
    {
        cout << setw(5) << left << "" << "| " << setw(17) << left << userData.getUserName();
        cout << "| " << setw(15) << left << userData.getPassword();
        cout << "| " << setw(20) << left << userData.FullName();
        cout << "| " << setw(15) << left << userData.getPhone();
        cout << "| " << setw(27) << left << userData.getEmail();
        cout << "| " << setw(14) << left << userData.getAccessValue() << "|";
    }

public:
    static void showUsersList()
    {
        vector <clsBankUser> vUsers = clsBankUser::getUserListVector(UsersDataFile);

        string title = "\t\tUsers List Screen";
        string subTitle = "\t\tUsers List (" + to_string(vUsers.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(5) << left << "" <<  "-------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(5) << left << "" << "| " << left << setw(17) << "UserName:";
        cout << "| " << left << setw(15) << "Password:"      ;
        cout << "| " << left << setw(20) << "User FullName:" ;
        cout << "| " << left << setw(15) << "Phone:"         ;
        cout << "| " << left << setw(27) << "Email:"         ;
        cout << "| " << left << setw(15) << "Access Value: |" << endl;
        cout << setw(5) << left << "" << "-------------------------------------------------------------------------------------------------------------------------" << endl;

        if (vUsers.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsBankUser & user : vUsers)
        {
            _printUserData(user);
            cout << endl;
        }
        cout << setw(5) << left << "" <<  "-------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};
