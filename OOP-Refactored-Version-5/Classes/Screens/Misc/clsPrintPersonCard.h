/**
 * @file clsPrintPersonCard.h
 * @brief Declares the `clsPrintPersonCard` utility class for printing formatted client and user information.
 *
 * ## Overview
 * This file provides helper methods to display information about `clsBankClient`
 * and `clsBankUser` objects in a human-readable "card" format.
 *
 * The cards are used in various screens to show details like personal data,
 * account information, or transfer-related details in a consistent layout.
 *
 * ## Relationships
 * - **Uses:**
 *   - `clsBankClient` — for accessing client data.
 *   - `clsBankUser` — for accessing system user data.
 */

#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Core/clsBankUser.h"
using namespace std;

/**
 * @class clsPrintPersonCard
 * @brief Utility class for printing formatted cards of clients and users.
 *
 * ## Overview
 * The `clsPrintPersonCard` class provides static helper methods to print
 * detailed or partial information about clients and users.
 * It is designed to ensure a consistent UI layout across different screens.
 *
 * ## Methods
 * - `static void printClientInfo(clsBankClient)` — Prints full client information.
 * - `static void printTransferClientInfo(clsBankClient)` — Prints limited client information
 *   (for transfers).
 * - `static void printUserInfo(clsBankUser)` — Prints full user information.
 *
 * ## Design
 * - **Static Class**: All methods are `static` to allow direct use without instantiating the class.
 * - **Output Format**: Information is printed in a bordered "card" style for readability.
 */
class clsPrintPersonCard
{
public:

    /**
     * @brief Prints the full information of a bank client in a formatted card.
     *
     * @param client The `clsBankClient` object containing the client’s details.
     *
     * ## Details Printed
     * - First name
     * - Last name
     * - Full name
     * - Email
     * - Phone
     * - Account number
     * - PIN code
     * - Account balance
     */
    static void printClientInfo(clsBankClient client)
    {
        cout << "\nClient Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << client.getFirstName() << endl;
        cout << "Last Name: " << client.getLastName() << endl;
        cout << "Full Name: " << client.FullName() << endl;
        cout << "Email: " << client.getEmail() << endl;
        cout << "Phone: " << client.getPhone() << endl;
        cout << "Account Number: " << client.getAccountNumber() << endl;
        cout << "PIN Code: " << client.getPinCode() << endl;
        cout << "Account Balance: " << client.getAccountBalance() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }

    /**
     * @brief Prints a simplified client card for transfer operations.
     *
     * @param client The `clsBankClient` object containing the client’s details.
     *
     * ## Details Printed
     * - Full name
     * - Account number
     * - Account balance
     */
    static void printTransferClientInfo(clsBankClient client)
    {
        cout << "\nClient Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "Full Name: " << client.FullName() << endl;
        cout << "Account Number: " << client.getAccountNumber() << endl;
        cout << "Account Balance: " << client.getAccountBalance() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }

    /**
     * @brief Prints the full information of a system user in a formatted card.
     *
     * @param user The `clsBankUser` object containing the user’s details.
     *
     * ## Details Printed
     * - First name
     * - Last name
     * - Full name
     * - Email
     * - Phone
     * - Username
     * - Password
     * - Access value (permissions bitmask/role level)
     */
    static void printUserInfo(clsBankUser user)
    {
        cout << "\nUser Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << user.getFirstName() << endl;
        cout << "Last Name: " << user.getLastName() << endl;
        cout << "Full Name: " << user.FullName() << endl;
        cout << "Email: " << user.getEmail() << endl;
        cout << "Phone: " << user.getPhone() << endl;
        cout << "UserName: " << user.getUserName() << endl;
        cout << "Password: " << user.getPassword() << endl;
        cout << "Access Value: " << user.getAccessValue() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }
};
