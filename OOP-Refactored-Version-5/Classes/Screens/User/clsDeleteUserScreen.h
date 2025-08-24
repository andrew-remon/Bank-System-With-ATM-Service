/**
 * @file clsDeleteUserScreen.h
 * @brief Defines the `clsDeleteUserScreen` class for deleting existing system users.
 *
 * ## Overview
 * The `clsDeleteUserScreen` class provides the user interface workflow
 * for removing a system user (bank staff) from the database. It ensures
 * that the user exists, confirms the deletion, and updates persistent storage.
 *
 * ## Key Responsibilities
 * - Display the "Delete User" screen header.
 * - Validate that the username exists.
 * - Print user details for confirmation.
 * - Prompt the operator to confirm deletion.
 * - Mark the user record as deleted and update the file.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — provides screen formatting and headers.
 * - **Uses:**
 *   - `clsBankUser` — for user data lookup, validation, deletion marking, and persistence.
 *   - `clsPrintPersonCard` — for displaying user details before deletion.
 *   - `clsUtil` — for confirmation prompt handling.
 *
 * ## Usage
 * Call `clsDeleteUserScreen::deleteUserScreen()` to initiate the
 * **user deletion workflow** in the system.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankUser.h"
#include "../../utils/clsUtil.h"
using namespace std;

/**
 * @class clsDeleteUserScreen
 * @brief Provides the user interface screen for deleting users.
 *
 * ## Overview
 * The class encapsulates the complete workflow of deleting a system user.
 * It ensures safe deletion by requiring confirmation and updating the
 * persistent data file.
 *
 * ## Responsibilities
 * - Load the current list of users from storage.
 * - Request an existing username for deletion.
 * - Display the user’s details before deletion.
 * - Confirm the deletion with the operator.
 * - Mark the user as deleted and save the changes.
 *
 *  @note This class modifies user data by marking and removing records,
 *  unlike other screen classes that may be read-only (e.g., user list).
 */
class clsDeleteUserScreen : protected clsScreen
{
public:
    /**
     * @brief Displays the "Delete User" screen and executes the deletion workflow.
     *
     * ## Workflow
     * - Loads all users from file.
     * - Displays the "Delete User Info Screen" header.
     * - Prompts for an existing username.
     * - Finds and displays the user record to be deleted.
     * - Asks the operator for confirmation.
     * - If confirmed:
     *   - Marks the user as deleted using `_markUserDeleteSign`.
     *   - Saves the updated user list to persistent storage.
     *   - Replaces the deleted object with an empty user.
     *   - Displays a success message.
     *
     * @note The deletion is logical (via marking), not necessarily
     *       a full removal of the record, depending on implementation.
     */
    static void deleteUserScreen()
    {
        vector<clsBankUser> vUsers = clsBankUser::getListVectorFromFile(UsersDataFile);

        _drawScreenHeader("\t Delete User Info Screen");

        string userName = clsBankUser::readUserName(enStatus::Exist);

        clsBankUser &userToBeDeleted = clsBankUser::findUserRef(userName, vUsers);

        clsPrintPersonCard::printUserInfo(userToBeDeleted);

        char ans = clsUtil::confirm("Are You Sure you want to delete this account date (Y/N)");

        if (tolower(ans) == 'y')
        {
            clsBankUser::_markUserDeleteSign(userToBeDeleted);
            clsBankUser::_saveUserDataIntoFile(UsersDataFile, vUsers);
            userToBeDeleted = clsBankUser::_getEmptyUserObject();
            cout << "\nUser Deleted Successfully." << endl;
        }
    }
};
