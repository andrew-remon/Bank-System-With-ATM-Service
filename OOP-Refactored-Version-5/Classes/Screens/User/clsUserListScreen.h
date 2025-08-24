/**
 * @file clsUserListScreen.h
 * @brief Defines the `clsUserListScreen` class for displaying all users in the system.
 *
 * ## Overview
 * The `clsUserListScreen` class provides a screen interface for listing all
 * bank users. It loads user records from the persistent storage and
 * prints them in a formatted table.
 *
 * ## Key Responsibilities
 * - Display the "Users List" screen header.
 * - Load all users from the file.
 * - Print user details in a tabular format.
 * - Handle empty data gracefully.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for headers and formatting.
 * - **Uses:**
 *   - `clsBankUser` — for accessing user data.
 *   - `iomanip` — for tabular formatting.
 *
 * ## Usage
 * Call `clsUserListScreen::showUsersList()` to display all registered users.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../Misc/clsScreen.h"
#include "../../Core/clsBankUser.h"
using namespace std;

/**
 * @class clsUserListScreen
 * @brief Provides a screen interface for listing all users.
 *
 * ## Overview
 * Responsible for rendering a table of all users stored in the system,
 * showing details like username, password, full name, phone, email, and access level.
 *
 * ## Responsibilities
 * - Load all users from file.
 * - Display users in a formatted table.
 * - Handle cases where no users exist.
 *
 * ## Methods
 * - `static void showUsersList()` — Displays all users in a table.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen`.
 * - **Uses:** `clsBankUser` (data handling).
 */

class clsUserListScreen : protected clsScreen
{
private:
    static void _printUserData(clsBankUser userData)
    {
        cout << setw(5) << left << "" << "| " << setw(17) << left << userData.getUserName();
        // string userPassword = clsBankUser::encryptPassword(userData.getPassword());
        // cout << "| " << setw(15) << left << userPassword;
        // cout << "| " << setw(15) << left << userData.getPassword();
        cout << "| " << setw(15) << left << "****";
        cout << "| " << setw(20) << left << userData.FullName();
        cout << "| " << setw(15) << left << userData.getPhone();
        cout << "| " << setw(27) << left << userData.getEmail();
        cout << "| " << setw(14) << left << userData.getAccessValue() << "|";
    }

public:
    static void showUsersList()
    {
        vector<clsBankUser> vUsers = clsBankUser::getListVectorFromFile(UsersDataFile);

        string title = "\t\tUsers List Screen";
        string subTitle = "\t\tUsers List (" + to_string(vUsers.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(5) << left << "" << "-------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(5) << left << "" << "| " << left << setw(17) << "UserName:";
        cout << "| " << left << setw(15) << "Password:";
        cout << "| " << left << setw(20) << "User FullName:";
        cout << "| " << left << setw(15) << "Phone:";
        cout << "| " << left << setw(27) << "Email:";
        cout << "| " << left << setw(15) << "Access Value: |" << endl;
        cout << setw(5) << left << "" << "-------------------------------------------------------------------------------------------------------------------------" << endl;

        if (vUsers.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsBankUser &user : vUsers)
        {
            _printUserData(user);
            cout << endl;
        }
        cout << setw(5) << left << "" << "-------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};
