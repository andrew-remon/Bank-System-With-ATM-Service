/**
 * @file clsAddNewClientScreen.h
 * @brief Defines the `clsAddNewClientScreen` class for adding new bank clients through the UI.
 *
 * ## Overview
 * The `clsAddNewClientScreen` class represents the **"Add New Client"** screen in the banking
 * application. It inherits from the generic template class `clsAddNewEntityScreen<clsBankClient>`,
 * which provides a reusable workflow for adding new entities. By specializing the workflow with
 * `clsBankClient`, this screen handles client-specific input, persistence, and output formatting.
 *
 * ## Key Responsibilities
 * - Provide an interface for adding new client records.
 * - Configure the base entity-creation workflow with client-specific methods:
 *   - Reading and validating account numbers.
 *   - Creating and initializing client objects.
 *   - Collecting user input and updating the client record.
 *   - Saving new client data into persistent storage.
 *   - Printing a formatted summary of the new client.
 *
 * ## Relationships
 * - **Inherits from:** `clsAddNewEntityScreen<clsBankClient>` — generic base class for
 *   adding entities, customized here for bank clients.
 * - **Uses:**
 *   - `clsBankClient` — to create, modify, and persist client objects.
 *   - `clsPrintPersonCard` — to print the newly added client’s information.
 *   - `clsScreen` — to reuse screen header drawing utilities.
 *
 * ## Notable Implementation Details
 * - The `addNewClientScreen()` method delegates almost entirely to the template method
 *   `addNewEntityScreen()`, supplying `clsBankClient`-specific function pointers to
 *   customize the workflow.
 * - This eliminates code duplication compared to older implementations, where the
 *   add-client logic was repeated directly in the screen.
 *
 * ## Usage
 * Call `clsAddNewClientScreen::addNewClientScreen()` to launch the "Add New Client" process
 * within the system’s UI flow.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Core/clsBankClient.h"
#include "../../Templates/clsAddNewEntityScreen.h"
using namespace std;

/**
 * @class clsAddNewClientScreen
 * @brief Specializes the generic `clsAddNewEntityScreen` for managing bank clients.
 *
 * ## Overview
 * This class represents the **"Add New Client"** screen in the banking system.
 * It inherits from the templated base class `clsAddNewEntityScreen<clsBankClient>`
 * to reuse the generic entity-creation workflow and adapt it for `clsBankClient`.
 *
 * ## Responsibilities
 * - Provide a screen for adding new clients.
 * - Configure the base template workflow with client-specific methods:
 *   - Reading account numbers.
 *   - Creating new client objects.
 *   - Modifying and saving client data.
 *   - Displaying client information.
 *
 * @note This class does not introduce additional state or logic beyond configuring
 *       the template. It serves as a **UI entry point** for the add-client process.
 */
class clsAddNewClientScreen : protected clsAddNewEntityScreen<clsBankClient>
{
public:

    /**
     * @brief Displays the "Add New Client" screen and executes the add-client workflow.
     *
     * ## Workflow
     * - Prompts the user for a new account number.
     * - Creates a `clsBankClient` object for the new client.
     * - Collects input and updates the client record.
     * - Saves the new client data into the file.
     * - Prints a formatted client card with the added details.
     *
     * @note Internally, this delegates to the templated `addNewEntityScreen()` method
     *       with `clsBankClient`-specific functions passed as parameters.
     */
    static void addNewClientScreen()
    {
        // note: New implementation with 'template' integrated in the method.
        addNewEntityScreen
        (
            UsersDataFile,
            "\tAdd New User Info Scree",
            "\nClient Added Successfully.",
            clsBankClient::readAccountNumber,
            clsBankClient::_getAddClientObject,
            clsBankClient::_changeClientRecord,
            clsBankClient::_saveClientDataIntoFile,
            clsPrintPersonCard::printClientInfo
        );

        //note: old implementation with repeated code.

        // vector <clsBankClient> vClients = clsBankClient::_loadDataFileIntoVector(ClientsDataFile);

        // _drawScreenHeader("\tAdd New Client Info Screen");

        // string accountNumber = clsBankClient::readAccountNumber(enStatus::New);

        // clsBankClient newClient = clsBankClient::_getAddClientObject(accountNumber);

        // clsBankClient::_changeClientRecord(newClient);

        // newClient._mode = clsBankClient::enMode::UpdateMode;

        // vClients.push_back(newClient);

        // clsBankClient::_saveClientDataIntoFile(ClientsDataFile, vClients);

        // cout << "\nClient Added Successfully." << endl;

        // clsPrintPersonCard::printClientInfo(newClient);
    }
};
