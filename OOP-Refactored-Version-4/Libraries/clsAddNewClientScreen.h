#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsBankClient.h"
using namespace std;


class clsAddNewClientScreen : protected clsScreen
{
public:
    static void addNewClientScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::_loadDataFileIntoVector(ClientsDataFile);

        _drawScreenHeader("\tAdd New Client Info Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::New);

        clsBankClient newClient = clsBankClient::_getAddClientObject(accountNumber);

        clsBankClient::_changeClientRecord(newClient);

        newClient._mode = clsBankClient::enMode::UpdateMode;

        vClients.push_back(newClient);

        clsBankClient::_saveClientDataIntoFile(ClientsDataFile, vClients);

        cout << "\nClient Added Successfully." << endl;

        clsPrintPersonCard::printClientInfo(newClient);
    }
};
