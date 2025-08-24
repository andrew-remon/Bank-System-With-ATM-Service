/**
 * @file clsLoggedInUser.h
 * @brief Declares the `clsLoggedInUser` class for representing and managing login history.
 *
 * ## Overview
 * The `clsLoggedInUser` class represents a single login record and provides
 * functionality to:
 * - Parse login records from a log file
 * - Convert log entries into structured objects
 * - Retrieve all login records as a vector
 * - Clear all login records
 *
 * ## Responsibilities
 * - Encapsulate user login details (username, password, access level, timestamp).
 * - Serve as a data model for login history entries.
 * - Provide utility methods for working with login record files.
 *
 * ## Relationships
 * - **Uses**:
 *   - `clsString` for string splitting.
 *   - `clsUtil` (not directly here but part of utilities).
 *   - Standard I/O and file stream operations (`<fstream>`).
 */

#pragma once
#include <iostream>
#include <fstream>
#include "../../Utils/clsString.h"
#include "../../Utils/clsUtil.h"
using namespace std;

/**
 * @class clsLoggedInUser
 * @brief Represents a single login record and provides utilities to manage login history.
 *
 * ## Overview
 * Each `clsLoggedInUser` object corresponds to a login record, containing:
 * - Login timestamp
 * - Username
 * - Password
 * - Access level
 *
 * The class also provides static methods to load records from a file,
 * clear records, and represent the login history as a collection of objects.
 *
 * ## Design
 * - **Data encapsulation**: private fields with public getters.
 * - **Utility functions**: private static helpers to convert between file records and objects.
 * - **Stateless operations**: most methods are `static` since login history
 *   is a global system resource.
 */
class clsLoggedInUser
{
private:
    string _userName, _password, _loginTimeRecord;
    short _accessValue;

    /**
     * @brief Converts a string login record into a `clsLoggedInUser` object.
     *
     * @param statement The raw log record string.
     * @param sep Separator string (default = "#//#").
     * @return A `clsLoggedInUser` object populated with parsed data.
     */
    static clsLoggedInUser _convertLoginRecordIntoUserObject(string statement, string sep = "#//#")
    {
        vector <string> vUserDate;

        clsString::split(statement, vUserDate, sep);

        return clsLoggedInUser(vUserDate[0], vUserDate[1], vUserDate[2], stod(vUserDate[3]));
    }

    /**
     * @brief Loads all login records from a file into a vector of `clsLoggedInUser` objects.
     *
     * @param fileName The log file path/name.
     * @return A vector of `clsLoggedInUser` objects.
     *
     * ## Behavior
     * - Reads line by line.
     * - Converts each line using `_convertLoginRecordIntoUserObject`.
     * - Skips empty files safely.
     */
    static vector <clsLoggedInUser> _loadLoginRecordFileIntoVector(string fileName)
    {
        vector <clsLoggedInUser> vUsers;

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line;

            while(getline(myFile, line))
            {
                clsLoggedInUser user = _convertLoginRecordIntoUserObject(line);

                vUsers.push_back(user);
            }
            myFile.close();
        }

        return vUsers;
    }

public:

    /**
     * @brief Constructs a `clsLoggedInUser` object with login details.
     *
     * @param loginTimeRecord The timestamp of login.
     * @param userName Username used.
     * @param password Password used.
     * @param accessValue User’s access level.
     */
    clsLoggedInUser(string loginTimeRecord, string userName, string password, short accessValue)
    {
        _userName = userName;
        _password = password;
        _accessValue = accessValue;
        _loginTimeRecord = loginTimeRecord;
    }

    /**
     * @brief Gets the user’s password.
     * @return Password as a string.
     */
    string getPassword()
    {
        return _password;
    }

    /**
     * @brief Gets the user’s username.
     * @return Username as a string.
     */
    string getUserName()
    {
        return _userName;
    }

    /**
     * @brief Gets the user’s access value (role/permissions).
     * @return Access value as a short integer.
     */
    short getAccessValue()
    {
        return _accessValue;
    }

    /**
     * @brief Gets the timestamp of the login attempt.
     * @return Timestamp string.
     */
    string getLoginTimeRecord()
    {
        return _loginTimeRecord;
    }

    /**
     * @brief Retrieves all login records from a file into a vector.
     *
     * @param fileName The log file path/name.
     * @return Vector of `clsLoggedInUser` objects.
     */
    static vector <clsLoggedInUser> getLoginRecordVector(string fileName)
    {
        return _loadLoginRecordFileIntoVector(fileName);
    }

    /**
     * @brief Clears all login records from the specified file.
     *
     * @param fileName The log file path/name.
     *
     * ## Example
     * ```cpp
     * clsLoggedInUser::clearAllLoginRecords("Logins.txt");
     * ```
     */
    static void clearAllLoginRecords(string fileName)
    {
        fstream myFile(fileName, ios::out);
        myFile.close();
    }
};

