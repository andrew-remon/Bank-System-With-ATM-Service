/**
 * @file clsLoginLogger.h
 * @brief Declares the `clsLoginLogger` class for logging user login attempts.
 *
 * ## Overview
 * The `clsLoginLogger` class is responsible for recording login attempts
 * into a persistent log file. It captures information such as:
 * - Date and time of login
 * - Username
 * - Password
 * - Access rights level
 *
 * This logging mechanism is useful for auditing, monitoring security,
 * and troubleshooting unauthorized access attempts.
 *
 * ## Responsibilities
 * - Generate formatted login records from either:
 *   - A specified `clsBankUser` object, or
 *   - The global `currentUser`.
 * - Save login records into a text file.
 * - Provide static methods to register logins.
 *
 * ## Data Storage Format
 * Login Record Data is stored in a text file where each line represents login record.
 * Fields are separated by delimeter "#//#" in the following order:
 * ```
 * Timestamp#//#Username#//#Password#//#AccessValue
 * ```
 *
 * ## Relationships
 * - **Uses:**
 *   - `clsBankUser` for user information.
 *   - `clsDate` for timestamping login attempts.
 *   - `currentUser` (from global context) when no explicit user is passed.
 */

#pragma once
#include <iostream>
#include "../../Core/clsBankUser.h"
#include "../../Utils/clsDate.h"
using namespace std;

/**
 * @class clsLoginLogger
 * @brief Provides functionality for logging system login attempts.
 *
 * ## Overview
 * The `clsLoginLogger` class captures and stores user login information in a log file.
 * It works with both explicit `clsBankUser` objects and the global `currentUser`.
 *
 * ## Features
 * - Records the time of login.
 * - Records username, password, and access level.
 * - Supports appending logs to a file.
 * - Provides overloads for logging either a specific user or the current global user.
 *
 * ## Design
 * - **Static methods**: No object instantiation needed; logging is a system-level concern.
 * - **Encapsulation**: Helper methods are private, exposed only through `registerLoginIntoFile`.
 */
class clsLoginLogger
{
private:
    /**
     * @brief Builds a formatted login record string from a given user.
     *
     * ## Format
     * ```
     * [Timestamp]#//#[Username]#//#[Password]#//#[AccessValue]
     * ```
     *
     * @param userData The `clsBankUser` object to extract login data from.
     * @param sep Separator string (default = "#//#").
     * @return A formatted login record string.
     */
    static string _returnLoginRecordData(const clsBankUser & userData, string sep = "#//#")
    {
        string loginRecord = "";

        loginRecord += clsDate::TimeToString(clsDate()) + sep;
        loginRecord += userData.getUserName()   + sep;
        loginRecord += userData.getPassword()  + sep;
        loginRecord += to_string(userData.getAccessValue());

        return loginRecord;
    }

    /**
     * @brief Builds a formatted login record string from the global `currentUser`.
     *
     * @param sep Separator string (default = "#//#").
     * @return A formatted login record string.
     */
    static string _returnLoginRecordData(string sep = "#//#")
    {
        string loginRecord = "";

        loginRecord += clsDate::TimeToString(clsDate()) + sep;
        loginRecord += currentUser.getUserName()   + sep;
        loginRecord += currentUser.getPassword()  + sep;
        loginRecord += to_string(currentUser.getAccessValue());

        return loginRecord;
    }

    /**
     * @brief Saves a login record for a specific user into the log file.
     *
     * @param fileName The log file path/name.
     * @param userRecord The `clsBankUser` object whose login will be recorded.
     */
    static void _saveLoginRecordIntoFile(const string & fileName, const clsBankUser & userRecord)
    {
        fstream myFile;
        string loginRecord = _returnLoginRecordData(userRecord);

        myFile.open(fileName, ios::out|ios::app);

        if (myFile.is_open())
        {
            myFile << loginRecord << endl;
            myFile.close();
        }
    }

    /**
     * @brief Saves a login record for the global `currentUser` into the log file.
     *
     * @param fileName The log file path/name.
     */
    static void _saveLoginRecordIntoFile(const string & fileName)
    {
        fstream myFile;
        string loginRecord = _returnLoginRecordData();

        myFile.open(fileName, ios::out|ios::app);

        if (myFile.is_open())
        {
            myFile << loginRecord << endl;
            myFile.close();
        }
    }

public:

    /**
     * @brief Registers a login attempt into the log file for a specified user.
     *
     * @param fileName The log file path/name.
     * @param userRecord The user whose login data will be recorded.
     *
     * ## Example
     * ```cpp
     * clsBankUser user = clsBankUser::findUserRef("Admin");
     * clsLoginLogger::registerLoginIntoFile("Logins.txt", user);
     * ```
     */
    static void registerLoginIntoFile(const string & fileName, const clsBankUser & userRecord)
    {
        _saveLoginRecordIntoFile(fileName, userRecord);
    }

    /**
     * @brief Registers a login attempt into the log file for the global `currentUser`.
     *
     * @param fileName The log file path/name.
     */
    static void registerLoginIntoFile(const string & fileName)
    {
        _saveLoginRecordIntoFile(fileName);
    }
};
