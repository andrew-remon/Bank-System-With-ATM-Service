#include <iostream>
#include "clsMainScreen.h"
#include "clsTransactionScreen.h"
#include "clsUserScreen.h"
#include "clsGlobal.h"
#include "clsLoginScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsGlobal.h"
using namespace std;

void clsMainScreen::_performMainMenuChoice(enChoice choice)
{
    switch (choice)
    {
        case enChoice::ShowClientList :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::ShowClientList))
            if (currentUser.isUserHasPermission(enPermissions::showing))
                clsClientListScreen::showClientsList();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::AddNewClient :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::AddNewClient))
            if (currentUser.isUserHasPermission(enPermissions::adding))
                clsAddNewClientScreen::addNewClientScreen();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::DeleteClient :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::DeleteClient))
            if (currentUser.isUserHasPermission(enPermissions::deleting))
                clsDeleteClientScreen::deleteClientScreen();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::UpdateClientInfo :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::UpdateClientInfo))
            if (currentUser.isUserHasPermission(enPermissions::updating))
                clsUpdateClientScreen::updateClientScreen();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::FindClient :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::FindClient))
            if (currentUser.isUserHasPermission(enPermissions::finding))
                clsFindClientScreen::findClientScreen();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::Transactions :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::Transactions))
            if (currentUser.isUserHasPermission(enPermissions::transactions))
                clsTransactionScreen::showTransactionsMenu();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::ManageUsers :
        {
            // if (clsBankUser::isUserHasPermission(enChoice::ManageUsers))
            if (currentUser.isUserHasPermission(enPermissions::managingUsers))
                clsUserScreen::showUserMenu();
            else clsBankUser::printAccessDeniedMessage();
            break;
        }
        case enChoice::LogOut :
        {
            currentUser = clsBankUser::findUserByUserNameAndPassword("", "");
            clsLoginScreen::showLogInScreen();
            break;
        }
    }
}

void clsMainScreen::showMainMenu()
{
    _drawScreenHeader("\t\tMain Screen"); // ! inherited from the clsScreen class.

    cout << "\n\t\t\t\t\t===========================================\n" ;
    cout << setw(40) << left << "" << "\t\tMain Menu Screen\n" ;
    cout << setw(40) << left << "" << "===========================================\n" ;
    cout << setw(40) << left << "" << "\t[1] Show Clients List.\n" ;
    cout << setw(40) << left << "" << "\t[2] Add New Client.\n" ;
    cout << setw(40) << left << "" << "\t[3] Delete Client.\n" ;
    cout << setw(40) << left << "" << "\t[4] Update Client Info.\n" ;
    cout << setw(40) << left << "" << "\t[5] Find Client.\n" ;
    cout << setw(40) << left << "" << "\t[6] Transactions.\n" ;
    cout << setw(40) << left << "" << "\t[7] Manage Users.\n" ;
    cout << setw(40) << left << "" << "\t[8] Log Out.\n" ;
    cout << setw(40) << left << "" << "===========================================\n" ;
    _performMainMenuChoice((enChoice)_readMainMenuChoice());
}
