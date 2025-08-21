#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
{
public:
    static void findClientScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        _drawScreenHeader("\t Find Client Info Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient clientFound = clsBankClient::findClient(accountNumber);

        if (!clientFound.isEmpty())
        {
            cout << "\nClient is Found :)\n";
            clsPrintPersonCard::printClientInfo(clientFound);
        }
    }
};

