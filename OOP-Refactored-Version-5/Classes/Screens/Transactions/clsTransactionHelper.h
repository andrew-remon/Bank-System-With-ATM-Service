/**
 * @file clsTransactionHelper.h
 * @brief Provides helper functions for executing and persisting financial transactions.
 *
 * ## Overview
 * The `clsTransactionHelper` class centralizes the logic for handling transactions
 * such as deposits, withdrawals, and transfers between client accounts.
 * It ensures confirmation from the user before applying changes, updates account balances,
 * and persists updated client records to the storage file.
 *
 * ## Relationships
 * - **Uses `clsUtil`:**
 *   → Provides confirmation prompts before performing critical financial operations.
 *
 * - **Uses `clsBankClient`:**
 *   → Updates account balances for clients.
 *   → Saves updated records into persistent storage.
 *
 * ## Key Responsibilities
 * - Process single-account transactions (deposit/withdraw).
 * - Process transfers between two accounts.
 * - Ensure user confirmation before committing changes.
 * - Persist updated client data to the designated storage file.
 */

#pragma once
#include <iostream>
#include "../../Utils/clsUtil.h"
#include "../../Core/clsBankClient.h"

/**
 * @class clsTransactionHelper
 * @brief A utility class that provides static methods to execute financial transactions.
 *
 * The class prevents code duplication across multiple transaction screens
 * (e.g., deposit, withdrawal, transfer) by providing centralized methods
 * for balance updates and file persistence.
 */
class clsTransactionHelper
{
public:
    /**
     * @brief Executes a deposit or withdrawal transaction for a client.
     *
     * Prompts the user for confirmation before applying the transaction.
     * If confirmed, updates the client’s account balance and persists
     * the updated list of clients to the storage file.
     *
     * @param amount The transaction amount (positive for deposit, negative for withdrawal).
     * @param vClients Reference to the list of all bank clients.
     * @param client Reference to the client whose account is affected.
     */
    static void makeTransaction(double amount, vector <clsBankClient> & vClients, clsBankClient & client)
    {
        char ans = clsUtil::confirm("Are you sure you want to perform this transaction? (Y/N) ");

        if (tolower(ans) == 'y')
        {
            client.updateAccBalance(amount);
            clsBankClient::saveClientDataIntoFile(ClientsDataFile, vClients);
            cout << "Done Successfully, New Account Total Balance: " << client.getAccountBalance() << endl;
        }
    }

    /**
     * @brief Executes a transfer transaction between two clients.
     *
     * Prompts the user for confirmation before applying the transfer.
     * If confirmed, deducts the transfer amount from the source client’s balance,
     * adds it to the destination client’s balance, and persists updated records.
     *
     * @param amount The amount to transfer.
     * @param vClients Reference to the list of all bank clients.
     * @param sourceClient Reference to the client sending money.
     * @param destinationClient Reference to the client receiving money.
     */
    static void transferAmountBetweenTwoAccounts(double amount, vector <clsBankClient> & vClients, clsBankClient & sourceClient, clsBankClient & destinationClient)
    {
        char ans = clsUtil::confirm("Are you sure you want to perform this transaction? (Y/N) ");

        if (tolower(ans) == 'y')
        {
            sourceClient.updateAccBalance(-amount);
            destinationClient.updateAccBalance(+amount);
            clsBankClient::saveClientDataIntoFile(ClientsDataFile, vClients);
            cout << "\nTransfer Done Successfully." << endl;
        }
    }
};
