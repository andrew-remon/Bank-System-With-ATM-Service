/**
 * @file clsMainScreen.h
 * @brief Declares the `clsMainScreen` class, which serves as the main entry point for navigation.
 *
 * ## Overview
 * The `clsMainScreen` class provides the central navigation menu
 * for the banking system. It dispatches user input to the
 * appropriate screen classes (clients, transactions, users, etc.).
 *
 * ## Key Responsibilities
 * - Display the Main Menu options.
 * - Handle input validation for menu choices.
 * - Enforce permissions for actions based on the logged-in user.
 * - Route the chosen action to the corresponding screen class.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` (UI header/formatting).
 * - **Uses:**
 *   - `clsInputValidation` — for reading menu input.
 *   - `clsEnums` — defines `enChoice`.
 *   - `clsBankUser` / `clsGlobal::currentUser` — to check permissions.
 *
 *  @note: we implement this header file to separate the logic code from the UI.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../../Utils/clsInputValidation.h"
#include "../Misc/clsScreen.h"
#include "../../Core/clsGlobal.h"
#include "../../Core/clsEnums.h"
using namespace std;

/**
 * @class clsMainScreen
 * @brief Provides the main menu for the banking system.
 *
 * ## Overview
 * The `clsMainScreen` class serves as the central navigation point of the system
 * after login. It presents the main menu options and allows the user to:
 * - Manage clients (list, add, delete, update, find).
 * - Perform transactions (deposit, withdraw, transfer, etc.).
 * - Access user management (list, add, delete, update, find).
 * - View login history records.
 * - Logout and return to the login screen.
 *
 * ## Methods
 * - `static void showMainMenu()` — Displays the main menu and processes input.
 *
 * ## Private Helpers
 * - `_readMainMenuChoice()` — Reads and validates the user’s main menu choice.
 * - `_performMainMenuChoice(enChoice)` — Executes the chosen operation (defined in `.cpp`).
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen`.
 * - **Uses:**
 *   - `clsBankUser` and `clsGlobal` for current user and permissions.
 *   - `clsLoginScreen` for returning to login after logout.
 *   - Client management screens (e.g., `clsClientListScreen`, `clsAddNewClientScreen`, etc.).
 *   - Transaction management (`clsTransactionScreen`).
 *   - User management (`clsUserScreen`).
 *   - Login records (`clsLoginListRecordScreen`).
 */
class clsMainScreen : protected clsScreen
{
private:
    /**
     * @brief Reads and validates the current(logged-in) user's main menu choice.
     *
     * @return short The validated menu option (between 1 and 9).
     *
     * ## Behavior
     * - Prompts the user to enter a choice.
     * - Validates that the choice is within range [1–9].
     * - Returns the chosen option for further processing.
     */
    static short _readMainMenuChoice()
    {
        cout << setw(31) << left << " " << "Choose What Do You Want to do? [1 to 9]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 9, "Enter a Number from 1 to 9");
        return choice;
    }

    /**
     * @brief Executes the selected main menu option.
     *
     * @param choice The chosen main menu option, represented by the enum class `enChoice`.
     *
     * ## Behavior
     * Dispatches the control flow by a switch case to the corresponding screen class:
     * - `enChoice::ShowClientList` → `clsClientListScreen::showClientsList()`
     * - `enChoice::AddNewClient` → `clsAddNewClientScreen::addNewClientScreen()`
     * - `enChoice::DeleteClient` → `clsDeleteClientScreen::deleteClientScreen()`
     * - `enChoice::UpdateClientInfo` → `clsUpdateClientScreen::updateClientScreen()`
     * - `enChoice::FindClient` → `clsFindClientScreen::findClientScreen()`
     * - `enChoice::Transactions` → `clsTransactionScreen::showTransactionsMenu()`
     * - `enChoice::ManageUsers` → `clsUserScreen::showUserMenu()`
     * - `enChoice::ShowLoginRecordsList` → `clsLoginListRecordScreen::showloginRecordsList()`
     * - `enChoice::LogOut` → Returns to login screen.
     *
     * @note Implemented in the `.cpp` file.
     */
    static void _performMainMenuChoice(enChoice choice);

public:
    /**
     * @brief Displays the Management Main Menu.
     *
     * ## Workflow
     * - Displays the screen header and main menu options.
     * - Reads the logged-in user's choice using `_readMainMenuChoice()`.
     * - Executes the chosen option via `_performMainMenuChoice()`.
     *
     * @note Acts as the entry point for all system operations/features.
     */
    static void showMainMenu();
};
