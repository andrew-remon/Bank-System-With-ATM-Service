#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsGlobal.h"
#include "clsWithdrawScreen.h"
#include "clsScreen.h"
#include "clsEnums.h"
using namespace std;

class clsMainScreen;

class clsTransactionScreen : protected clsScreen
{
private:
    static short _readTransactionsChoice()
    {
        cout << setw(30) << "" << "Choose What Do You Want to do? [1 to 4]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 4, "Choose a number between 1 and 4");
        return choice;
    }

    static void _performTransactionsChoice(enTransactionChoice transactionChoice);

public:
    static void showTransactionsMenu();

};
