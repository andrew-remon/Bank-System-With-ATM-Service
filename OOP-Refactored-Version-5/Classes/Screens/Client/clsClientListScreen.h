/**
 * @file clsClientListScreen.h
 * @brief Defines the `clsClientListScreen` class for displaying a formatted list of bank clients.
 *
 * ## Overview
 * The `clsClientListScreen` class provides a dedicated user interface screen
 * for viewing all clients registered in the banking system. It loads client
 * data from persistent storage, renders it in a structured tabular format,
 * and provides clear headers, spacing, and alignment for readability.
 *
 * ## Key Responsibilities
 * - Load all clients from the data file into a vector.
 * - Display a screen header with a dynamic subtitle indicating the client count.
 * - Print client details (account number, PIN code, full name, phone, email, and balance)
 *   in a tabular format with proper column alignment.
 * - Handle the case when no client data exists in the system.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 * - **Uses:**
 *   - `clsBankClient` — for retrieving client data and accessing client properties.
 *   - Standard C++ I/O and formatting utilities (`iostream`, `iomanip`) for aligned output.
 *
 * ## Notable Implementation Details
 * - Client records are retrieved using `clsBankClient::getListVectorFromFile()`,
 *   which loads clients from the persistent storage file.
 * - `_printClientData()` is a helper method responsible for printing a single
 *   client’s details in a row with aligned columns.
 * - The table uses fixed-width columns with `setw` for consistent alignment.
 * - If no clients exist, the screen explicitly shows a message instead of an empty table.
 *
 * ## Usage
 * Call `clsClientListScreen::showClientsList()` to display the client list screen
 * as part of the banking application’s UI navigation flow.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include "../Misc/clsScreen.h"
#include "../../Core/clsBankClient.h"
using namespace std;

/**
 * @class clsClientListScreen
 * @brief Provides a user interface screen to display all registered bank clients.
 *
 * ## Overview
 * This screen allows the user to view a formatted list of all clients in the banking system.
 * It inherits from `clsScreen` to reuse common screen functionality, such as drawing
 * headers, and integrates with `clsBankClient` to fetch and display client data.
 *
 * ## Responsibilities
 * - Load all client records from the persistent storage file.
 * - Display a header and subtitle with the number of clients.
 * - Print client details (account number, PIN code, full name, phone, email, balance)
 *   in a properly formatted table.
 * - Show a fallback message if no clients exist in the system.
 *
 * @note This class does not modify client data; it is strictly read-only and
 *       intended for displaying existing records.
 */

class clsClientListScreen : protected clsScreen
{
private:
    static void _printClientData(clsBankClient clientData)
    {
        cout << setw(8) << left << "" << "| " << setw(17) << left << clientData.getAccountNumber();
        cout << "| " << setw(15) << left << clientData.getPinCode();
        cout << "| " << setw(20) << left << clientData.FullName();
        cout << "| " << setw(15) << left << clientData.getPhone();
        cout << "| " << setw(25) << left << clientData.getEmail();
        cout << "| " << setw(9) << left << clientData.getAccountBalance() << "|";
    }

public:
    static void showClientsList()
    {
        vector<clsBankClient> vClients = clsBankClient::getListVectorFromFile(ClientsDataFile);

        string title = "\t\tClients List Screen";
        string subTitle = "\t\tClients List (" + to_string(vClients.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(17) << "Account Number:";
        cout << "| " << left << setw(15) << "PIN Code:";
        cout << "| " << left << setw(20) << "Client Name:";
        cout << "| " << left << setw(15) << "Phone:";
        cout << "| " << left << setw(25) << "Email:";
        cout << "| " << left << setw(13) << "Balance: |" << endl;
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------------------" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsBankClient &client : vClients)
        {
            _printClientData(client);
            cout << endl;
        }
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------------------" << endl;
    }
};
