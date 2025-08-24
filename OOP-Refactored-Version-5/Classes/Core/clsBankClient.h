/**
 * @file clsBankClient.h
 * @brief Defines the `clsBankClient` class for managing bank client data.
 *
 * ## Overview
 * The `clsBankClient` class represents a single bank client's information and provides
 * methods for creating, retrieving, updating, deleting, and persisting client records
 * to and from a file. It extends `clsPerson` to include additional banking-related
 * properties such as account number, PIN code, and account balance.
 *
 * This class implements both:
 * - **Instance-level operations** (e.g., printing details, updating a client's own data).
 * - **Static-level operations** (e.g., loading all clients from file, finding a client by account number).
 *
 * ## Key Responsibilities
 * - Encapsulates client details (personal info + bank account data).
 * - Reads and writes client data to text files with a defined serialization format.
 * - Supports creating new clients, updating existing ones, and marking clients as deleted.
 * - Provides validation helpers for ensuring account number uniqueness or existence.
 * - Supports balance calculations and formatted listing of all clients.
 *
 * ## Data Storage Format
 * Client data is stored in a text file where each line represents a single client record.
 * Fields are separated by the delimiter `#//#` in the following order:
 * ```
 * FirstName#//#LastName#//#Email#//#Phone#//#PinCode#//#AccountNumber#//#AccountBalance
 * ```
 *
 * ## Relationships
 * - **Inherits from:** `clsPerson` — for basic identity and contact details.
 * - **Uses utilities:**
 *   - `clsString` — string splitting for serialization/deserialization.
 *   - `clsInputValidation` — validated user input for updating/creating records.
 *   - `clsUtil` — helper utilities (confirmation prompts, number-to-text conversion).
 * - **Friend Classes:**
 *   - `clsAddNewClientScreen`
 *   - `clsDeleteClientScreen`
 *   - `clsUpdateClientScreen`
 *   These screens can directly manipulate client data members.
 *
 * ## Notable Implementation Details
 * - Uses an internal `enMode` enum to track object state (Empty, Update, Add).
 * - Deletion is handled via a `_deleteSign` flag; deleted clients are skipped when saving.
 * - All getters for immutable data members are `const` so they can be called on const objects.
 * - Most static functions work on collections (`vector<clsBankClient>`) representing all loaded clients.
 * - `calculateTotalBalances()` sums balances of all clients.
 * - Account number input can be validated for uniqueness or existence using `readAccountNumber()`.
 *
 * @note This class is tightly coupled with file-based storage;
 *  future modifications may be needed to support database storage.
 */
#pragma once
#include <iostream>
#include <vector>
#include "clsPerson.h"
#include "clsEnums.h"
using namespace std;

/**
 * @class clsBankClient
 * @brief Represents a Client in the banking system.
 *
 * This class stores account number, pincode and account balance.
 * it provides core operations such as updating, deleting, finding and saving client information.
 *
 * Inherits:
 * - clsPerson (to manage general personal information)
 */
class clsBankClient : public clsPerson
{
private:

    enMode _mode;
    string _pinCode;
    string _accountNumber;
    double  _accountBalance;
    bool   _deleteSign = false;

    /**
     * @brief Convert a delimited string into a clsBankClient object.
     *
     * Splits a line of text into individual fields using the provided separator
     * and constructs a clsBankClient object in UpdateMode with the extracted data.
     *
     * @param line The serialized client data as a single string.
     * @param separator The delimiter used to split the string (default: "#//#").
     * @return A clsBankClient object with the parsed data.
     */
    static clsBankClient _convertLineIntoClientObject(const string& line, string separator = "#//#");

    /**
     * @brief Load client data from a file into a vector of clsBankClient objects.
     *
     * Opens the specified file, reads each line, converts it into a clsBankClient
     * object using _convertLineIntoClientObject(), and stores it in a vector.
     *
     * @param fileName The name of the file containing serialized client data.
     * @return A vector of clsBankClient objects loaded from the file.
     */
    static vector <clsBankClient> _loadDataFileIntoVector(const string& fileName);

    /**
     * @brief Create an empty clsBankClient object.
     *
     * Returns a clsBankClient in EmptyMode with all string fields empty and balance set to 0.
     *
     * @return An empty clsBankClient object.
     */
    static clsBankClient _getEmptyClientObject();

    /**
     * @brief Create a new clsBankClient object for adding a client.
     *
     * Returns a clsBankClient in AddMode with an empty profile except for the account number.
     *
     * @param accountNumber The account number to assign to the new client.
     * @return A clsBankClient object prepared for adding a new client.
     */
    static clsBankClient _getAddClientObject(const string& accountNumber);

    /**
     * @brief Convert a clsBankClient object into a serialized string.
     *
     * Joins all client fields into a single string separated by the specified separator.
     *
     * @param clientData The clsBankClient object to serialize.
     * @param sep The delimiter to use between fields (default: "#//#").
     * @return A serialized string representing the client.
     */
    static string _returnClientData(const clsBankClient& clientData, string sep = "#//#");

    /**
     * @brief Save client data from a vector into a file.
     *
     * Writes serialized client data into the specified file, excluding clients
     * marked with the delete sign.
     *
     * @param fileName The name of the file to write data into.
     * @param vClients The vector of clsBankClient objects to save.
     */
    static void _saveClientDataIntoFile(const string& fileName, const vector <clsBankClient> & vClients);

    /**
     * @brief Prompt the user to update all personal and account information of a client.
     *
     * This function modifies the provided client object directly by reference.
     * It updates the first name, last name, email, phone number, PIN code,
     * and account balance based on user input.
     *
     * @param client Reference to The client object to update.
     */
    static void _setClientInfo(clsBankClient & client);

    /**
     * @brief Modify a client's record by searching for their account number.
     *
     * Finds a client in the given vector by account number and prompts the user
     * to update their personal details and account balance.
     *
     * @param accountNumber The account number of the client to update.
     * @param vClients The vector of clients in which to search and update.
     */
    static void _changeClientRecord(const string& accountNumber, vector <clsBankClient> & vClients);

    /**
     * @brief Modify the details of a given clsBankClient object.
     *
     * Prompts the user for updated client information including name, contact info,
     * PIN code, and account balance, then updates the object directly.
     *
     * @param client The client object to modify.
     */
    static void _changeClientRecord(clsBankClient & client);

    /**
     * @brief Mark a client as deleted in memory.
     *
     * Sets the delete sign flag of the given client object to true.
     *
     * @param client The client object to mark as deleted.
     * @param vClients The vector of clients containing the client (unused in this implementation).
     */
    static void _markClientDeleteSign(clsBankClient & client, vector <clsBankClient> & vClients);

    /**
     * @brief Display a client's account balance in a formatted table row.
     *
     * Prints the account number, full name, and balance aligned in columns.
     *
     * @param clientData The client whose balance is to be displayed.
     */
    static void _showClientBalance(const clsBankClient & clientData);

public:
    /**
     * @brief Constructs a new clsBankClient object with specified personal and account details.
     *
     * Initializes the object by setting the client's personal details (first name, last name, email, phone), account credentials (account number, account balance, pincode).
     * this class also calls the clsPerson class base class constructor to initialize personal details.
     *
     * @param mode Operational mode for the client (e.g., AddMode, UpdateMode, EmptyMode).
     * @param firstName Client's first name.
     * @param lastName Client's last name.
     * @param email Client's email address.
     * @param phone Client's phone number.
     * @param pinCode Client's account PIN code.
     * @param accountNumber Unique account number assigned to the client.
     * @param accountBalance Initial account balance.
     */
    clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string pinCode, string accountNumber, float accountBalance);

    /**
     * @brief Sets the client's PIN code.
     *
     * @param pinCode The new PIN code to set.
     */
    void setPinCode(string pinCode)
    {
        _pinCode = pinCode;
    }

    /**
     * @brief Sets the client's account balance.
     *
     * @param accountBalance The new account balance.
     */
    void setAccountBalance(float accountBalance)
    {
        _accountBalance = accountBalance;
    }

    /**
     * @brief Marks the client record for deletion or clears the delete mark.
     *
     * @param value True to mark for deletion, false to unmark.
     */
    void setDeleteSign(bool value)
    {
        _deleteSign = value;
    }

    /**
     * @brief Retrieves the client's account number.
     *
     * @return The account number as a string.
     */
    string getAccountNumber() const
    {
        return _accountNumber;
    }

    /**
     * @brief Retrieves the client's account balance.
     *
     * @return The account balance as a float.
     */
    float getAccountBalance() const
    {
        return _accountBalance;
    }

    /**
     * @brief Retrieves the client's PIN code.
     *
     * @return The PIN code as a string.
     */
    string getPinCode() const
    {
        return _pinCode;
    }

    /**
     * @brief Checks whether the client record is marked for deletion.
     *
     * @return True if marked for deletion, false otherwise.
     */
    bool getDeleteSign() const
    {
        return _deleteSign;
    }

    /**
     * @brief checks if the mode is in 'UpdateMode'
     * @return true if the mode is updated, otherwise false.
     */
    bool isModeUpdated() const;

    /**
     * @brief Switches the client object into update mode.
     */
    void setToUpdateMode();

    /**
     * @brief Prints detailed information about the client to the console.
     */
    void print();

    /**
     * @brief Checks if the client object is empty (no valid account data).
     *
     * @return True if the object is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Loads client records from a file into a vector.
     *
     * Reads client records from the specified file and returns them as a vector
     * of `clsBankClient` objects. The file is expected to contain data in the
     * format recognized by `_loadClientDataFileIntoVector()`.
     *
     * @param fileName Name (or path) of the file to read from.
     * @return Vector of clsBankClient objects loaded from the file.
     */
    static vector <clsBankClient> getListVectorFromFile(const string& fileName);

    /**
     * @brief Searches for a client by account number.
     *
     * @param accountNumber The account number to search for.
     * @return The clsBankClient object if found, otherwise an empty client object.
     */
    static clsBankClient findClient(const string& accountNumber);

    /**
     * @brief Finds a client by account number and returns it by reference from a provided vector.
     *
     * @param accountNumber The account number to search for.
     * @param vClients The vector of clients to search in.
     * @return Reference to the found clsBankClient object.
     * @throws runtime_error if the client is not found.
     */
    static clsBankClient & findClientRef(const string& accountNumber, vector <clsBankClient>& vClients);

    /**
     * @brief Checks if a client exists in the system by account number.
     *
     * @param accountNumber The account number to check.
     * @return True if the client exists, false otherwise.
     */
    static bool isClientExist(const string& accountNumber);

    /**
     * @brief Updates the current client's information.
     *
     * Loads all clients from the data file into a vector, prints the current client's details,
     * and asks for confirmation before updating. If confirmed and the object is in
     * UpdateMode, the method updates the current client record, modifies the vector,
     * and saves the updated data back to the file.
     *
     * @note Only works if the object is not empty and is in UpdateMode.
     * @note Modifies the current object data in the file and in memory.
     */
    void updateInfo();

    /**
     * @brief Deletes the current client's information.
     *
     * Loads all clients from the data file into a vector, prints the current client's details,
     * and asks for confirmation before deletion. If confirmed, marks the client as deleted,
     * updates the vector, saves changes back to the file, and sets the current object
     * to an empty client object.
     *
     * @note Only works if the object is not empty.
     * @note This action is irreversible once saved to the file.
     * @note Modifies the current object to an empty client after deletion.
     */
    void deleteInfo();

    /**
     * @brief Displays the total balances of all clients along with individual balances.
     *
     * Loads all clients from the data file into a vector, then loop through every clsBankClient object to get
     * its account balance to be calculated in a different variable.
     *
     * @return the sum of each client account balances as a double.
     */
    static double calculateTotalBalances();

    /**
     * @brief Displays the total balances of all clients along with individual balances.
     */
    static void showTotalBalances();

    /**
     * @brief Adjusts the client's account balance by a given amount.
     *
     * @param amount Amount to add (positive) or subtract (negative).
     */
    void updateAccBalance(double amount);

    /**
     * @brief Saves the provided client vector to the specified file.
     *
     * @param fileName Path to the file where data will be saved.
     * @param vClients The vector of clsBankClient objects to save.
     */
    static void saveClientDataIntoFile(const string& fileName,const vector <clsBankClient>& vClients);

    /**
     * @brief Reads an account number from user input with validation.
     *
     * Depending on the provided status, validates whether the entered account number
     * exists or is new:
     * - If status is Exist, keeps prompting until a valid existing account number is entered.
     * - If status is New, keeps prompting until a unique new account number is entered.
     *
     * @param status The validation mode: Exist (must already exist) or New (must not exist).
     * @return The validated account number entered by the user.
     *
     * @note This method performs interactive console input and validation loops.
     */
    static string readAccountNumber(enStatus status);

    // These friend declarations giving access to specific screens classes to they can directly add, update and delete
    // clsBankClient objects.
    friend class clsAddNewClientScreen;
    friend class clsDeleteClientScreen;
    friend class clsUpdateClientScreen;
};
