/**
 * @file clsAddNewUserScreen.h
 * @brief Defines the `clsAddNewUserScreen` class for adding new system users.
 *
 * ## Overview
 * The `clsAddNewUserScreen` class provides a screen that enables operators
 * to create and persist new system users (bank staff). It leverages the
 * generic `clsAddNewEntityScreen` template, which abstracts common
 * "add new entity" functionality to reduce code duplication.
 *
 * ## Key Responsibilities
 * - Display a screen for adding new user information.
 * - Read and validate a new username.
 * - Create a new `clsBankUser` object with initial values.
 * - Allow editing of user details.
 * - Save the new user into persistent storage.
 * - Display the newly added user’s details.
 *
 * ## Relationships
 * - **Inherits from:** `clsAddNewEntityScreen<clsBankUser>` — a generic template
 *   for adding new entities.
 * - **Uses:**
 *   - `clsBankUser` — for user data creation, validation, modification, and persistence.
 *   - `clsPrintPersonCard` — to display user details after creation.
 *   - `clsScreen` — indirectly (via template inheritance) for screen formatting.
 *
 * ## Usage
 * Call `clsAddNewUserScreen::addNewUserScreen()` to launch the
 * **"Add New User"** workflow in the system’s UI flow.
 */

#pragma once
#include <iostream>
// #include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Core/clsBankUser.h"
#include "../../Templates/clsAddNewEntityScreen.h"
using namespace std;

/**
 * @class clsAddNewUserScreen
 * @brief Provides the user interface screen for adding new users.
 *
 * ## Overview
 * This class is a specialization of the generic `clsAddNewEntityScreen<T>`
 * template, with `clsBankUser` as its entity type. It encapsulates the
 * workflow for creating new system users.
 *
 * ## Responsibilities
 * - Request and validate a new username.
 * - Create a new `clsBankUser` object with default/initial values.
 * - Allow modification of the user’s details before saving.
 * - Save the new user record to persistent storage.
 * - Print the new user’s information after successful creation.
 *
 * @note This class reduces code duplication by reusing the generic
 *       entity-creation workflow in `clsAddNewEntityScreen`.
 */
class clsAddNewUserScreen : protected clsAddNewEntityScreen<clsBankUser>
{
public:
    /**
     * @brief Displays the "Add New User" screen and executes the user creation workflow.
     *
     * ## Workflow
     * - Reads the list of existing users from file.
     * - Displays the "Add New User" header screen.
     * - Prompts for a new, unique username.
     * - Creates a new `clsBankUser` object for the provided username.
     * - Allows modification of the new user’s details.
     * - Saves the updated list of users into persistent storage.
     * - Prints the newly created user’s details.
     *
     * @note This method reuses the generic workflow provided by
     *       `clsAddNewEntityScreen<clsBankUser>` instead of duplicating code.
     */
    static void addNewUserScreen()
    {
        addNewEntityScreen
        (
            UsersDataFile,
            "\tAdd New User Info Scree",
            "\nUser Added Successfully.",
            clsBankUser::readUserName,
            clsBankUser::_getAddUserObject,
            clsBankUser::_changeUserRecord,
            clsBankUser::_saveUserDataIntoFile,
            clsPrintPersonCard::printUserInfo
        );

        //note: old implementation with repeated code.

        // vector <clsBankUser> vUsers = clsBankUser::getListVectorFromFile(UsersDataFile);

        // _drawScreenHeader("\tAdd New User Info Screen");

        // string userName = clsBankUser::readUserName(enStatus::New);

        // clsBankUser newUser = clsBankUser::_getAddUserObject(userName);

        // clsBankUser::_changeUserRecord(newUser);

        // newUser._mode = clsBankUser::enMode::UpdateMode;

        // vUsers.push_back(newUser);

        // clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);

        // cout << "\nUser Added Successfully." << endl;

        // clsPrintPersonCard::printUserInfo(newUser);
    }
};
