/**
 * @file clsFindClientScreen.h
 * @brief Defines the `clsFindClientScreen` class for searching and displaying a client’s information.
 *
 * ## Overview
 * The `clsFindClientScreen` class provides a user interface screen that allows
 * operators to find an existing client by account number. It inherits from
 * `clsScreen` for common UI utilities and integrates with `clsBankClient`
 * to locate and display the requested client.
 *
 * ## Key Responsibilities
 * - Display a screen for finding client information.
 * - Prompt the user to enter an existing account number.
 * - Search for a client in persistent storage by account number.
 * - Display the client’s details if the account exists.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — to reuse screen drawing and formatting utilities.
 * - **Uses:**
 *   - `clsBankClient` — for searching and retrieving client records.
 *   - `clsPrintPersonCard` — to print client details if found.
 *   - `clsInputValidation` — for validated account number input.
 *
 * ## Notable Implementation Details
 * - Client search is performed using `clsBankClient::findClient()`.
 * - If the client is not found, no details are printed (future extension could add a “not found” message).
 * - Data is always loaded fresh from the persistent storage file.
 *
 * ## Usage
 * Call `clsFindClientScreen::findClientScreen()` to launch the
 * **"Find Client"** process in the system’s UI flow.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
#include "../../Templates/clsFindEntityScreen.h"
using namespace std;

/**
 * @class clsFindClientScreen
 * @brief Provides the user interface screen for locating and displaying a client’s details.
 *
 * ## Overview
 * This screen allows operators to look up an existing client by account number.
 * It inherits from `clsScreen` for header formatting and relies on `clsBankClient`
 * to retrieve the client record and `clsPrintPersonCard` to display the result.
 *
 * ## Responsibilities
 * - Ask the user for an account number.
 * - Search for the corresponding client in the system.
 * - Display the client’s details if found.
 *
 * @note The current implementation only prints details if the client exists;
 *       it does not notify the user when no match is found.
 */
class clsFindClientScreen : protected clsFindEntityScreen<clsBankClient>
{
public:
    /**
     * @brief Displays the "Find Client" screen and executes the client search workflow.
     *
     * ## Workflow
     * - Prompts the user to enter an existing account number.
     * - Searches for the client using `clsBankClient::findClient()`.
     * - If the client is found, prints a confirmation message and the client’s details.
     *
     * @note If no client is found, the method silently exits without printing a message.
     *       This can be extended to provide better feedback to the user.
     */
    static void findClientScreen()
    {
        findEntityScreen
        (
            ClientsDataFile,
            "\t Find Client Info Screen",
            clsBankClient::readAccountNumber,
            clsBankClient::findClient,
            clsPrintPersonCard::printClientInfo
        );
    }
        // vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        // _drawScreenHeader("\t Find Client Info Screen");

        // string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        // clsBankClient clientFound = clsBankClient::findClient(accountNumber);

        // if (!clientFound.isEmpty())
        // {
        //     cout << "\nClient is Found :)\n";
        //     clsPrintPersonCard::printClientInfo(clientFound);
        // }

};
