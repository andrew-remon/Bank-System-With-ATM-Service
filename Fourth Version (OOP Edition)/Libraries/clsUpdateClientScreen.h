#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

public:
    static void updateClientScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        _drawScreenHeader("\tUpdate Client Info Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient & clientToBeUpdated = clsBankClient::findClientRef(accountNumber, vClients);

        clsPrintPersonCard::printClientInfo(clientToBeUpdated);

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            if (clientToBeUpdated._mode == clsBankClient::enMode::UpdateMode)
            {
                clsBankClient::_changeClientRecord(clientToBeUpdated);

                clsBankClient::_saveClientDataIntoFile(ClientsDataFile, vClients);

                cout << "\nClient Updated Successfully." << endl;

                clsPrintPersonCard::printClientInfo(clientToBeUpdated);
            }
            else cout << "\nUpdate Failed, It's an empty object.";
        }
    }
};
