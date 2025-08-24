/**
 * @file clsUpdateClientScreen.h
 * @brief Defines the `clsUpdateClientScreen` class for updating an existing client’s information.
 *
 * ## Overview
 * The `clsUpdateClientScreen` class provides a user interface screen that allows
 * operators to update the details of an existing client by account number.
 * It inherits from `clsScreen` for screen formatting and integrates with
 * `clsBankClient` to handle the update process.
 *
 * ## Key Responsibilities
 * - Display a screen for updating client data.
 * - Prompt the user to enter an existing account number.
 * - Confirm whether the user wants to update the record.
 * - Allow modification of the client’s details.
 * - Save the updated client list to persistent storage.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for drawing headers and screen formatting.
 * - **Uses:**
 *   - `clsBankClient` — to retrieve, modify, and persist client data.
 *   - `clsPrintPersonCard` — to display client details before and after updates.
 *   - `clsInputValidation` — for validated input handling.
 *   - `clsUtil` — for confirmation prompts.
 *
 * ## Usage
 * Call `clsUpdateClientScreen::updateClientScreen()` to launch the
 * **"Update Client"** workflow in the system’s UI flow.
 */

#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
#include "../Misc/clsPrintPersonCard.h"
#include "../../Utils/clsInputValidation.h"
#include "../../Core/clsBankClient.h"
#include "../../Templates/clsUpdateEntityScreen.h"
using namespace std;

/**
 * @class clsUpdateClientScreen
 * @brief Provides the user interface screen for updating an existing client’s details.
 *
 * ## Overview
 * This screen enables operators to modify client records. It confirms the action,
 * updates the client object, and persists changes to storage.
 *
 * ## Responsibilities
 * - Request the account number of the client to update.
 * - Confirm with the user before performing the update.
 * - Modify the client’s details via `clsBankClient::_changeClientRecord()`.
 * - Save the modified client list to persistent storage.
 * - Display updated client details after successful update.
 *
 * @note Updates only succeed if the client object is in `UpdateMode`.
 */
class clsUpdateClientScreen : protected clsUpdateEntityScreen<clsBankClient>
{
public:
    /**
     * @brief Displays the "Update Client" screen and executes the client update workflow.
     *
     * ## Workflow
     * - Prompts the user to enter an existing account number.
     * - Displays the current details of the client.
     * - Asks the user to confirm before proceeding.
     * - If confirmed and the client is in `UpdateMode`:
     * - Updates the client’s details.
     * - Saves the modified client list to persistent storage.
     * - Displays the updated client information.
     * - If the client object is not in `UpdateMode`, the update fails.
     *
     * @note This method modifies persistent client records and should be used with care.
     */
    static void updateClientScreen()
    {
        updateEntityScreen
        (
            ClientsDataFile,
            "\tUpdate Client Info Screen",
            "\nClient Updated Successfully.\n",
            clsBankClient::readAccountNumber,
            clsBankClient::findClientRef,
            clsPrintPersonCard::printClientInfo,
            clsBankClient::_changeClientRecord,
            clsBankClient::saveClientDataIntoFile
        );


    //     vector <clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

    //     _drawScreenHeader("\tUpdate Client Info Screen");

    //     string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

    //     clsBankClient &clientToBeUpdated = clsBankClient::findClientRef(accountNumber, vClients);

    //     clsPrintPersonCard::printClientInfo(clientToBeUpdated);

    //     char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

    //     if (tolower(ans) == 'y')
    //     {
    //         if (clientToBeUpdated._mode == clsBankClient::enMode::UpdateMode)
    //         {
    //             clsBankClient::_changeClientRecord(clientToBeUpdated);

    //             clsBankClient::_saveClientDataIntoFile(ClientsDataFile, vClients);

    //             cout << "\nClient Updated Successfully." << endl;

    //             clsPrintPersonCard::printClientInfo(clientToBeUpdated);
    //         }
    //         else
    //             cout << "\nUpdate Failed, It's an empty object.";
    //     }
    }
};
