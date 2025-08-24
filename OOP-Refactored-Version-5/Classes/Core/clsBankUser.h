/**
 * @file clsBankUser.h
 * @brief Defines the `clsBankUser` class for managing system user accounts and access permissions.
 *
 * ## Overview
 * The `clsBankUser` class represents a single system user within the banking application.
 * It stores authentication details (username, password) and authorization settings
 * (access permissions), and provides methods for verifying credentials, checking
 * permissions, and managing user records in persistent storage.
 *
 * It supports:
 * - **Instance-level operations**: Working with a single user's data (e.g., printing,
 *   permission checks).
 * - **Static-level operations**: Loading all users from a file, finding a specific user
 *   by username or credentials, saving user collections back to file.
 *
 * ## Key Responsibilities
 * - Encapsulate user details including authentication credentials and permission flags.
 * - Serialize and deserialize user data to/from a text file.
 * - Support login validation by matching username/password combinations.
 * - Manage permissions using bitwise flags or a full-access (-1) value.
 * - Provide CRUD-like functionality (create, find, update, delete) for user accounts.
 *
 * ## Data Storage Format
 * User data is stored in a text file, each record on a single line with fields separated
 * by the delimiter `#//#` in the following order:
 * ```
 * FirstName#//#LastName#//#Email#//#Phone#//#UserName#//#Password#//#AccessValue
 * ```
 * Deleted users are not saved back to the file; they are skipped during the save process.
 *
 * ## Relationships
 * - **Inherits from:** `clsPerson` — for basic identity/contact info.
 * - **Uses utilities:**
 *   - `clsString` — for splitting and joining serialized data strings.
 *   - `clsInputValidation` — for validated input during user creation/update.
 *   - `clsUtil` — helper utilities for confirmations and formatting.
 * - **Friend Classes** (can access private members):
 *   - `clsAddNewUserScreen`
 *   - `clsDeleteUserScreen`
 *   - `clsUpdateUserScreen`
 *
 * ## Notable Implementation Details
 * - **Permissions** are stored as a `short` integer, either as a sum of bit flags
 *   or `-1` for full access.
 * - `isUserHasPermission()` uses bitwise `AND` to check specific permissions.
 * - Internal `_deleteSign` flag determines if a user is marked for deletion.
 * - Const correctness is applied to getters so they can be called on const objects.
 * - Vectors are passed by `const&` when not modified, improving performance.
 * - `findUserByUserNameAndPassword()` returns a **copy** of the matched user
 *   (safe for modifications after retrieval).
 *
 * @note This class is tightly integrated with the file I/O layer and the screen classes.
 *       It should be modified carefully to maintain data integrity.
 *
 * @note This class is designed for file-based storage; adapting to a database may require
 * changes in serialization methods.
 */

#pragma once
#include <iostream>
#include <vector>
#include "clsPerson.h"
#include "clsEnums.h"
using namespace std;

/**
 * @class clsBankUser
 * @brief Represents a User in the banking system.
 *
 * This class stores username, password, user permissions and access value.
 * it provides core operations such as updating, deleting, finding and saving user information.
 *
 * Inherits:
 * - clsPerson (to manage general personal information)
 */
class clsBankUser : public clsPerson
{
private:
    struct stPermissions
    {
        bool showing = false, adding = false, deleting = false, updating = false, finding = false,
            transactions = false, managingUsers = false, loginRecords = false;
    };

    string _userName, _password;
    enMode _mode;
    stPermissions _permissions;
    short _accessValue;
    bool _deleteSign = false;

    /**
     * @brief converts the user record from  the file to a clsBankUser object.
     *
     * retrieves the user record from the main Users file (acting as a database) and constructs a
     * corresponding clsBankUser object.
     *
     * @param userRecord the user record line from the file.
     * @param sep the default separator used to split each field of the user record.
     * @return a clsBankUser Object created from the parsed record.
     */
    static clsBankUser _convertLineIntoUserObject(const string& userRecord, const string& sep = "#//#");

    /**
     * @brief creates an empty clsBankUser object.
     *
     * constructs a clsBankUser object with default/empty values.
     *
     * @return an empty clsBankUser object.
     */
    static clsBankUser _getEmptyUserObject();

    /**
     * @brief creates a clsBankUser object with add mode.
     *
     * constructs a clsBankUser object with default values, add mode and a specified username.
     *
     * @param userName The username required for the new clsBankUser object.
     * @return a clsBankUser object initialized in add mode with the given user name.
     */
    static clsBankUser _getAddUserObject(const string& userName);

    /**
     * @brief rebuilds the clsBankUser object permissions from its access value.
     *
     * Extracts individual permission flags from the user's `_accessValue`
     * by applying the bitwise AND (`&`) operator with predefined masks.
     *
     * @param user Reference to clsBankUser object whose permissions will be updated.
     */
    static void _rebuildPermissionsFromAccessValue(clsBankUser & user);

    /**
     * @brief Reads all user records from a file and loads them into a vector of clsBankUser objects.
     *
     * Opens the specified file, reads each line as a user record, converts it into a clsBankUser object,
     * and appends it to the resulting vector. Permissions are rebuilt for each user after loading.
     *
     * @param fileName The path to the file containing user records.
     * @return A vector of clsBankUser objects loaded from the file.
     */
    static vector <clsBankUser> _loadUserDataFileIntoVector(const string& fileName);

    /**
     * @brief Interactively configures the access permissions for a clsBankUser
     *
     * prompts the user with a series of yes-or-no questions for each available permissions or grants full permissions if
     * chosen, updates the clsBankUser object accordingly and returns the access value as a bitmask.
     *
     * @param user Reference to the clsBankUser whose access value will be updated.
     * @return The updated access value as an integer bitmask, or -1 if full access is granted.
     */
    static int _manageUserAccess(clsBankUser & user);

    /**
     * @brief builds a user record string from a clsBankUser object.
     *
     * Extracts every detail from the clsBankUser instance, concatenates them into a user record string, with each field separated by the default separator.
     *
     * @param userData Reference to a clsBankUser object whose data will be serialized.
     * @param sep used to separate different clsBankUser information fields.
     * @return a string containing the serialized user record.
     */
    static string _returnUserData(const clsBankUser& userData, string sep = "#//#");

    /**
     * @brief save each user record string serialized from the clsBankUser vector to a file (acting as a database)
     *
     * Converts each clsBankUser object in the given vector into a serialized string and writes it to the specified file,      * overwriting any existing content.
     * Records marked for deletion are skipped
     *
     * @param fileName the main file used to stored serialized users records.
     * @param vUsers a vector containing all the clsBankUser objects defined in the system.
     */
    static void _saveUserDataIntoFile(const string& fileName, const vector <clsBankUser>& vUsers);

    /**
     * @brief Marks a clsBankUser object for deletion.
     *
     * Sets the user's internal '_deleteSign' flag to true, indicating
     * that the record should be skipped when saving to file.
     *
     * @param user Reference to a clsBankUser object whose delete sign will be changed.
     */
    static void _markUserDeleteSign(clsBankUser & user);

    /**
     * @brief Interactively changes the clsBankUser object information, including permissions.
     *
     * Prompts the user to update personal details:(first name, last name, email, phone, password)
     * and adjusts access permissions through `_manageUserAccess`.
     * @param user Reference to a clsBankUser object whose information will be updated in-place.
     */
    static void _changeUserRecord(clsBankUser & user);

public:

    /**
     * @brief constructs The clsBankUser object with the given personal and account details.
     *
     * Initializes the object by setting the user's personal details (first name, last name, email, phone), account credentials (username, password), access permissions value and operational mode.
     * this class also calls the clsPerson class base class constructor to initialize personal details.
     *
     * @param mode The operational mode for the user (e.g., AddMode, UpdateMode).
     * @param firstName The user's first name.
     * @param lastName The user's last name.
     * @param email The user's email address.
     * @param phone The user's phone number.
     * @param userName The unique username for the bank user.
     * @param password The user's account password.
     * @param accessValue The permission/access level value assigned to the user.
     */
    clsBankUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password,short accessValue);

    /**
     * @brief Gets the username of the user.
     * @return Username as a string.
     */
    string getUserName() const
    {
        return _userName;
    }

    /**
     * @brief Sets the username of the user.
     * @param UserName New username to assign.
     */
    void setUserName(string UserName)
    {
        _userName = UserName;
    }

    /**
     * @brief Sets the user's password.
     * @param Password New password to assign.
     */
    void setPassword(string Password)
    {
        _password = Password;
    }

    /**
     * @brief Gets the user's password.
     * @return Password as a string.
     */
    string getPassword() const
    {
        return _password;
    }

    /**
     * @brief Sets the user's access value as a bitmask.
     *
     * The access value encodes permissions using individual bits:
     * - Bit 0 (1):    Can view clients list
     * - Bit 1 (2):    Can add new clients
     * - Bit 2 (4):    Can delete clients
     * - Bit 3 (8):    Can update clients
     * - Bit 4 (16):   Can find clients
     * - Bit 5 (32):   Can perform transactions
     * - Bit 6 (64):   Can manage users
     * - Bit 7 (128):  Can view login records
     *
     * Use bitwise OR (`|`) to combine multiple permissions,
     * and bitwise AND (`&`) to check for a specific permission.
     *
     * @param value New access value bitmask.
     */
    void setAccessValue(int value)
    {
        _accessValue = value;
    }

    /**
     * @brief Gets the user's access value as a bitmask.
     *
     * The access value encodes permissions using individual bits:
     * - Bit 0 (1):    Can view clients list
     * - Bit 1 (2):    Can add new clients
     * - Bit 2 (4):    Can delete clients
     * - Bit 3 (8):    Can update clients
     * - Bit 4 (16):   Can find clients
     * - Bit 5 (32):   Can perform transactions
     * - Bit 6 (64):   Can manage users
     * - Bit 7 (128):  Can view login records
     *
     * @return Access value as a short integer bitmask.
     */
    short getAccessValue() const
    {
        return _accessValue;
    }

    /**
     * @brief Checks whether the delete sign is set for the user.
     * @return True if marked for deletion, false otherwise.
     */
    bool getDeleteSign() const
    {
        return _deleteSign;
    }

    /**
     * @brief Sets the delete sign for the user.
     * @param value True to mark for deletion, false otherwise.
     */
    void setDeleteSign(bool value)
    {
        _deleteSign = value;
    }

    /**
     * @brief sets the clsBankUser '_mode' to update mode.
     */
    void setToUpdateMode();

    /**
     * @brief prints the user's personal and account information.
     *
     * displays the clsBankUser object card with personal information (first name, last name, full name, email, phone)
     * and account details (username, password, access value.)
     */
    void print();

    /**
     * @brief checks if the mode is in 'UpdateMode'
     * @return true if the mode is updated, otherwise false.
     */
    bool isModeUpdated() const;

    /**
     * @brief check the clsBankUser object whether it is empty or not.
     *
     * @return true if the mode is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Loads a list of bank users from a file.
     *
     * Reads user records from the specified file and returns them as a vector
     * of `clsBankUser` objects. The file is expected to contain data in the
     * format recognized by `_loadUserDataFileIntoVector()`.
     *
     * @param fileName Name (or path) of the file to read from.
     * @return A vector containing all `clsBankUser` objects loaded from the file.
     */
    static vector <clsBankUser> getListVectorFromFile(const string& fileName);

    /**
     * @brief Searches for a user in the data file by username.
     *
     * Loads all users from the data file and iterates through them to find the one
     * with the specified username. If found, returns a copy of the corresponding clsBankUser object.
     * If no match is found, returns an empty clsBankUser object.
     *
     * @param userName The username of the user to search for.
     * @return clsBankUser A copy of the matching user if found; otherwise, an empty user object.
     *
     * @note This method returns a copy, so changes made to the returned object
     *       will not affect the original data in the file.
     * @note Performance: Each call reads all user data from the file, which may be slow
     *       if the file is large or the method is called frequently.
     */
    static clsBankUser findUser(const string& userName);

    /**
     * @brief Searches for a user in the data file by username and password.
     *
     * Loads all users from the data file and iterates through them to find a user
     * whose username and password both match the specified values.
     * If found, returns a copy of the matching clsBankUser object.
     * If no match is found, returns an empty clsBankUser object.
     *
     * @param userName The username to search for.
     * @param password The password to match with the username.
     * @return clsBankUser A copy of the matching user if found; otherwise, an empty user object.
     *
     * @note This method returns a copy, so changes made to the returned object
     *       will not affect the original data in the file.
     * @note Performance: Each call reads all user data from the file, which may be slow
     *       if the file is large or the method is called frequently.
     */
    static clsBankUser findUserByUserNameAndPassword(const string& userName, const string& password);

    /**
     * @brief Finds a reference to a user in a given list of users by username.
     *
     * Iterates through the provided vector of clsBankUser objects and returns a reference
     * to the first user whose username matches the specified value.
     *
     * @param userName The username of the user to search for.
     * @param vUsers A reference to the vector containing users to search within.
     * @return clsBankUser& A reference to the matching user.
     *
     * @throws std::runtime_error If no user with the given username is found.
     *
     * @note Because this method returns a reference to a user inside the vector,
     *       modifying the returned object will directly modify the vector's contents.
     *       The vector must remain valid while using the returned reference.
     * @note Performance: The search is linear in time complexity (O(n)), but it avoids
     *       file access since it operates directly on the provided vector.
     */
    static clsBankUser & findUserRef(const string& userName, vector <clsBankUser> & vUsers);

    /**
     * @brief Check if clsBankUser object exists.
     *
     * internally calls the method 'findUser' and search through all clsBankUser objects by username to find the specified object.
     *
     * @param userName The clsBankUser username to search for.
     * return True if the user is found, false otherwise.
     */
    static bool isUserExist(string userName);

    /**
     * @brief Check if clsBankUser object exists.
     *
     * internally calls the method 'findUserByUserNameAndPassword' and search through all clsBankUser objects by username and password to find the specified object.
     *
     * @param userName The clsBankUser username to search for.
     * @param password The clsBankUser password to search for.
     * return True if the user is found, false otherwise.
     */
    static bool isUserExist(string userName, string password);

    /**
     * @brief Updates the current user's information.
     *
     * Loads all users from the data file into a vector, prints the current user's details,
     * and asks for confirmation before updating. If confirmed and the object is in
     * UpdateMode, the method updates the current user record, modifies the vector,
     * and saves the updated data back to the file.
     *
     * @note Only works if the object is not empty and is in UpdateMode.
     * @note Modifies the current object data in the file and in memory.
     */
    void updateInfo();

    /**
     * @brief Deletes the current user's information.
     *
     * Loads all users from the data file into a vector, prints the current user's details,
     * and asks for confirmation before deletion. If confirmed, marks the user as deleted,
     * updates the vector, saves changes back to the file, and sets the current object
     * to an empty user object.
     *
     * @note Only works if the object is not empty.
     * @note This action is irreversible once saved to the file.
     * @note Modifies the current object to an empty user after deletion.
     */
    void deleteInfo();

    /**
     * @brief Prints an access denied message.
     *
     * Displays a message indicating that the current user does not have permission
     * to perform the requested operation and advises contacting the admin.
     */
    static void printAccessDeniedMessage();

    /**
     * @brief Reads a username from user input with validation.
     *
     * Depending on the provided status, validates whether the entered username
     * exists or is new:
     * - If status is Exist, keeps prompting until a valid existing username is entered.
     * - If status is New, keeps prompting until a unique new username is entered.
     *
     * @param status The validation mode: Exist (must already exist) or New (must not exist).
     * @return The validated username entered by the user.
     *
     * @note This method performs interactive console input and validation loops.
     */
    static string readUserName(enStatus status);

    // note: a way to use struct with enums to manage permissions.
    // static bool isUserHasPermission(enChoice permission)
    // {
    //     if (currentUser.getAccessValue() == -1) return true;
    //     else
    //     {
    //         switch (permission)
    //         {
    //         case enChoice::AddNewClient :
    //         {
    //             if (currentUser._permissions.adding == true) return true;
    //             break;
    //         }
    //         case enChoice::ShowClientList :
    //         {
    //             if (currentUser._permissions.showing == true) return true;
    //             break;
    //         }
    //         case enChoice::DeleteClient :
    //         {
    //             if (currentUser._permissions.deleting == true) return true;
    //             break;
    //         }
    //         case enChoice::UpdateClientInfo :
    //         {
    //             if (currentUser._permissions.updating == true) return true;
    //             break;
    //         }
    //         case enChoice::FindClient :
    //         {
    //             if (currentUser._permissions.finding == true) return true;
    //             break;
    //         }
    //         case enChoice::Transactions :
    //         {
    //             if (currentUser._permissions.transactions == true) return true;
    //             break;
    //         }
    //         case enChoice::ManageUsers :
    //         {
    //             if (currentUser._permissions.managingUsers == true) return true;
    //             break;
    //         }
    //         default:
    //             return false;
    //         }
    //     }
    //     return false;
    // }

    /**
     * @brief Checks if the user has the required permission.
     *
     * Determines whether the current clsBankUser object either:
     * - Has full access (access value of -1), or
     * - Has the specified permission, verified using the bitwise AND operator.
     *
     * @param permission The permission to check, represented as an enPermissions value.
     * @return True if the user has full access or the specified permission; false otherwise.
     *
     * @note This method is intended for use only with permission enums.
     */
    bool isUserHasPermission(enPermissions permission);

    // These friend declarations giving access to specific screens classes to they can directly add, update and delete
    // clsBankUser objects.
    friend class clsAddNewUserScreen;
    friend class clsDeleteUserScreen;
    friend class clsUpdateUserScreen;
};
