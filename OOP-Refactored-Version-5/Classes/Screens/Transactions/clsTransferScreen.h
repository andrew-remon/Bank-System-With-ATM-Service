/**
 * @file clsTransferScreen.h
 * @brief Defines the `clsTransferScreen` class for handling money transfer operations between accounts.
 *
 * ## Overview
 * The `clsTransferScreen` class:
 * - Displays the transfer screen header.
 * - Prompts the user for source and destination account numbers.
 * - Validates accounts and displays their details.
 * - Reads and validates the transfer amount.
 * - Performs the transfer using `clsTransactionHelper`.
 * - Updates and displays account balances.
 * - Logs the transfer using `clsTransferLogger`.
 *
 * ## Relationships
 * - Inherits from **`clsScreen`** to use screen utilities like `_drawScreenHeader`.
 * - Uses **`clsBankClient`** to retrieve and manage client accounts.
 * - Uses **`clsPrintPersonCard`** to display client information before and after transfer.
 * - Uses **`clsWithdrawScreen`** for validating withdrawable amounts.
 * - Uses **`clsTransactionHelper`** to perform the actual transfer operation.
 * - Uses **`clsTransferLogger`** to record the transfer into a log file.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
#include "clsWithdrawScreen.h"
#include "clsTransactionHelper.h"
#include "clsTransferLogger.h"
using namespace std;

/**
 * @class clsTransferScreen
 * @brief Provides an interface for transferring money between two accounts.
 *
 * The `clsTransferScreen` is responsible for guiding the user through the transfer
 * process by:
 * 1. Selecting source and destination accounts.
 * 2. Ensuring the transfer amount is valid.
 * 3. Performing the transfer.
 * 4. Displaying updated balances.
 * 5. Logging the transfer operation.
 */
class clsTransferScreen : protected clsScreen
{
public:
    /**
     * @brief Displays the transfer screen and processes a money transfer.
     *
     * Workflow:
     * - Displays the "Transfer Screen" header.
     * - Reads the source account number and fetches account details.
     * - Reads the destination account number and fetches account details.
     * - Prompts for and validates a transfer amount (via `clsWithdrawScreen`).
     * - Executes the transfer using `clsTransactionHelper`.
     * - Prints updated account details for both accounts.
     * - Logs the transfer to a file (`Transfer.txt`) using `clsTransferLogger`.
     */
    static void transferScreen()
    {
        _drawScreenHeader("\t\t Transfer Screen");

        vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        cout << "Transfer From Account:- " << endl;
        string transferFromAccountNumber = clsBankClient::readAccountNumber(enStatus::Exist);
        clsBankClient &transferFromAccount = clsBankClient::findClientRef(transferFromAccountNumber, vClients);
        clsPrintPersonCard::printTransferClientInfo(transferFromAccount);

        cout << "Transfer To Account:- " << endl;
        string transferToAccountNumber = clsBankClient::readAccountNumber(enStatus::Exist);
        clsBankClient &transferToAccount = clsBankClient::findClientRef(transferToAccountNumber, vClients);
        clsPrintPersonCard::printTransferClientInfo(transferToAccount);

        double transferAmount = 0;

        cout << "Enter Transfer Amount: ";
        transferAmount = clsWithdrawScreen::getValidWithdrawAmount(transferFromAccount);

        clsTransactionHelper::transferAmountBetweenTwoAccounts(transferAmount, vClients, transferFromAccount, transferToAccount);

        clsPrintPersonCard::printTransferClientInfo(transferFromAccount);
        clsPrintPersonCard::printTransferClientInfo(transferToAccount);

        clsTransferLogger::registerTransferIntoFile("Transfer.txt", transferFromAccount, transferToAccount, transferAmount);
    }
};
