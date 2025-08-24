/**
 * @file clsDeleteClientScreen.h
 * @brief Defines the `clsDeleteClientScreen` class for deleting bank clients through the UI.
 *
 * ## Overview
 * The `clsDeleteClientScreen` class provides a user interface screen that allows
 * operators to delete an existing client from the banking system. It inherits from
 * `clsScreen` to reuse common screen utilities and works closely with `clsBankClient`
 * to locate, mark, and persist deletions.
 *
 * ## Key Responsibilities
 * - Display a screen for deleting a client’s information.
 * - Prompt the user to enter an existing account number.
 * - Confirm deletion by showing the client’s details and asking for user confirmation.
 * - Mark the client as deleted and save the updated client list to persistent storage.
 * - Provide feedback about the deletion outcome.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — to reuse screen drawing and formatting utilities.
 * - **Uses:**
 *   - `clsBankClient` — to search for, mark, and save client records.
 *   - `clsPrintPersonCard` — to display client details before deletion.
 *   - `clsInputValidation` — to ensure valid user input (account numbers).
 *
 * ## Notable Implementation Details
 * - Clients are deleted logically by marking them with a delete flag,
 *   then saving the updated list back to file.
 * - Confirmation is explicitly requested before any deletion takes place.
 * - If deletion is confirmed, the client object reference is replaced with an empty object.
 *
 * ## Usage
 * Call `clsDeleteClientScreen::deleteClientScreen()` to launch the
 * **"Delete Client"** process in the system’s UI flow.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
using namespace std;


/**
 * @class clsDeleteClientScreen
 * @brief Provides the user interface screen for deleting existing bank clients.
 *
 * ## Overview
 * This screen handles the workflow of removing a client from the system.
 * It inherits from `clsScreen` for header drawing and screen formatting,
 * and integrates with `clsBankClient` to handle client lookup, deletion,
 * and persistence.
 *
 * ## Responsibilities
 * - Ask the user for an account number of the client to delete.
 * - Display the client’s details for confirmation.
 * - Handle confirmation logic and remove the client from storage if approved.
 *
 * @note This class modifies client data by marking and removing records,
 *       unlike other screen classes that may be read-only (e.g., client list).
 */
class clsDeleteClientScreen : protected clsScreen
{
public:
    /**
     * @brief Displays the "Delete Client" screen and executes the delete-client workflow.
     *
     * ## Workflow
     * - Prompts the user to enter an existing account number.
     * - Retrieves and displays the client’s details for confirmation.
     * - Asks the user to confirm whether to proceed with deletion.
     * - If confirmed, marks the client for deletion and saves the updated list to file.
     * - Replaces the deleted client object with an empty placeholder.
     *
     * @note This method modifies client records and updates persistent storage.
     */
    static void deleteClientScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        _drawScreenHeader("\t Delete Client Info Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient &clientToBeDeleted = clsBankClient::findClientRef(accountNumber, vClients);

        clsPrintPersonCard::printClientInfo(clientToBeDeleted);

        cout << "\nAre You sure You want to delete this account data (Y/N)? ";
        char ans;
        cin >> ans;

        if (tolower(ans) == 'y')
        {
            clsBankClient::_markClientDeleteSign(clientToBeDeleted, vClients);
            clsBankClient::_saveClientDataIntoFile(ClientsDataFile, vClients);
            clientToBeDeleted = clsBankClient::_getEmptyClientObject();
            cout << "\nClient Deleted Successfully." << endl;
        }
    }
};
