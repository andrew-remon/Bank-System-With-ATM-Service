#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

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
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        string title = "\t\tClients List Screen";
        string subTitle = "\t\tClients List (" + to_string(vClients.size()) + "):";
        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" <<  "------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(17) << "Account Number:";
        cout << "| " << left << setw(15) << "PIN Code:"      ;
        cout << "| " << left << setw(20) << "Client Name:"   ;
        cout << "| " << left << setw(15) << "Phone:"         ;
        cout << "| " << left << setw(25) << "Email:"         ;
        cout << "| " << left << setw(13) << "Balance: |" << endl;
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------------------" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\tNo Data Available in the System" << endl;
        }

        for (clsBankClient & client : vClients)
        {
            _printClientData(client);
            cout << endl;
        }
        cout << setw(8) << left << "" <<  "------------------------------------------------------------------------------------------------------------------" << endl;
    }
};
