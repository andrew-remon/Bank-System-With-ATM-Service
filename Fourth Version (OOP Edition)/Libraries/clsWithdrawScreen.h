#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
public:
    static void withdrawScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        _drawScreenHeader("\t\t Withdraw Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient & client = clsBankClient::findClientRef(accountNumber, vClients);
        clsPrintPersonCard::printClientInfo(client);

        double withdrawAmount = 0;

        do
        {
            cout << "Please enter Withdraw Amount? ";
            withdrawAmount = clsInputValidation::readDblNumber("Invalid Input, Please Enter A Valid Number.");

            if (withdrawAmount > client.getAccountBalance())
                cout << "\nAmount Exceeds the balance, you can withdraw up to: " << client.getAccountBalance() << endl;

        } while (withdrawAmount > client.getAccountBalance());

        clsBankClient::changeAccBalance(-withdrawAmount, vClients, client);
    }
};
