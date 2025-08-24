/**
 * @file clsFindUserScreen.h
 * @brief Defines the `clsFindUserScreen` class for retrieving and displaying user information.
 *
 * ## Overview
 * The `clsFindUserScreen` class provides a screen interface to search for a
 * specific system user (bank staff) by their username. If the user exists,
 * their details are displayed in a formatted view.
 *
 * ## Key Responsibilities
 * - Display the "Find User Info Screen" header.
 * - Read a valid username from input.
 * - Search for the user in persistent storage.
 * - Show user details if the record exists.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for UI formatting and headers.
 * - **Uses:**
 *   - `clsBankUser` — for user lookup and validation.
 *   - `clsPrintPersonCard` — for displaying user details.
 *
 * ## Usage
 * Call `clsFindUserScreen::findUserScreen()` to display the
 * **user search screen** and retrieve details of an existing user.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankUser.h"
#include "../../Templates/clsFindEntityScreen.h"
using namespace std;

/**
 * @class clsFindUserScreen
 * @brief Provides the screen interface for searching users by username.
 *
 * ## Overview
 * Encapsulates the process of searching for a system user. Ensures
 * that the input username exists before displaying details.
 *
 * ## Responsibilities
 * - Load users from the database file.
 * - Accept a username and verify its existence.
 * - Display user details if found.
 *
 *  @note The current implementation only prints details if the user exists;
 *  it does not notify the user when no match is found.
 */
class clsFindUserScreen : protected clsFindEntityScreen<clsBankUser>
{
public:
    /**
     * @brief Displays the "Find User" screen and executes the search workflow.
     *
     * ## Workflow
     * - Loads all users from file.
     * - Displays the "Find User Info Screen" header.
     * - Prompts for a valid username.
     * - Searches for the corresponding user record.
     * - If found:
     *   - Prints a success message.
     *   - Displays user details via `clsPrintPersonCard::printUserInfo`.
     *
     * @note If the user is not found, no details are displayed.
     */
    static void findUserScreen()
    {
        findEntityScreen
        (
            ClientsDataFile,
            "\t Find User Info Screen",
            clsBankUser::readUserName,
            clsBankUser::findUser,
            clsPrintPersonCard::printUserInfo
        );
        // vector<clsBankUser> vUsers = clsBankUser::getListVectorFromFile(UsersDataFile);

        // _drawScreenHeader("\t Find User Info Screen");

        // string userName = clsBankUser::readUserName(enStatus::Exist);

        // clsBankUser userFound = clsBankUser::findUser(userName);

        // if (!userFound.isEmpty())
        // {
        //     cout << "\nUser is Found :)\n";
        //     clsPrintPersonCard::printUserInfo(userFound);
        // }
    }
};
