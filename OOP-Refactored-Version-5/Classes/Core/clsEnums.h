/**
 * @file clsEnums.h
 * @brief Defines all the enums used in The Bank System Project.
 *
 * ## Overview
 * This file gathers all the enums used in the project relevant to project features, provides a clear way to define each enum
 * and its scope, deals with enum related to UI features, transactions features, user features,
 * the status of the user or the client (a new entity or an existed one), and finally the users' permissions.
 *
 * ## Key Responsibilities
 * - Defines the UI Features (Showing the clients list, Adding, Deleting, Updating and finding client,
 * the transactions for/between clients, Managing Users, Displaying the Log file for logins and finally the Log Out option)
 * - Defines The Transaction Features (Deposit, Withdraw, showing the total Balances sum,
 * Transfer between two clients' accounts, Displaying the Transfer Log file and Returning to Main Menu Screen)
 * - Defines the User Features (Showing the Users list, Adding, Deleting, Updating, Finding user,
 * and Returning to Main Menu)
 * - Defines the User/Client Status (whether Existed or New).
 * - Defines The Users' Permissions (to the UI Features whether the logged-in User
 * has the access to use this feature or not. This class uses powers 2 (bitmask) for bitwise flags.)
 */
#pragma once
#include <iostream>
using namespace std;

/**
 * @enum enChoice
 * @brief Represents the available options in the main menu of the Bank System.
 *
 * This enum class defines the possible choices a user can make from the main UI menu,
 * covering client management, transactions, user management, and session actions.
 *
 * ## Enumerators
 * - ShowClientList (1): Display all clients in the system.
 * - AddNewClient   (2): Add a new client to the system.
 * - DeleteClient   (3): Remove an existing client.
 * - UpdateClientInfo (4): Edit details of an existing client.
 * - FindClient     (5): Search for a client by account number.
 * - Transactions   (6): Access the transactions sub-menu.
 * - ManageUsers    (7): Access the user management sub-menu.
 * - ShowLoginRecordsList (8): Display the login activity log.
 * - LogOut         (9): Log out of the current session.
 */
enum class enChoice
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    ManageUsers = 7,
    ShowLoginRecordsList = 8,
    LogOut = 9,
};

/**
 * @enum enTransactionChoice
 * @brief Represents all the transactions options (features) in the Bank System.
 *
 * This enum class defined the available options When user proceed with Transactions for/between clients' accounts.
 *
 * ## Enumerators
 * - Deposit (1): Deposit a specified amount into a client account.
 * - Withdraw (2): Withdraw a specified amount from a client account (only if the balance is sufficient).
 * - TotalBalances (3): Display all clients list (Name, Account Number and Account Balance)
 *  along with The sum of all balances.
 * - Transfer (4): Transfer money between two clients's accounts.
 * - ShowTransferRecordsList (5): Display the transactions activity log.
 * - MainMenu (6): Return to the main menu screen.
*/
enum class enTransactionChoice
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    Transfer = 4,
    ShowTransferRecordsList = 5,
    MainMenu = 6
};

/**
 * @enum enUserChoice
 * @brief Represents the available options (Features) for users management in the bank system.
 *
 * This enum class provides defined actions to manage users such as: showing all users list,
 * adding, deleting, updating, finding users.
 *
 * ## Enumerators
 * - ShowUserList (1): Display all users in the system.
 * - AddNewUser   (2): Add a new user to the system.
 * - DeleteUser   (3): Remove an existing user.
 * - UpdateUserInfo (4): Edit details of an existing user.
 * - FindUser     (5): Search for a user by username.
 * - MainMenu (6): Return to the main menu screen.
 */
enum class enUserChoice
{
    ShowUserList = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUserInfo = 4,
    FindUser = 5,
    MainMenu = 6,
};

/**
 * @enum enStatus
 * @brief Defines the status of an entity (user or client).
 *
 * ## Enumerators
 * New (1): Represents a new entity.
 * Exist (2): Represents an existing entity.
 */
enum class enStatus
{
    New = 1,
    Exist = 2,
};

/**
 * @enum enPermissions
 * @brief Defines the available permissions for a user to manage system features.
 *
 * This enum class provides the user the available permissions as bitmask flags where each value is a power of 2.
 *
 * ## Enumerators
 * - showing (1): permission to show all clients list.
 * - adding (2): permission to add new client.
 * - deleting (4): permission to delete an existing client.
 * - updating (8): permission to update client's information.
 * - finding (16): permission to find client's information by account number.
 * - transactions (32): permission to make transactions.
 * - managingUsers (64): permission to manage users.
 * - loginRecords (128): permission to view login activity log.
 */
enum class enPermissions
{
    showing = 1,
    adding = 2,
    deleting = 4,
    updating = 8,
    finding = 16,
    transactions = 32,
    managingUsers = 64,
    loginRecords = 128,
};

enum class enMode
{
    EmptyMode = 0,
    UpdateMode = 1,
    AddMode = 2
};
