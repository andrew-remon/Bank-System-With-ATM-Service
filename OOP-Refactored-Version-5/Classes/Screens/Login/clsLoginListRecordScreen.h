/**
 * @file clsLoginListRecordScreen.h
 * @brief Defines the `clsLoginListRecordScreen` class for displaying user login history records.
 *
 * ## Overview
 * The `clsLoginListRecordScreen` class provides functionality to display a formatted list
 * of user login records that are stored in a log file. It inherits from `clsScreen`
 * to reuse the screen header formatting functionality.
 *
 * ### Key Features:
 * - Reads login history from the log file via `clsLoggedInUser`.
 * - Displays the login time, username, password (masked), and access value.
 * - Provides a user-friendly table layout for easy visualization.
 *
 * ### Relationships:
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 * - **uses**:
 *   - Standard C++ I/O and formatting utilities (`iostream`, `iomanip`) for aligned output.
 *   - `clsLoggedInUser.h` - for retrieving logged-in users records and deal with their info.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../Misc/clsScreen.h"
#include "clsLoggedInUser.h"
using namespace std;

/**
 * @class clsLoginListRecordScreen
 * @brief A screen class for displaying user login records in a tabular format.
 *
 * The class fetches login records using `clsLoggedInUser` and displays them neatly
 * in the console, with masked password fields for privacy.
 */
class clsLoginListRecordScreen : protected clsScreen
{
private:
    static void _printLoginRecordData(clsLoggedInUser loginRecord)
    {
        cout << setw(20) << left << "" << "| " << setw(30) << left << loginRecord.getLoginTimeRecord();
        // cout << "| " << setw(15) << left << loginRecord.getPassword();
        cout << "| " << setw(15) << left << "****";
        cout << "| " << setw(17) << left << loginRecord.getUserName();
        cout << "| " << setw(14) << left << loginRecord.getAccessValue() << "|";
    }

public:
    static void showloginRecordsList()
    {
        vector <clsLoggedInUser> vLoggedInUser = clsLoggedInUser::getLoginRecordVector(LoginRegisterFile);

        string title = "\tLogin Records List Screen";
        string subTitle = "\t      Users List (" + to_string(vLoggedInUser.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(20) << left << "" <<  "-------------------------------------------------------------------------------------" << endl;
        cout << setw(20) << left << "" << "| " << left << setw(30) << "Date/Time:" ;
        cout << "| " << left << setw(15) << "Password:";
        cout << "| " << left << setw(17) << "UserName:";
        cout << "| " << left << setw(15) << "Access Value: |" << endl;
        cout << setw(20) << left << "" << "-------------------------------------------------------------------------------------" << endl;

        if (vLoggedInUser.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsLoggedInUser & loggedUser : vLoggedInUser)
        {
            _printLoginRecordData(loggedUser);
            cout << endl;
        }
        cout << setw(20) << left << "" <<  "-------------------------------------------------------------------------------------" << endl;
    }
};
