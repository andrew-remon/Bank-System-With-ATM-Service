#include <iostream>
#include "clsUserScreen.h"
#include "clsMainScreen.h"
using namespace std;

void clsUserScreen::_performUserChoice(enUserChoice userChoice)
{
    switch (userChoice)
    {
        case enUserChoice::ShowUserList :
        {
            clsUserListScreen::showUsersList();
            break;
        }
        case enUserChoice::AddNewUser :
        {
            clsAddNewUserScreen::addNewUserScreen();
            break;
        }
        case enUserChoice::DeleteUser :
        {
            clsDeleteUserScreen::deleteUserScreen();
            break;
        }
        case enUserChoice::UpdateUserInfo :
        {
            clsUpdateUserScreen::updateUserScreen();
            break;
        }
        case enUserChoice::FindUser :
        {
            clsFindUserScreen::findUserScreen();
            break;
        }
        case enUserChoice::MainMenu:
        {
            clsMainScreen::showMainMenu();
            break;
        }
    }
}

void clsUserScreen::showUserMenu()
{
    _drawScreenHeader("\t   Manage Users Screen");

    cout << "\n\t\t\t\t\t==============================================\n" ;
    cout << setw(40) << left << "" << "\t\tUser Menu Screen\n" ;
    cout << setw(40) << left << "" << "==============================================\n" ;
    cout << setw(40) << left << "" << "\t[1] show Users List.\n" ;
    cout << setw(40) << left << "" << "\t[2] Add New User.\n" ;
    cout << setw(40) << left << "" << "\t[3] Delete User.\n" ;
    cout << setw(40) << left << "" << "\t[4] Update User Info.\n" ;
    cout << setw(40) << left << "" << "\t[5] Find User.\n" ;
    cout << setw(40) << left << "" << "\t[6] Main Menu.\n" ;
    cout << setw(40) << left << "" << "==============================================\n" ;
    _performUserChoice((enUserChoice)_readUserChoice());
}
