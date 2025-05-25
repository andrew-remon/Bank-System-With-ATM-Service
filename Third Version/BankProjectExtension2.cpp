#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

enum enChoice
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    ManageUsers = 7,
    LogOut = 8,
};

enum enTransactionChoice
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

enum enUserChoice
{
    ShowUserList = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUserInfo = 4,
    FindUser = 5,
    MainMenue = 6,
};

struct stClientData
{
    string accountNumber, name, phone, pinCode;
    double accountBalance;
    bool deleteSign = false;
};

struct stPermissions
{
    bool showing = false, adding = false, deleting = false, updating = false, finding = false,
        transactions = false, managingUsers = false;
};

struct stUserData
{
    string name, password;
    stPermissions permissions;
    short accessValue;
    bool deleteSign = false;
};

string ClientFile = "bank_data.txt";
string UserFile = "users.txt";
stUserData loggedInUser;

void showMainMenu();
void showLogInScreen();
void showUserMenu();
void printAccessDeniedMessage();
bool isUserHasPermission();

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

void addClientDataToFile(string clientRecord)
{
    fstream myFile;

    myFile.open(ClientFile, ios::out | ios::app);

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

void saveClientDataIntoFile(string ClientFile, vector <stClientData> vClients)
{
    fstream myFile;

    myFile.open(ClientFile, ios::out);

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
            saveClientDataIntoFile(ClientFile, vClients);

            vClients = loadClientDataFileIntoVector(ClientFile);

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

            saveClientDataIntoFile(ClientFile, vClients);

            cout << "\nClient Updated Successfully." << endl;
        }
    }
    else cout << "\nClient with Account Number (" << accNumber << ") is not found." << endl;
}

short readMainMenuChoice()
{
    cout << "Choose What Do You Want to do? [1 to 8]? " ;
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
                saveClientDataIntoFile(ClientFile, vClients);
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
    vector <stClientData> vClients = loadClientDataFileIntoVector(ClientFile);
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
    vector <stClientData> vClients = loadClientDataFileIntoVector(ClientFile);
    switch (choice)
    {
        case enChoice::ShowClientList :
        {
            if (isUserHasPermission())
            printClientsData(vClients);
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::AddNewClient :
        {
            char ans = 'n';
            if (isUserHasPermission())
            {
                do
                {
                    cout << "\n-----------------------------------------------------------\n";
                    cout << "\t\t Adding New Client Screen" << endl;
                    cout << "-----------------------------------------------------------\n";

                    stClientData newClient = getClientData(vClients);
                    addClientDataToFile(returnClientData(newClient));
                    cout << "Client Added Successfully, do you want to add more Clients (y/n)? ";
                    cin >> ans;
                } while (tolower(ans) == 'y');
            }
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::DeleteClient :
        {
            if (isUserHasPermission())
            {
                cout << "\n-----------------------------------------------------------\n";
                cout << "\t\t Delete Client Screen" << endl;
                cout << "-----------------------------------------------------------\n\n";

                string accNumber = readAccountNumber();
                deleteClientData(accNumber, vClients);
            }
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::UpdateClientInfo :
        {
            if (isUserHasPermission())
            {
                cout << "\n-----------------------------------------------------------\n";
                cout << "\t\t Updating Client Info Screen" << endl;
                cout << "-----------------------------------------------------------\n\n";
                string accNumber = readAccountNumber();
                updateClientData(accNumber, vClients);
            }
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::FindClient :
        {
            if (isUserHasPermission())
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
            }
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::Transactions :
        {
            if (isUserHasPermission())
            showTransactionsMenu();
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::ManageUsers :
        {
            if (isUserHasPermission())
            showUserMenu();
            else printAccessDeniedMessage();
            break;
        }
        case enChoice::LogOut :
        {
            showLogInScreen();
        }
        // Old Case
        // case enChoice::Exit :
        // {
        //     cout << "\n--------------------------------------------------------------\n";
        //     cout << "\t\tThanks For Using Our Service :-)" << endl;
        //     cout << "--------------------------------------------------------------\n";
        //     break;
        // }
    }
}

void showMainMenu()
{
    cout << "\n==============================================\n" ;
    cout << "\t\tMain Menu Screen\n" ;
    cout << "==============================================\n" ;
    cout << "\t[1] Show Clients List.\n" ;
    cout << "\t[2] Add New Client.\n" ;
    cout << "\t[3] Delete Client.\n" ;
    cout << "\t[4] Update Client Info.\n" ;
    cout << "\t[5] Find Client.\n" ;
    cout << "\t[6] Transactions.\n" ;
    cout << "\t[7] Manage Users.\n" ;
    cout << "\t[8] Log Out.\n" ;
    cout << "==============================================\n" ;
    performMainMenuChoice((enChoice)readMainMenuChoice());
}

// ------------------- Extension 2 -------------------------

stUserData extractUserData(string statement, string sep)
{
    stUserData userData;
    vector <string> vWords;

    split(statement, vWords, sep);

    userData.name = vWords[0];
    userData.password = vWords[1];
    userData.accessValue = stod(vWords[2]);

    return userData;
}

void rebuildPermissionsFromAccessValue(stUserData &user)
{
    int access = user.accessValue;
    user.permissions.showing        = access & 1;
    user.permissions.adding         = access & 2;
    user.permissions.deleting       = access & 4;
    user.permissions.updating       = access & 8;
    user.permissions.finding        = access & 16;
    user.permissions.transactions   = access & 32;
    user.permissions.managingUsers = access & 64;
}

vector <stUserData> loadUserDataFileIntoVector(string UserFile)
{
    vector <stUserData> vUsers;

    fstream myFile;
    myFile.open(UserFile, ios::in);

    if (myFile.is_open())
    {
        string line;
        stUserData user;

        while(getline(myFile, line))
        {
            user = extractUserData(line, "#//#");

            // add the permissions flags after extracting the data from the file.
            rebuildPermissionsFromAccessValue(user);

            vUsers.push_back(user);
        }

        myFile.close();
    }

    return vUsers;
}

int manageUserAccess(stUserData & user)
{
    int totalAccess = 0;
    char answer;

    cout << "\nDo You want to Full Access? (y/n) ";
    cin >> answer;

    if (tolower(answer) == 'y') return -1;

    cout << "\nDo you want to give Access to: \n";

    cout << "Show Client List? (y/n) ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 1;
        user.permissions.showing = true;
    }

    cout << "Add New Client? (y/n) ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 2;
        user.permissions.adding = true;
    }

    cout << "Delete Client? (y/n) ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 4;
        user.permissions.deleting = true;
    }

    cout << "Update Client? (y/n) ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 8;
        user.permissions.updating = true;
    }

    cout << "Find Client? (y/n) ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 16;
        user.permissions.finding = true;
    }

    cout << "Transactions? (y/n)";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 32;
        user.permissions.transactions = true;
    }

    cout << "Manage Users? (y/n)";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        totalAccess |= 64;
        user.permissions.managingUsers = true;
    }

    return totalAccess;
}

bool checkUserAccountExist(stUserData & userData, vector <stUserData> vUsers)
{
    for (stUserData existedUser : vUsers)
    {
        if(userData.name == existedUser.name && userData.password == existedUser.password)
        {
            userData = existedUser;
            return true;
        }
    }
    return false;
}

bool checkUserNameExist(stUserData userData, vector <stUserData> vUsers)
{
    for (stUserData existedUser : vUsers)
    {
        if(existedUser.name == userData.name)
        {
            return true;
        }
    }
    return false;
}

bool isUserHasPermission()
{
    if (loggedInUser.permissions.showing == true || loggedInUser.accessValue == -1) return true;
    else return false;
}

void printUserDataByUserName(stUserData userFound, string userInputUserName)
{
    if (userFound.name == userInputUserName)
    {
        cout << "\nThe following are the Account Details: \n" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "Name: " << userFound.name << endl;
        cout << "Password: " << userFound.password << endl;
        cout << "Permissions: " << userFound.accessValue << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n\n";
    }
}

stUserData getUserData(vector <stUserData> & vUsers)
{
    stUserData userData;

    cout << "\nAdding New User:\n\n";

    cout << "Enter User Name? ";
    cin >> userData.name;

    while(checkUserNameExist(userData, vUsers))
    {
        cout << "User with [" << userData.name << "] exists, enter another User Name? ";
        cin >> userData.name;
    }

    cout << "Enter Password? ";
    cin >> userData.password;
    cin.ignore();

    userData.accessValue = manageUserAccess(userData);

    return userData;
}

string returnUserData(stUserData userData, string sep = "#//#")
{
    string userRecord = "";

    userRecord += userData.name  + sep;
    userRecord += userData.password + sep;
    userRecord += to_string(userData.accessValue);

    return userRecord;
}

void addUserDataToFile(string userRecord)
{
    fstream myFile;

    myFile.open(UserFile, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << userRecord << endl;
        myFile.close();
    }
}

bool findUserDataByUserName(vector <stUserData> vUsers, string inputUserName, stUserData & user)
{
    for (stUserData u : vUsers)
    {
        if (u.name == inputUserName)
        {
            user = u;
            return true;
        }
    }
    return false;
}

string readInput(string message)
{
    string input;
    cout << message;
    cin >> input;
    return input;
}

void printUserData(stUserData userData)
{
    cout << setw(17) << left << userData.name;
    cout << setw(18) << left << userData.password;
    cout << setw(10) << left << userData.accessValue;
}

void printUsersData(vector <stUserData> vUsers)
{
    cout << "\n\n";
    cout << "\t\t Clients List (" << vUsers.size() << "):" << endl;
    cout << "------------------------------------------------------\n";
    cout << left << setw(17) << "Name:";
    cout << left << setw(18) << "Password:";
    cout << left << setw(10) << "Permissions:\n";
    cout << "------------------------------------------------------\n";

    for (stUserData user : vUsers)
    {
        printUserData(user);
        cout << endl;
    }
    cout << "------------------------------------------------------\n";
}

void login()
{
    vector <stUserData> vUsers = loadUserDataFileIntoVector(UserFile);
    do
    {
        loggedInUser.name = readInput("Enter UserName? ");
        loggedInUser.password = readInput("Enter Password? ");
        if(!checkUserAccountExist(loggedInUser, vUsers)) cout << "\nInvalid UserName/Password!\n";
    } while (!checkUserAccountExist(loggedInUser, vUsers));
}

void showLogInScreen()
{
    cout << "----------------------------------------------\n" ;
    cout << "\t\tLogin Screen\n" ;
    cout << "----------------------------------------------\n" ;
    login();
    showMainMenu();
}

short readUserChoice()
{
    cout << "Choose What Do You Want to do? [1 to 6]? " ;
    short choice = 0;
    cin >> choice;
    return choice;
}

void printAccessDeniedMessage()
{
    cout << "\n------------------------------------------------------------------\n";
    cout << "This User Doesn't have the permission, Please Contact the Admin.\n";
    cout << "------------------------------------------------------------------\n";
}

bool markUserDeleteSign(string userName, vector <stUserData> & vUsers)
{
    for (stUserData & user : vUsers)
    {
        if (user.name == userName)
        {
            user.deleteSign = true;
            return true;
        }
    }
    return false;
}

void saveUserDataIntoFile(string UserFile, vector <stUserData> vUsers)
{
    fstream myFile;

    myFile.open(UserFile, ios::out);

    if (myFile.is_open())
    {
        for (stUserData user : vUsers)
        {
            if (user.deleteSign == false)
            {
                string dataLine = returnUserData(user);
                myFile << dataLine << endl;
            }
        }
        myFile.close();
    }
}

void deleteUserData(string userName, vector <stUserData> & vUsers)
{
    stUserData user;

    if (userName == "Admin")
    {
        cout << "\nThis User Can't Be Deleted, Please Contact The Admin For More Information.";
        return;
    }

    if (findUserDataByUserName(vUsers, userName, user))
    {
        cout << endl;
        printUserDataByUserName(user, userName);
        cout << endl;

        cout << "Are You sure You want to delete this account data (Y/N)? ";
        char ans;
        cin >> ans;

        if (tolower(ans) == 'y')
        {
            markUserDeleteSign(userName, vUsers);
            saveUserDataIntoFile(UserFile, vUsers);

            vUsers = loadUserDataFileIntoVector(UserFile);

            cout << "\nUser Deleted Successfully." << endl;
        }
    }
    else cout << "\nUser with UserName (" << userName << ") is not found." << endl;
}

void changeUserRecord(string userName, vector <stUserData> & vUsers)
{
    for (stUserData & user : vUsers)
    {
        if (user.name == userName)
        {
            cout << "\nEnter Password? ";
            cin >> user.password;

            user.accessValue = manageUserAccess(user);
        }
    }
}

void updateUserData(string userName, vector <stUserData> & vUsers)
{
    stUserData user;

    if (userName == "Admin")
    {
        cout << "\nThis User Can't Be Updated, Please Contact The Admin For More Information.";
        return;
    }

    if (findUserDataByUserName(vUsers, userName, user))
    {
        cout << endl;
        printUserDataByUserName(user, userName);
        cout << endl;

        cout << "Are You sure You want to update this account data (Y/N)? ";
        char ans;
        cin >> ans;

        if (tolower(ans) == 'y')
        {
            changeUserRecord(userName, vUsers);

            saveUserDataIntoFile(UserFile, vUsers);

            cout << "\nUser Updated Successfully." << endl;
        }
    }
    else cout << "\nUser with User Name (" << userName << ") is not found." << endl;
}

void performUserChoice(enUserChoice userChoice)
{
    vector <stUserData> vUsers = loadUserDataFileIntoVector(UserFile);

    switch (userChoice)
    {
        case enUserChoice::ShowUserList :
        {
            printUsersData(vUsers);
            break;
        }
        case enUserChoice::AddNewUser :
        {
            char ans = 'n';
            do
            {
                cout << "\n-----------------------------------------------------------\n";
                cout << "\t\t Adding New User Screen" << endl;
                cout << "-----------------------------------------------------------\n";
                stUserData newUser = getUserData(vUsers);
                addUserDataToFile(returnUserData(newUser));
                cout << "User Added Successfully, do you want to add more Users (y/n)? ";
                cin >> ans;
            } while (tolower(ans) == 'y');
            break;
        }
        case enUserChoice::DeleteUser :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Delete User Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";

            string userName = readInput("Please Enter User Name? ");
            deleteUserData(userName, vUsers);
            break;
        }
        case enUserChoice::UpdateUserInfo :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Updating User Info Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";
            string userName = readInput("Please Enter User Name? ");
            updateUserData(userName, vUsers);
            break;
        }
        case enUserChoice::FindUser :
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "\t\t Finding User Screen" << endl;
            cout << "-----------------------------------------------------------\n\n";

            stUserData user;
            string userName = readInput("Please Enter User Name? ");

            if (findUserDataByUserName(vUsers, userName, user))
            {
                printUserDataByUserName(user, userName);
            }
            else cout << "Client with Account Number (" << userName << ") is not found." << endl;
            break;
        }
        case enUserChoice::MainMenue:
        {
            showMainMenu();
            break;
        }
    }
}

void showUserMenu()
{
    cout << "\n\n==============================================\n" ;
    cout << "\t\tUser Menu Screen\n" ;
    cout << "==============================================\n" ;
    cout << "\t[1] show Users List.\n" ;
    cout << "\t[2] Add New User.\n" ;
    cout << "\t[3] Delete User.\n" ;
    cout << "\t[4] Update User Info.\n" ;
    cout << "\t[5] Find User.\n" ;
    cout << "\t[6] Main Menu.\n" ;
    cout << "==============================================\n" ;
    performUserChoice((enUserChoice)readUserChoice());
}

int main()
{
    showLogInScreen();
}