#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankUser.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{

public:
    static void updateUserScreen()
    {
        vector <clsBankUser> vUsers = clsBankUser::getUserListVector(UsersDataFile);

        _drawScreenHeader("\tUpdate User Info Screen");

        string userName = clsBankUser::readUserName(enStatus::Exist);

        if (userName == "Admin")
        {
            cout << "\nThis User Can't Be Updated, Please Contact The Admin For More Information.";
            return;
        }

        clsBankUser & userToBeUpdated = clsBankUser::findUserRef(userName, vUsers);

        clsPrintPersonCard::printUserInfo(userToBeUpdated);

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            if (userToBeUpdated._mode == clsBankUser::enMode::UpdateMode)
            {
                clsBankUser::_changeUserRecord(userToBeUpdated);

                clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);

                cout << "\nUser Updated Successfully." << endl;

                clsPrintPersonCard::printUserInfo(userToBeUpdated);
            }
            else cout << "\nUpdate Failed, It's an empty object.";
        }
    }
};
