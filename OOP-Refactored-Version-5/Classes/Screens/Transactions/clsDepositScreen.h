/**
 * @file clsDepositScreen.h
 * @brief Defines the `clsDepositScreen` class for handling deposit transactions in the banking system.
 *
 * ### Overview
 * The `clsDepositScreen` provides a UI flow for depositing funds into a bank account.
 * It allows the user to select an account, enter a deposit amount, and update the balance.
 *
 * ### Relationships
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 *
 * - **Uses**:
 *   -`clsBankClient`:**
 *   → Loads all clients from the data file.
 *   → Finds a client by account number.
 *   → Holds the client reference for updating balance.
 * 
 *   -`clsPrintPersonCard`:
 *   → Displays client information before performing the transaction.
 *
 *   - **Uses `clsInputValidation`:
 *   → Validates the deposit amount entered by the user.
 *
 *   - **Uses `clsTransactionHelper`:
 *   → Applies the deposit operation and ensures data persistence in the client file.
 *
 * ## Workflow
 * 1. Displays the deposit screen header.
 * 2. Loads all clients from the database file.
 * 3. Reads and validates the target account number.
 * 4. Locates the client object by reference.
 * 5. Displays client information.
 * 6. Reads and validates the deposit amount.
 * 7. Processes the transaction and updates the client’s balance.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "clsTransactionHelper.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
using namespace std;

/**
 * @class clsDepositScreen
 * @brief Provides the interface for depositing money into a client’s account.
 *
 * Inherits from `clsScreen` to reuse standard screen drawing utilities.
 * Uses helper classes (`clsTransactionHelper`, `clsPrintPersonCard`, and `clsInputValidation`)
 * to manage deposit functionality.
 */
class clsDepositScreen : protected clsScreen
{
public:
    /**
     * @brief Displays the deposit screen and processes a deposit transaction.
     *
     * ### Steps:
     * 1. Displays the deposit screen header.
     * 2. Loads all clients from the `ClientsDataFile`.
     * 3. Reads and validates the account number to ensure it exists.
     * 4. Retrieves the matching client object by reference.
     * 5. Prints the client’s information on the screen.
     * 6. Prompts the user to enter a deposit amount, validating input.
     * 7. Calls `clsTransactionHelper::makeTransaction` to apply the deposit and save changes.
     *
     * @note The account balance is updated directly within the `vClients` vector,
     *       ensuring persistence when saved by `makeTransaction`.
     */
    static void depositScreen()
    {
        _drawScreenHeader("\t\t Deposit Screen");

        vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient &client = clsBankClient::findClientRef(accountNumber, vClients);
        clsPrintPersonCard::printClientInfo(client);

        cout << "\n\nPlease enter Deposit Amount? ";
        double depositAmount = clsInputValidation::readDblNumber("Invalid Input, Please Enter A Valid Number.");

        clsTransactionHelper::makeTransaction(depositAmount, vClients, client);
    }
};
