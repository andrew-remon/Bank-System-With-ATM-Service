#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
public:
    static void deleteClientScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        _drawScreenHeader("\t Delete Client Info Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient & clientToBeDeleted = clsBankClient::findClientRef(accountNumber, vClients);

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
