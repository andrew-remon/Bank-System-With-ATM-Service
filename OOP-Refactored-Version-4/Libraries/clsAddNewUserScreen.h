#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsBankUser.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
public:
    static void addNewUserScreen()
    {
        vector <clsBankUser> vUsers = clsBankUser::getUserListVector(UsersDataFile);

        _drawScreenHeader("\tAdd New User Info Screen");

        string userName = clsBankUser::readUserName(enStatus::New);

        clsBankUser newUser = clsBankUser::_getAddUserObject(userName);

        clsBankUser::_changeUserRecord(newUser);

        newUser._mode = clsBankUser::enMode::UpdateMode;

        vUsers.push_back(newUser);

        clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);

        cout << "\nUser Added Successfully." << endl;

        clsPrintPersonCard::printUserInfo(newUser);
    }
};
