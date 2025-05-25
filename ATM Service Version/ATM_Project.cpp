#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

enum enClientChoice {
    QuickWithdraw = 1,
    Withdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    LogOut = 5,
    Exit = 6,
};

struct stClientData
{
    string accountNumber, name, phone, pinCode;
    double accountBalance;
};

string ClientFile = "bank_data.txt";
stClientData loggedInClient;

void showLogInScreen();

string readInput(string message)
{
    string input;
    cout << message;
    cin >> input;
    return input;
}

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

vector <stClientData> loadClientDataFileIntoVector(string ClientFile)
{
    vector <stClientData> vClients;

    fstream myFile;
    myFile.open(ClientFile, ios::in);

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

string returnClientDataIntoString(stClientData clientData, string sep = "#//#")
{
    string clientRecord = "";

    clientRecord += clientData.accountNumber  + sep;
    clientRecord += clientData.pinCode + sep;
    clientRecord += clientData.name    + sep;
    clientRecord += clientData.phone   + sep;
    clientRecord += to_string(clientData.accountBalance);

    return clientRecord;
}

void saveClientDataIntoFile(string ClientFile, vector <stClientData> vClients)
{
    fstream myFile;

    myFile.open(ClientFile, ios::out);

    if (myFile.is_open())
    {
        for (stClientData C : vClients)
        {
            string dataLine = returnClientDataIntoString(C);
            myFile << dataLine << endl;
        }
        myFile.close();
    }
}

bool isClientExist(stClientData& clientData, vector <stClientData> vClients)
{
    for (stClientData existedClient : vClients)
    {
        if(clientData.accountNumber == existedClient.accountNumber && clientData.pinCode == existedClient.pinCode)
        {
            clientData = existedClient;
            return true;
        }
    }
    return false;
}

void changeAccBalance(int amount, vector <stClientData> & vClients, string accNumber)
{
    char ans = 'n';

    cout << "\nAre you sure you want to perform this transactions? (Y/N) ";
    cin >> ans;

    if (tolower(ans) == 'y')
    {
        for (stClientData & c : vClients)
        {
            if (c.accountNumber == accNumber)
            {
                c.accountBalance += amount;
                saveClientDataIntoFile(ClientFile, vClients);
                cout << "\nDone Successfully, Account Total Balance: " << c.accountBalance << endl;
            }
        }
    }
}

void deposit(string accNumber, vector <stClientData> & vClients)
{
    double depositAmount = 0;

    do
    {
        cout << "\nPlease enter Deposit Amount? ";
        cin >> depositAmount;

        if (depositAmount <= 0) cout << "\nInvalid Amount of Money, PLease Try Again. ";
    } while (depositAmount <= 0);

    changeAccBalance(depositAmount, vClients, accNumber);
}

void withdraw(string accNumber, vector <stClientData> & vClients)
{
    double withdrawAmount = 0;
    do
    {
        cout << "\nPlease enter Withdraw Amount Multiple of 5's ? ";
        cin >> withdrawAmount;

        if (withdrawAmount <= 0 || (long long)withdrawAmount % 5 != 0)
            cout << "\nInvalid Amount of Money, PLease Try Again. ";
        if (withdrawAmount > loggedInClient.accountBalance)
        {
            cout << "\nAmount Exceeds the balance, you can withdraw up to: " << loggedInClient.accountBalance << endl;
        }

    } while (withdrawAmount <= 0 || (long long)withdrawAmount % 5 != 0 || withdrawAmount > loggedInClient.accountBalance);

    changeAccBalance(-withdrawAmount, vClients, accNumber);
}

enum enQWithdrawAmount
{
    Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundred = 4, FourHundred = 5, SixHundred = 6,
    EightHundred = 7, OneThousand = 8, TwoThousand = 9, FiveThousand = 10, WithdrawExit = 11,
};

short readQuickWithdrawChoice()
{
    short choice = 0;
    do
    {
        cout << "Choose What Do You Want to do? [1 to 11]? " ;
        cin >> choice;

        if (choice > 11 || choice < 1) cout << "\nInvalid Input, Please Try Again. ";
    } while (choice > 11 || choice < 1);
    return choice;
}

void performQuickWithdrawChoice(enQWithdrawAmount choice)
{
    vector <stClientData> vClients = loadClientDataFileIntoVector(ClientFile);

    short quickWithdrawAmount = 0;

    switch (choice)
    {
    case enQWithdrawAmount::Twenty :
    {
        quickWithdrawAmount = 20;
        break;
    }
    case enQWithdrawAmount::Fifty :
    {
        quickWithdrawAmount = 50;
        break;
    }
    case enQWithdrawAmount::OneHundred :
    {
        quickWithdrawAmount = 100;
        break;
    }
    case enQWithdrawAmount::TwoHundred :
    {
        quickWithdrawAmount = 200;
        break;
    }
    case enQWithdrawAmount::FourHundred :
    {
        quickWithdrawAmount = 400;
        break;
    }
    case enQWithdrawAmount::SixHundred :
    {
        quickWithdrawAmount = 600;
        break;
    }
    case enQWithdrawAmount::EightHundred :
    {
        quickWithdrawAmount = 800;
        break;
    }
    case enQWithdrawAmount::OneThousand :
    {
        quickWithdrawAmount = 1000;
        break;
    }
    case enQWithdrawAmount::TwoThousand :
    {
        quickWithdrawAmount = 2000;
        break;
    }
    case enQWithdrawAmount::FiveThousand :
    {
        quickWithdrawAmount = 5000;
        break;
    }
    default:
    {
        return;
    }
    }
    changeAccBalance(-quickWithdrawAmount, vClients, loggedInClient.accountNumber);
}

void showQuickWithdrawScreen()
{
    cout << "\n--------------------------------------------------------------\n";
    cout << "\t\tQuick Withdraw Screen" << endl;
    cout << "--------------------------------------------------------------\n";
    cout << "\t [1] 20 \t\t [2] 50\n";
    cout << "\t [2] 100 \t\t [4] 200\n";
    cout << "\t [5] 400 \t\t [6] 600\n";
    cout << "\t [7] 800 \t\t [8] 1000\n";
    cout << "\t [9] 2000 \t\t [10] 50000\n";
    cout << "\t [11] exit\n";
    cout << "--------------------------------------------------------------\n";
    cout << "Your Balance is " << loggedInClient.accountBalance << endl;
    performQuickWithdrawChoice((enQWithdrawAmount)readQuickWithdrawChoice());
}

short readATMMenuChoice()
{
    short choice = 0;
    do
    {
        cout << "Choose What Do You Want to do? [1 to 6]? " ;
        cin >> choice;

        if (choice > 11 || choice < 1) cout << "\nInvalid Input, Please Try Again. ";
    } while (choice > 11 || choice < 1);
    return choice;
}

void performATMMenuChoice(enClientChoice choice)
{
    vector <stClientData> vClients = loadClientDataFileIntoVector(ClientFile);
    switch (choice)
    {
        case enClientChoice::QuickWithdraw :
        {
            showQuickWithdrawScreen();
            break;
        }
        case enClientChoice::Withdraw :
        {
            cout << "\n--------------------------------------------------------------\n";
            cout << "\t\tWithdraw Screen" << endl;
            cout << "--------------------------------------------------------------\n";
            withdraw(loggedInClient.accountNumber, vClients);
            break;
        }
        case enClientChoice::Deposit :
        {
            cout << "\n--------------------------------------------------------------\n";
            cout << "\t\tDeposit Screen" << endl;
            cout << "--------------------------------------------------------------\n";
            deposit(loggedInClient.accountNumber, vClients);
            break;
        }
        case enClientChoice::CheckBalance :
        {
            cout << "\n--------------------------------------------------------------\n";
            cout << "\t\tCheck Balance Screen" << endl;
            cout << "--------------------------------------------------------------\n";
            cout << "\nYour Balance is " << loggedInClient.accountBalance << ".\n";
            break;
        }
        case enClientChoice::LogOut :
        {
            showLogInScreen();
        }
        case enClientChoice::Exit :
        {
            cout << "\n--------------------------------------------------------------\n";
            cout << "\t\tThanks For Using Our Service :-)" << endl;
            cout << "--------------------------------------------------------------\n";
            break;
        }
    }
}

void showATMScreen()
{
    cout << "\n==============================================\n" ;
    cout << "\t\tATM Menu Screen\n" ;
    cout << "==============================================\n" ;
    cout << "\t [1] Quick Withdraw.\n" ;
    cout << "\t [2] Withdraw.\n" ;
    cout << "\t [3] Deposit.\n" ;
    cout << "\t [4] Check Balance.\n" ;
    cout << "\t [5] LogOut.\n" ;
    cout << "\t [6] Exit.\n" ;
    cout << "==============================================\n" ;
    performATMMenuChoice((enClientChoice)readATMMenuChoice());
}

void login()
{
    vector <stClientData> vClients = loadClientDataFileIntoVector(ClientFile);
    do
    {
        loggedInClient.accountNumber = readInput("Enter Account Number? ");
        loggedInClient.pinCode = readInput("Enter PinCode? ");
        if(!isClientExist(loggedInClient, vClients)) cout << "\nInvalid Account Number/PinCode!\n";
    } while (!isClientExist(loggedInClient, vClients));
}

void showLogInScreen()
{
    cout << "----------------------------------------------\n" ;
    cout << "\t\tLogin Screen\n" ;
    cout << "----------------------------------------------\n" ;
    login();
    showATMScreen();
}

int main()
{
    showLogInScreen();
    cout << loggedInClient.accountBalance;
}