/**
 * @file clsWithdrawScreen.h
 * @brief Defines the `clsWithdrawScreen` class for handling withdrawal transactions in the banking system.
 *
 * ## Overview
 * The `clsWithdrawScreen` provides a user interface for withdrawing funds from a client’s account.
 * It ensures that the withdrawal amount does not exceed the current balance, updates the client record,
 * and saves the changes to persistent storage.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 *
 * - **Uses**:
 *  -`clsBankClient`:
 *   → Loads clients from the data file.
 *   → Validates that the account exists.
 *   → Retrieves and updates the client’s account balance.
 *
 *  -`clsPrintPersonCard`:
 *   → Displays the selected client’s details before proceeding with the withdrawal.
 *
 *  -`clsInputValidation`:
 *   → Ensures the withdrawal amount entered is a valid numeric value.
 *
 *  -`clsTransactionHelper`:
 *   → Executes the withdrawal operation (negative transaction) and persists updated records.
 *
 * ## Workflow
 * 1. Displays the withdrawal screen header.
 * 2. Loads the list of clients from file.
 * 3. Prompts for and validates an existing account number.
 * 4. Locates the client reference and displays client details.
 * 5. Reads and validates the withdrawal amount against available balance.
 * 6. Performs the withdrawal and updates records via `clsTransactionHelper`.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
#include "clsTransactionHelper.h"
using namespace std;

/**
 * @class clsWithdrawScreen
 * @brief Provides static methods to manage withdrawal operations in the banking system.
 *
 * This class handles the withdrawal process, ensuring input validation,
 * balance checks, and persistence of updated client data.
 */
class clsWithdrawScreen : protected clsScreen
{
public:
    /**
     * @brief Reads and validates a withdrawal amount for a client.
     *
     * Ensures that the entered withdrawal amount does not exceed the client's current balance.
     * Keeps prompting the user until a valid amount is entered.
     *
     * @param client The bank client whose balance is being checked.
     * @return double The validated withdrawal amount.
     */
    static double getValidWithdrawAmount(clsBankClient client)
    {
        double withdrawAmount;

        do
        {
            withdrawAmount = clsInputValidation::readDblNumber("Invalid Input, Please Enter A Valid Number.");

            if (withdrawAmount > client.getAccountBalance())
            {
                cout << "\nAmount Exceeds the balance, you can withdraw up to: " << client.getAccountBalance() << endl;
            }

        } while (withdrawAmount > client.getAccountBalance());
        return withdrawAmount;
    }

    /**
     * @brief Handles the full withdrawal workflow.
     *
     * - Draws the withdrawal screen header.
     * - Loads clients from file.
     * - Prompts for and validates account number.
     * - Displays client information.
     * - Validates and reads withdrawal amount.
     * - Updates client balance and saves data.
     */
    static void withdrawScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        _drawScreenHeader("\t\t Withdraw Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient &client = clsBankClient::findClientRef(accountNumber, vClients);
        clsPrintPersonCard::printClientInfo(client);

        double withdrawAmount = 0;

        cout << "Please enter Withdraw Amount? ";

        withdrawAmount = getValidWithdrawAmount(client);

        clsTransactionHelper::makeTransaction(-withdrawAmount, vClients, client);
    }
};
