#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

string FileName = "bank_data.txt";
void showMainMenu();

enum enChoice
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    Exit = 7
};

enum enTransactionChoice
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

struct stClientData
{
    string accountNumber, name, phone, pinCode;
    double accountBalance;
    bool deleteSign = false;
};

void split(string s, vector <string> &vWords, string divider = " ")
{
    short pos = 0;

    while ((pos = s.find(divider)) != s.npos)
    {
        string token = s.substr(0, pos);
        if (token != "") vWords.push_back(token);
        s.erase(0, pos+divider.length()); // pos + 1 to include the whitespace char.
    }

    if (s != "") vWords.push_back(s);
}

string readAccountNumber()
{
    cout << "\nPlease enter Account Number? ";
    string accNumber;
    cin >> accNumber;
    return accNumber;
}

stClientData extractClientData(string statement, string sep)
{
    stClientData clientData;
    vector <string> vWords;

    split(statement, vWords, sep);

    clientData.accountNumber = vWords[0];
    clientData.pinCode = vWords[1];
    clientData.name = vWords[2];
    clientData.phone = vWords[3];
    clientData.accountBalance = stod(vWords[4]);

    return clientData;
}

vector <stClientData> loadDataFileIntoVector(string fileName)
{
    vector <stClientData> vClients;

    fstream myFile;
    myFile.open(fileName, ios::in);

    if (myFile.is_open())
    {
        string line;
        stClientData client;

        while(getline(myFile, line))
        {
            client = extractClientData(line, "#//#");
            vClients.push_back(client);
        }

        myFile.close();
    }

    return vClients;
}

void printClientData(stClientData clientData)
{
    cout << setw(17) << left << clientData.accountNumber;
    cout << setw(15) << left << clientData.pinCode;
    cout << setw(25) << left << clientData.name;
    cout << setw(15) << left << clientData.phone;
    cout << setw(12) << left << clientData.accountBalance;
}

void printClientsData(vector <stClientData> vClients)
{
    cout << "\n\n";
    cout << "\t\t\t\t Clients List (" << vClients.size() << "):" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << left << setw(17) << "Account Number:";
    cout << left << setw(15) << "PIN Code:";
    cout << left << setw(25) << "Name:";
    cout << left << setw(15) << "Phone:";
    cout << left << setw(12) << "Balance:" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    for (stClientData client : vClients)
    {
        printClientData(client);
        cout << endl;
    }
    cout << "-------------------------------------------------------------------------------" << endl;
}

bool checkClientExist(stClientData clientData, vector <stClientData> vClients)
{
    for (stClientData existedClient : vClients)
    {
        if(clientData.accountNumber == existedClient.accountNumber)
        {
            return true;
        }
    }
    return false;
}

stClientData getClientData(vector <stClientData> & vClients)
{
    stClientData clientData;

    cout << "\nAdding New Client:\n\n";

    cout << "Enter Account Number? ";
    cin >> clientData.accountNumber;

    while(checkClientExist(clientData, vClients))
    {
        cout << "Client with [" << clientData.accountNumber << "] exists, enter another Account Number? ";
        cin >> clientData.accountNumber;
    }

    cout << "Enter PIN Code? ";
    cin >> clientData.pinCode;
    cin.ignore();

    cout << "Enter Name? ";
    getline(cin, clientData.name);

    cout << "Enter Phone? ";
    cin >> clientData.phone;

    cout << "Enter Account Balance? ";
    cin >> clientData.accountBalance;

    return clientData;
}

string returnClientData(stClientData clientData, string sep = "#//#")
{
    string clientRecord = "";

    clientRecord += clientData.accountNumber  + sep;
    clientRecord += clientData.pinCode + sep;
    clientRecord += clientData.name    + sep;
    clientRecord += clientData.phone   + sep;
    clientRecord += to_string(clientData.accountBalance);

    return clientRecord;
}

void addClient(string clientRecord)
{
    fstream myFile;

    myFile.open(FileName, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << clientRecord << endl;
        myFile.close();
    }
}

bool findClientDataByAccNumber(vector <stClientData> vClients, string userInputAccountNumber, stClientData & client)
{
    for (stClientData c : vClients)
    {
        if (c.accountNumber == userInputAccountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}

void printClientDataByAccNumber(stClientData clientFound, string userInputAccountNumber)
{
    if (clientFound.accountNumber == userInputAccountNumber)
    {
        cout << "\nThe following are the Account Details: \n" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "Account Number: " << clientFound.accountNumber << endl;
        cout << "PIN Code: " << clientFound.pinCode << endl;
        cout << "Name: " << clientFound.name << endl;
        cout << "Phone: " << clientFound.phone << endl;
        cout << "Account Balance: " << clientFound.accountBalance << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n\n";
    }
}

bool markClientDeleteSign(string accNumber, vector <stClientData> & vClients)
{
    for (stClientData & C : vClients)
    {
        if (C.accountNumber == accNumber)
        {
            C.deleteSign = true;
            return true;
        }
    }
    return false;
}

void saveClientDataIntoFile(string fileName, vector <stClientData> vClients)
{
    fstream myFile;

    myFile.open(fileName, ios::out);

    if (myFile.is_open())
    {
        for (stClientData C : vClients)
        {
            if (C.deleteSign == false)
            {
                string dataLine = returnClientData(C);
                myFile << dataLine << endl;
            }
        }
        myFile.close();
    }
}

void deleteClientData(string accNumber, vector <stClientData> & vClients)
{
    stClientData client;

    if (findClientDataByAccNumber(vClients, accNumber, client))
    {
        cout << endl;
        printClientDataByAccNumber(client, accNumber);
        cout << endl;

        cout << "Are You sure You want to delete this account data (Y/N)? ";
        char ans;
        cin >> ans;

        if (tolower(ans) == 'y')
        {
            markClientDeleteSign(accNumber, vClients);
            saveClientDataIntoFile(FileName, vClients);

            vClients = loadDataFileIntoVector(FileName);

            cout << "\nClient Deleted Successfully." << endl;
        }
    }
    else cout << "\nClient with Account Number (" << accNumber << ") is not found." << endl;
}

void changeClientRecord(string accNumber, vector <stClientData> & vClients)
{
    for (stClientData & client : vClients)
    {
        if (client.accountNumber == accNumber)
        {
            cout << "\nEnter PIN Code? ";
            cin >> client.pinCode;
            cin.ignore();

            cout << "Enter Name? ";
            getline(cin, client.name);

            cout << "Enter Phone? ";
            cin >> client.phone;

            cout << "Enter Account Balance? ";
            cin >> client.accountBalance;
        }
    }
}

void updateClientData(string accNumber, vector <stClientData> & vClients)
{
    stClientData client;

    if (findClientDataByAccNumber(vClients, accNumber, client))
    {
        cout << endl;
        printClientDataByAccNumber(client, accNumber);
        cout << endl;

        cout << "Are You sure You want to update this account data (Y/N)? ";
        char ans;
        cin >> ans;

        if (tolower(ans) == 'y')
        {
            changeClientRecord(accNumber, vClients);

            saveClientDataIntoFile(FileName, vClients);

            cout << "\nClient Updated Successfully." << endl;
        }
    }
    else cout << "\nClient with Account Number (" << accNumber << ") is not found." << endl;
}

short readMainMenuChoice()
{
    cout << "Choose What Do You Want to do? [1 to 7]? " ;
    short choice = 0;
    cin >> choice;
    return choice;
}

short readTransactionsChoice()
{
    cout << "Choose What Do You Want to do? [1 to 4]? " ;
    short choice = 0;
    cin >> choice;
    return choice;
}

void changeAccBalance(int amount, vector <stClientData> & vClients, string accNumber)
{
    char ans = 'n';

    cout << "\n\nAre you sure you want to perform this transactions? (Y/N) ";
    cin >> ans;

    if (tolower(ans) == 'y')
    {
        for (stClientData & c : vClients)
        {
            if (c.accountNumber == accNumber)
            {
                c.accountBalance += amount;
                saveClientDataIntoFile(FileName, vClients);
                cout << "Done Successfully, Account Total Balance: " << c.accountBalance << endl;
            }
        }
    }
}

void deposit(string accNumber, vector <stClientData> & vClients)
{
    stClientData client;

    while(!findClientDataByAccNumber(vClients, accNumber, client))
    {
        cout << "\n\nClient with Account Number (" << accNumber << ") does not found.,Please enter Account Number ";
        accNumber = readAccountNumber();
    }

    printClientDataByAccNumber(client, accNumber);

    double depositAmount = 0;

    cout << "\n\nPlease enter Deposit Amount? ";
    cin >> depositAmount;

    changeAccBalance(depositAmount, vClients, accNumber);

}

void withdraw(string accNumber, vector <stClientData> & vClients)
{
    stClientData client;

    while(!findClientDataByAccNumber(vClients, accNumber, client))
    {
        cout << "\n\nClient with Account Number (" << accNumber << ") does not found.,Please enter Account Number ";
        accNumber = readAccountNumber();
    }

    printClientDataByAccNumber(client, accNumber);

    double withdrawAmount = 0;

    cout << "\n\nPlease enter Withdraw Amount? ";
    cin >> withdrawAmount;

    while (withdrawAmount > client.accountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to: " << client.accountBalance << endl;
        cout << "Please enter Withdraw Amount? ";
        cin >> withdrawAmount;
    }

    changeAccBalance(-withdrawAmount, vClients, accNumber);

}

double getSumAccountsBalance(vector <stClientData> vClient)
{
    int sum = 0;
    for (stClientData & client : vClient)
    {
        sum += client.accountBalance;
    }
    return sum;
}

void printClientBalanceData(stClientData clientData)
{
    cout << setw(25) << left << clientData.accountNumber;
    cout << setw(30) << left << clientData.name;
    cout << setw(12) << left << clientData.accountBalance;
}

void printClientsBalanceData(vector <stClientData> vClients)
{
    cout << "\n\n";
    cout << "\t\t\t Clients List (" << vClients.size() << "):" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << left << setw(25) << "Account Number:";
    cout << left << setw(30) << "Name:";
    cout << left << setw(12) << "Balance:" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for (stClientData client : vClients)
    {
        printClientBalanceData(client);
        cout << endl;
    }
    cout << "---------------------------------------------------------------------\n\n";
    cout << "\t\t\t Total Balances = " << getSumAccountsBalance(vClients) << endl << endl;
}

void performTransactionsChoice(enTransactionChoice transactionChoice)
{
    vector <stClientData> vClients = loadDataFileIntoVector(FileName);
    switch (transactionChoice)
    {
        case enTransactionChoice::Deposit :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Deposit Screen" << endl;
            cout << "-----------------------------------------------------------\n";

            string accNumber = readAccountNumber();
            deposit(accNumber, vClients);
            break;
        }
        case enTransactionChoice::Withdraw :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Withdraw Screen" << endl;
            cout << "-----------------------------------------------------------\n";

            string accNumber = readAccountNumber();
            withdraw(accNumber, vClients);
            break;
        }
        case enTransactionChoice::TotalBalances :
        {
            printClientsBalanceData(vClients);
            break;
        }
        case enTransactionChoice::MainMenu :
        {
            showMainMenu();
            break;
        }
    }

}

void showTransactionsMenu()
{
    cout << "\n\n==============================================\n" ;
    cout << "\tTransactions Menu Screen\n" ;
    cout << "==============================================\n" ;
    cout << "\t[1] Deposit.\n" ;
    cout << "\t[2] Withdraw.\n" ;
    cout << "\t[3] Total Balances.\n" ;
    cout << "\t[4] Main Menu.\n" ;
    cout << "==============================================\n" ;
    performTransactionsChoice((enTransactionChoice)readTransactionsChoice());
}

void performMainMenuChoice(enChoice choice)
{
    vector <stClientData> vClients = loadDataFileIntoVector(FileName);
    switch (choice)
    {
        case enChoice::ShowClientList :
        {
            printClientsData(vClients);
            break;
        }
        case enChoice::AddNewClient :
        {
            char ans = 'n';
            do
            {
                cout << "\n-----------------------------------------------------------\n";
                cout << "\t\t Adding New Client Screen" << endl;
                cout << "-----------------------------------------------------------\n";

                stClientData client = getClientData(vClients);
                addClient(returnClientData(client));
                cout << "Client Added Successfully, do you want to add more Clients (y/n)? ";
                cin >> ans;
            } while (tolower(ans) == 'y');
            break;
        }
        case enChoice::DeleteClient :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Adding New Client Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";

            string accNumber = readAccountNumber();
            deleteClientData(accNumber, vClients);
            break;
        }
        case enChoice::UpdateClientInfo :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Updating Client Info Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";
            string accNumber = readAccountNumber();
            updateClientData(accNumber, vClients);
            break;
        }
        case enChoice::FindClient :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Finding Client Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";

            string accNumber = readAccountNumber();
            stClientData client;

            if (findClientDataByAccNumber(vClients, accNumber, client))
            {
                printClientDataByAccNumber(client, accNumber);
            }
            else cout << "Client with Account Number (" << accNumber << ") is not found." << endl;
            break;
        }
        case enChoice::Transactions :
        {
            showTransactionsMenu();
            break;
        }
        case enChoice::Exit :
        {
            cout << "\n--------------------------------------------------------------\n";
            cout << "\t\tThanks For Using Our Service :-)" << endl;
            cout << "--------------------------------------------------------------\n";
            break;
        }
    }
}

void showMainMenu()
{
    cout << "==============================================\n" ;
    cout << "\t\tMain Menu Screen\n" ;
    cout << "==============================================\n" ;
    cout << "\t[1] Show Clients List.\n" ;
    cout << "\t[2] Add New Client.\n" ;
    cout << "\t[3] Delete Client.\n" ;
    cout << "\t[4] Update Client Info.\n" ;
    cout << "\t[5] Find Client.\n" ;
    cout << "\t[6] Transactions.\n" ;
    cout << "\t[7] Exit.\n" ;
    cout << "==============================================\n" ;
    performMainMenuChoice((enChoice)readMainMenuChoice());
}

int main()
{
    showMainMenu();
}