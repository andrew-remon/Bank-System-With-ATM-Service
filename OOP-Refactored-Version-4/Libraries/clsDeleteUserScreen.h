#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankUser.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
public:
    static void deleteUserScreen()
    {
        vector <clsBankUser> vUsers = clsBankUser::getUserListVector(UsersDataFile);

        _drawScreenHeader("\t Delete User Info Screen");

        string userName = clsBankUser::readUserName(enStatus::Exist);

        clsBankUser & userToBeDeleted = clsBankUser::findUserRef(userName, vUsers);

        clsPrintPersonCard::printUserInfo(userToBeDeleted);

        char ans = clsUtil::confirm("Are You Sure you want to delete this account date (Y/N)");

        if (tolower(ans) == 'y')
        {
            clsBankUser::_markUserDeleteSign(userToBeDeleted, vUsers);
            clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);
            userToBeDeleted = clsBankUser::_getEmptyUserObject();
            cout << "\nUser Deleted Successfully." << endl;
        }
    }
};
