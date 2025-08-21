#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsEnums.h"
#include "clsBankClient.h"
#include "clsBankUser.h"
#include "clsInputValidation.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsGlobal.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>

using namespace std;

class clsUserScreen : protected clsScreen
{
private:
    static short _readUserChoice()
    {
        cout << setw(30) << "" << "Choose What Do You Want to do? [1 to 6]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 6, "please enter a number between 1 and 6");
        return choice;
    }

    static void _performUserChoice(enUserChoice userChoice);
public:
    static void showUserMenu();
};
