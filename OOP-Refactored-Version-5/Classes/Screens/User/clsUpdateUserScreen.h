/**
 * @file clsUpdateUserScreen.h
 * @brief Defines the `clsUpdateUserScreen` class for modifying existing user information.
 *
 * ## Overview
 * The `clsUpdateUserScreen` class provides a screen interface for updating
 * system users (bank staff). It ensures that only valid users can be updated
 * and enforces restrictions (e.g., the built-in Admin account cannot be modified).
 *
 * ## Key Responsibilities
 * - Display the "Update User Info Screen" header.
 * - Validate and locate the user record.
 * - Prevent updates to restricted accounts (e.g., Admin).
 * - Allow user details to be modified and saved back to file.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for screen formatting and headers.
 * - **Uses:**
 *   - `clsBankUser` — for user validation, editing, and saving.
 *   - `clsPrintPersonCard` — for displaying user details.
 *   - `clsUtil` — for confirmation prompts.
 *
 * ## Usage
 * Call `clsUpdateUserScreen::updateUserScreen()` to launch the update
 * process for an existing user.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankUser.h"
#include "../../Templates/clsUpdateEntityScreen.h"
using namespace std;

/**
 * @class clsUpdateUserScreen
 * @brief Provides the screen interface for updating user records.
 *
 * ## Overview
 * Encapsulates the workflow for modifying existing user data. Ensures
 * that sensitive accounts (like Admin) cannot be altered.
 *
 * ## Responsibilities
 * - Load users from persistent storage.
 * - Verify the target user exists.
 * - Disallow updates to restricted accounts.
 * - Update user details and persist changes.
 *
 * @note Updates only succeed if the user object is in `UpdateMode`.
 */
class clsUpdateUserScreen : protected clsUpdateEntityScreen<clsBankUser>
{
public:
    /**
     * @brief Displays the "Update User" screen and executes the update workflow.
     *
     * ## Workflow
     * - Loads all users from file.
     * - Displays the "Update User Info Screen" header.
     * - Prompts for an existing username.
     * - Restricts update if the username is `"Admin"`.
     * - If valid:
     *   - Confirms whether the update should proceed.
     *   - Calls `_changeUserRecord()` to allow modifications.
     *   - Saves updated user data to file.
     *   - Displays the updated record.
     *
     * @note If the user object is empty or invalid, the update fails.
     * @warning The built-in Admin account cannot be modified.
     */
    static void updateUserScreen()
    {
        updateEntityScreen
        (
            UsersDataFile,
            "\tUpdate User Info Screen",
            "\nUser Updated Successfully.\n",
            clsBankUser::readUserName,
            clsBankUser::findUserRef,
            clsPrintPersonCard::printUserInfo,
            clsBankUser::_changeUserRecord,
            clsBankUser::_saveUserDataIntoFile
        );
        // vector<clsBankUser> vUsers = clsBankUser::getListVectorFromFile(UsersDataFile);

        // _drawScreenHeader("\tUpdate User Info Screen");

        // string userName = clsBankUser::readUserName(enStatus::Exist);

        // if (userName == "admin")
        // {
        //     cout << "\nThis User Can't Be Updated, Please Contact The Admin For More Information.";
        //     return;
        // }

        // clsBankUser &userToBeUpdated = clsBankUser::findUserRef(userName, vUsers);

        // clsPrintPersonCard::printUserInfo(userToBeUpdated);

        // char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        // if (tolower(ans) == 'y')
        // {
        //     if (userToBeUpdated._mode == clsBankUser::enMode::UpdateMode)
        //     {
        //         clsBankUser::_changeUserRecord(userToBeUpdated);

        //         clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);

        //         cout << "\nUser Updated Successfully." << endl;

        //         clsPrintPersonCard::printUserInfo(userToBeUpdated);
        //     }
        //     else
        //         cout << "\nUpdate Failed, It's an empty object.";
        // }
    }
};
