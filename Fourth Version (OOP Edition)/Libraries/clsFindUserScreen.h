#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankUser.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
public:
    static void findUserScreen()
    {
        vector <clsBankUser> vUsers = clsBankUser::getUserListVector(UsersDataFile);

        _drawScreenHeader("\t Find User Info Screen");

        string userName =  clsBankUser::readUserName(enStatus::Exist);

        clsBankUser userFound = clsBankUser::findUser(userName);

        if (!userFound.isEmpty())
        {
            cout << "\nUser is Found :)\n";
            clsPrintPersonCard::printUserInfo(userFound);
        }
    }
};

