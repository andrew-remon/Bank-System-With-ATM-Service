/**
 * @file clsTransferListRecordScreen.h
 * @brief Defines the `clsTransferListRecordScreen` class for displaying transfer records in  a formatted screen view.
 *
 * ## Overview
 * The `clsTransferListRecordScreen` class provides functionality to:
 * - Display all transfer records retrieved from the transfer log file.
 * - Format and print transfer records with details such as:
 *   - Date/Time
 *   - Source Account Number
 *   - Destination Account Number
 *   - Transfer Amount
 *   - Source Account Balance
 *   - Destination Account Balance
 *   - Username that performed the transfer
 *
 * ## Key Responsibilities
 * - Load all transfer records from the data file into a vector.
 * - Display a screen header with a dynamic subtitle indicating the transfer records count.
 * - Print transfer details (source account number, destination account number, amount, source account balance, destination account balance, username)
 *   in a tabular format with proper column alignment.
 * - Handle the case when no transfer data exists in the system.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 * - Uses `clsTransferRecord` to access transfer record data.
 */
#pragma once
#include <iostream>
#include <iomanip>
#include "../Misc/clsScreen.h"
#include "clsTransferRecord.h"
using namespace std;

/**
 * @class clsTransferListRecordScreen
 * @brief Screen class for listing all transfer records in the system.
 *
 * This class retrieves transfer records from the transfer log file and
 * presents them in a formatted tabular style. It serves as a reporting
 * interface for administrators or users who want to view transaction history.
 */
class clsTransferListRecordScreen : protected clsScreen
{
private:
    static void _printTransferRecordData(clsTransferRecord transferRecord)
    {
        cout << setw(10) << left << "" << "| " << setw(20) << left << transferRecord.getLoginTimeRecord();
        cout << "| " << setw(16) << left << transferRecord.getSourceAccountNumber();
        cout << "| " << setw(16) << left << transferRecord.getDestinationAccountNumber();
        cout << "| " << setw(7) << left << transferRecord.getAmount();
        cout << "| " << setw(17) << left << transferRecord.getSourceAccountBalance();
        cout << "| " << setw(17) << left << transferRecord.getDestinationAccountBalance();
        cout << "| " << setw(12) << left << transferRecord.getUserName() << "|";
    }

public:
    static void showtransferRecordsList()
    {
        vector <clsTransferRecord> vTransfers = clsTransferRecord::getTransferRecordsVector(TransferLogsFile);

        string title = "\tTransfer Records List Screen";
        string subTitle = "\t      Transfers List (" + to_string(vTransfers.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(10) << left << "" <<  "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(10) << left << "" << "| " << left << setw(20) << "Date/Time:" ;
        cout << "| " << left << setw(16) << "S.AccountNumber";
        cout << "| " << left << setw(16) << "D.AccountNumber";
        cout << "| " << left << setw(7) << "Amount";
        cout << "| " << left << setw(17) << "S.AccountBalance";
        cout << "| " << left << setw(17) << "D.AccountBalance";
        cout << "| " << left << setw(17) << "UserName:   |" << endl;
        cout << setw(10) << left << "" << "------------------------------------------------------------------------------------------------------------------------" << endl;

        if (vTransfers.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsTransferRecord & transfer : vTransfers)
        {
            _printTransferRecordData(transfer);
            cout << endl;
        }
        cout << setw(10) << left << "" <<  "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};
