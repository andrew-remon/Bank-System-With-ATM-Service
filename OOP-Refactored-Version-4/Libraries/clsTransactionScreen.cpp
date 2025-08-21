#include <iostream>
#include "clsTransactionScreen.h"
#include "clsMainScreen.h"
#include "clsGlobal.h"
using namespace std;

void clsTransactionScreen::_performTransactionsChoice(enTransactionChoice transactionChoice)
{
    vector <clsBankClient> vClients = clsBankClient::getClientListVector(ClientsDataFile);
    switch (transactionChoice)
    {
        case enTransactionChoice::Deposit :
        {
            clsDepositScreen::depositScreen();
            break;
        }
        case enTransactionChoice::Withdraw :
        {
            clsWithdrawScreen::withdrawScreen();
            break;
        }
        case enTransactionChoice::TotalBalances :
        {
            clsBankClient::showTotalBalances();
            break;
        }
        case enTransactionChoice::MainMenu :
        {
            clsMainScreen::showMainMenu();
            break;
        }
    }
}

void clsTransactionScreen::showTransactionsMenu()
{
    _drawScreenHeader("\t    Transaction Screen");

    cout << "\n\t\t\t\t\t============================================\n" ;
    cout << setw(40) << "" << "\t    Transactions Menu\n" ;
    cout << setw(40) << "" << "============================================\n" ;
    cout << setw(40) << "" << "\t[1] Deposit.\n" ;
    cout << setw(40) << "" << "\t[2] Withdraw.\n" ;
    cout << setw(40) << "" << "\t[3] Total Balances.\n" ;
    cout << setw(40) << "" << "\t[4] Main Menu.\n" ;
    cout << setw(40) << "" << "============================================\n" ;
    _performTransactionsChoice((enTransactionChoice)_readTransactionsChoice());
}
