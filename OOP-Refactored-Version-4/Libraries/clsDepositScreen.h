#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPrintPersonCard.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
using namespace std;

class clsDepositScreen : protected clsScreen
{
public:
    static void depositScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);

        _drawScreenHeader("\t\t Deposit Screen");

        string accountNumber = clsBankClient::readAccountNumber(enStatus::Exist);

        clsBankClient & client = clsBankClient::findClientRef(accountNumber, vClients);
        clsPrintPersonCard::printClientInfo(client);


        cout << "\n\nPlease enter Deposit Amount? ";
        double depositAmount = clsInputValidation::readDblNumber("Invalid Input, Please Enter A Valid Number.");

        clsBankClient::changeAccBalance(depositAmount, vClients, client);
    }
};
