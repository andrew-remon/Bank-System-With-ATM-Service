/**
 * @file clsTransactionScreen.h
 * @brief Declares the `clsTransactionScreen` class for displaying and handling the transactions menu.
 *
 * ## Overview
 * The `clsTransactionScreen` class provides an interactive screen that allows
 * users to choose between different transaction-related operations such as:
 * - Depositing into an account
 * - Withdrawing from an account
 * - Viewing total balances
 * - Transferring between accounts
 * - Viewing transfer records
 * - Returning to the main menu
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 *
 * - **Collaborates with:**
 *   - `clsDepositScreen` → Handles deposit operations.
 *   - `clsWithdrawScreen` → Handles withdrawals.
 *   - `clsTransferScreen` → Handles transfers between accounts.
 *   - `clsTransferListRecordScreen` → Displays a list of transfer records.
 *   - `clsBankClient` → Provides balance overview and client data handling.
 *   - `clsMainScreen` → Allows navigation back to the main menu.
 *
 * ## Key Responsibilities
 * - Present the user with a transaction menu.
 * - Validate user choice using `clsInputValidation`.
 * - Redirect the flow to the correct screen based on the choice.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsEnums.h"
#include "../Misc/clsScreen.h"
using namespace std;

/**
 * @class clsTransactionScreen
 * @brief Manages the transaction menu and routes user choices to appropriate transaction screens.
 *
 * This class is a high-level dispatcher for transaction-related operations.
 * It isolates menu handling and decision-making from the actual business logic,
 * which resides in specialized screens like `clsDepositScreen` or `clsWithdrawScreen`.
 */
class clsTransactionScreen : protected clsScreen
{
private:
    /**
     * @brief Reads and validates the user's transaction menu choice.
     *
     * Displays a prompt and ensures the choice is within the valid range (1–6).
     *
     * @return short The validated transaction choice.
     */
    static short _readTransactionsChoice()
    {
        cout << setw(30) << "" << "Choose What Do You Want to do? [1 to 6]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 6, "Choose a number between 1 and 6");
        return choice;
    }

    /**
     * @brief Executes the transaction screen corresponding to the given choice.
     *
     * Uses a switch-case to dispatch the flow to the correct screen:
     * - Deposit
     * - Withdraw
     * - Total Balances
     * - Transfer
     * - Transfer Records List
     * - Main Menu
     *
     * @param transactionChoice The transaction option chosen by the user.
     */
    static void _performTransactionsChoice(enTransactionChoice transactionChoice);

public:
    /**
     * @brief Displays the transactions menu to the user.
     *
     * Prints the available transaction options, validates the user’s input,
     * and invokes `_performTransactionsChoice()` to handle the selection.
     */
    static void showTransactionsMenu();

};
