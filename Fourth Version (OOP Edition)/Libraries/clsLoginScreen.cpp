#include <iostream>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include "clsBankUser.h"
#include "clsGlobal.h"
using namespace std;

void clsLoginScreen::_login()
{
    bool loginFailed = true;
    string userName, password;
    do
    {
        cout << "\nEnter UserName? \n";
        userName = clsInputValidation::readString();
        cout << "Enter Password? \n";
        password = clsInputValidation::readString();

        currentUser = clsBankUser::findUserByUserNameAndPassword(userName, password);
        loginFailed = currentUser.isEmpty();

        if(loginFailed) cout << "\nInvalid UserName/Password!\n";
        else loginFailed = false;

    } while (loginFailed);

    clsMainScreen::showMainMenu();
}


void clsLoginScreen::showLogInScreen()
{
    _drawScreenHeader("\t\t Login Screen");
    _login();
}
