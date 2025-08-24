/**
 * @file clsTransferRecord.h
 * @brief Defines the `clsTransferRecord` class for representing and managing bank transfer records.
 *
 * ## Overview
 * The `clsTransferRecord` class encapsulates the details of a single transfer operation,
 * including source and destination accounts, transfer amount, balances after transfer,
 * username of the operator, and timestamp.
 *
 * It also provides static helper methods for:
 * - Converting stored records into `clsTransferRecord` objects.
 * - Loading all transfer records from a file.
 * - Clearing the transfer record file.
 *
 * ## Relationships
 * - **Uses `clsString`:** for splitting record lines when reading from files.
 * - **Interacts with the filesystem:** (`fstream`) to persist transfer history.
 *
 * ## Key Responsibilities
 * - Store and expose transfer details through getters.
 * - Load transfer records from a text file into memory.
 * - Clear all transfer records when needed.
 */

#pragma once
#include <iostream>
#include <fstream>
#include "../../Utils/clsString.h"
using namespace std;

/**
 * @class clsTransferRecord
 * @brief Represents a single transfer record and provides utilities for persistence.
 *
 * This class acts as both a data container (holding transfer details) and a utility
 * for reading/writing transfer records to a file. It supports converting raw string
 * statements into structured objects and retrieving all records in memory for reporting.
 */
class clsTransferRecord
{
private:
    string _loginTimeRecord, _sourceAccountNumber, _destinationAccountNumber, _userName;
    float _amount, _sourceAccountBalance, _destinationAccountBalance;

    /**
     * @brief Converts a serialized transfer record string into a `clsTransferRecord` object.
     *
     * @param statement The serialized transfer record (fields separated by `sep`).
     * @param sep The delimiter used to split fields. Defaults to "#//#".
     * @return clsTransferRecord A structured transfer record object.
     */
    static clsTransferRecord _convertTransferRecordIntoObject(string statement, string sep = "#//#")
    {
        vector <string> vTransferRecord;

        clsString::split(statement, vTransferRecord, sep);

        return clsTransferRecord(vTransferRecord[0], vTransferRecord[1], vTransferRecord[2], stof(vTransferRecord[3]), stof(vTransferRecord[4]), stof(vTransferRecord[5]), vTransferRecord[6]);
    }

    /**
     * @brief Loads all transfer records from a file into a vector.
     *
     * Reads the specified file line by line, converts each line into a `clsTransferRecord`,
     * and stores them in a vector.
     *
     * @param fileName The file containing transfer records.
     * @return vector<clsTransferRecord> A vector of transfer records loaded from the file.
     */
    static vector <clsTransferRecord> _loadTransferRecordFileIntoVector(string fileName)
    {
        vector <clsTransferRecord> vTransfers;

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line;

            while(getline(myFile, line))
            {
                clsTransferRecord transferRecord = _convertTransferRecordIntoObject(line);

                vTransfers.push_back(transferRecord);
            }
            myFile.close();
        }

        return vTransfers;
    }

public:

    /**
     * @brief Constructs a new `clsTransferRecord`.
     *
     * @param loginTimeRecord The timestamp of the transfer.
     * @param sourceAccountNumber The account number of the sender.
     * @param destinationAccountNumber The account number of the receiver.
     * @param amount The amount transferred.
     * @param sourceAccountBalance The sender's balance after transfer.
     * @param destinationAccountBalance The receiver's balance after transfer.
     * @param userName The username of the operator who performed the transfer.
     */
    clsTransferRecord(string loginTimeRecord, string sourceAccountNumber, string destinationAccountNumber, float amount, float sourceAccountBalance, float destinationAccountBalance, string userName)
    {
        _loginTimeRecord = loginTimeRecord;
        _sourceAccountBalance = sourceAccountBalance;
        _destinationAccountBalance = destinationAccountBalance;
        _sourceAccountNumber = sourceAccountNumber;
        _destinationAccountNumber = destinationAccountNumber;
        _amount = amount;
        _userName = userName;
    }

    /**
     * @brief Gets the source account number.
     * @return string The source account number.
     */
    string getSourceAccountNumber()
    {
        return _sourceAccountNumber;
    }

    /**
     * @brief Gets the balance of the source account after the transfer.
     * @return float The source account balance.
     */
    float getSourceAccountBalance()
    {
        return _sourceAccountBalance;
    }

    /**
     * @brief Gets the destination account number.
     * @return string The destination account number.
     */

    string getDestinationAccountNumber()
    {
        return _destinationAccountNumber;
    }

    /**
     * @brief Gets the balance of the destination account after the transfer.
     * @return float The destination account balance.
     */
    float getDestinationAccountBalance()
    {
        return _destinationAccountBalance;
    }

    /**
     * @brief Gets the transfer amount.
     * @return float The transfer amount.
     */
    float getAmount()
    {
        return _amount;
    }

    /**
     * @brief Gets the login time (timestamp) of the transfer record.
     * @return string The transfer timestamp.
     */
    string getLoginTimeRecord()
    {
        return _loginTimeRecord;
    }

    /**
     * @brief Gets the username of the operator who executed the transfer.
     * @return string The username.
     */
    string getUserName()
    {
        return _userName;
    }


    /**
     * @brief Loads all transfer records from a given file into a vector.
     *
     * @param fileName The file containing transfer records.
     * @return vector<clsTransferRecord> A vector of transfer record objects.
     */
    static vector <clsTransferRecord> getTransferRecordsVector(string fileName)
    {
        return _loadTransferRecordFileIntoVector(fileName);
    }

    /**
     * @brief Clears all transfer records from the given file.
     *
     * @param fileName The file containing transfer records.
     */
    static void clearAllTransferRecords(string fileName)
    {
        fstream myFile(fileName, ios::out);
        myFile.close();
    }

};

