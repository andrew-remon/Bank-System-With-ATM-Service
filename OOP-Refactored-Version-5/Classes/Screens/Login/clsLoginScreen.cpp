#include <iostream>
#include "../Misc/clsMainScreen.h"
#include "clsLoginScreen.h"
#include "clsLoggedInUser.h"
#include "clsLoginLogger.h"
#include "../../Core/clsBankUser.h"
#include "../../Core/clsGlobal.h"
#include "../../Utils/clsInputValidation.h"
using namespace std;

void clsLoginScreen::_login()
{
    bool loginFailed = true;
    const short MAX_ATTEMPTS = 3;
    short remainingAttempts = MAX_ATTEMPTS;

    do
    {
        string userName, password;
        cout << "\nEnter UserName? \n";
        userName = clsInputValidation::readString();
        cout << "Enter Password? \n";
        password = clsInputValidation::readString();

        currentUser = clsBankUser::findUserByUserNameAndPassword(userName, password);
        loginFailed = currentUser.isEmpty();

        if(loginFailed)
        {
            cout << "\nInvalid UserName/Password!\n";


            if (--remainingAttempts == 0)
            {
                cout << "No More Tries Left, Please Try Again Later.\n\n";
                return;
            }

            else cout << "You have " << remainingAttempts << " " << (remainingAttempts == 1 ? "Try" : "Tries") << " Left.\n";
        }

    } while (loginFailed && remainingAttempts > 0);

    clsLoginLogger::registerLoginIntoFile(LoginRegisterFile);

    clsMainScreen::showMainMenu();
}


void clsLoginScreen::showLogInScreen()
{
    _drawScreenHeader("\t\t Login Screen");
    _login();
}
