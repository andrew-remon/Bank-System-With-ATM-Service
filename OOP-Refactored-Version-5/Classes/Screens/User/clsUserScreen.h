/**
 * @file clsUserScreen.h
 * @brief Declares the `clsUserScreen` class, which provides the User Management Menu.
 *
 * ## Overview
 * The `clsUserScreen` class implements a submenu for user management
 * operations such as listing, adding, deleting, updating, and finding users.
 *
 * ## Key Responsibilities
 * - Display the User Menu options.
 * - Handle input validation for menu choices.
 * - Dispatch user actions to the appropriate screen classes.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` (for consistent UI header/formatting).
 * - **Uses:**
 *   - `clsInputValidation` — to validate user input.
 *   - `clsEnums` — defines `enUserChoice`.
 *   - `clsBankUser` — user data source.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../Misc/clsScreen.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsEnums.h"
#include "../../Core/clsGlobal.h"
using namespace std;

/**
 * @class clsUserScreen
 * @brief Provides a submenu for managing system users.
 *
 * ## Overview
 * The `clsUserScreen` class encapsulates the functionality to display and handle
 * user management options. It allows the user to:
 * - Show all users
 * - Add a new user
 * - Delete an existing user
 * - Update user information
 * - Find a user by username
 * - Return to the main menu
 *
 * ## Methods
 * - `static void showUserMenu()` — Displays the user menu and processes input.
 *
 * ## Private Helpers
 * - `_readUserChoice()` — Reads and validates the user's menu choice.
 * - `_performUserChoice(enUserChoice)` — Executes the chosen operation (defined in `.cpp`).
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen`.
 * - **Uses:** Other user management screen classes for operation-specific tasks.
 */
class clsUserScreen : protected clsScreen
{
private:
    /**
     * @brief Reads and validates the user's menu choice.
     *
     * @return short The validated menu option (between 1 and 6).
     *
     * ## Behavior
     * - Prompts the user to enter a choice.
     * - Validates that the choice is within range [1–6].
     * - Returns the chosen option for further processing.
     */
    static short _readUserChoice()
    {
        cout << setw(30) << "" << "Choose What Do You Want to do? [1 to 6]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 6, "please enter a number between 1 and 6");
        return choice;
    }

    /**
     * @brief Executes the selected user menu option.
     *
     * @param userChoice The chosen menu option, represented by the enum class `enUserChoice`.
     *
     * ## Behavior
     * Dispatches the control flow to the corresponding screen class:
     * - `enUserChoice::ShowUserList` → `clsUserListScreen::showUsersList()`
     * - `enUserChoice::AddNewUser` → `clsAddNewUserScreen::showAddNewUser()`
     * - `enUserChoice::DeleteUser` → `clsDeleteUserScreen::showDeleteUser()`
     * - `enUserChoice::UpdateUserInfo` → `clsUpdateUserScreen::updateUserScreen()`
     * - `enUserChoice::FindUser` → `clsFindUserScreen::findUserScreen()`
     * - `enUserChoice::MainMenu` → Returns to main menu.
     *
     * @note Implemented in the `.cpp` file.
     */
    static void _performUserChoice(enUserChoice userChoice);

public:
    /**
     * @brief Displays the User Management Menu.
     *
     * ## Workflow
     * - Displays the screen header and user menu options.
     * - Reads the user's choice using `_readUserChoice()`.
     * - Executes the chosen option via `_performUserChoice()`.
     *
     * @note Acts as the entry point for all user-related operations.
     */
    static void showUserMenu();
};
