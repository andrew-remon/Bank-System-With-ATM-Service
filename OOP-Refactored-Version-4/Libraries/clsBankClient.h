#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidation.h"
#include "clsUtil.h"
#include "clsGlobal.h"
#include "clsEnums.h"
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddMode = 2};
    enMode _mode;

    string _pinCode;
    string _accountNumber;
    float  _accountBalance;
    bool   _deleteSign = false;

    static clsBankClient _convertLineIntoClientObject(string line, string separator = "#//#")
    {
        vector <string> vClientData;
        clsString::split(line, vClientData, separator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static vector <clsBankClient> _loadDataFileIntoVector(string fileName)
    {
        vector <clsBankClient> vClients;

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line;

            while(getline(myFile, line))
            {
                clsBankClient client = _convertLineIntoClientObject(line, "#//#");
                vClients.push_back(client);
            }
            myFile.close();
        }
        return vClients;
    }

    static clsBankClient _getEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static clsBankClient _getAddClientObject(string accountNumber)
    {
        return clsBankClient(enMode::AddMode, "", "", "", "", "", accountNumber, 0);
    }

    static string _returnClientData(clsBankClient clientData, string sep = "#//#")
    {
        string clientRecord = "";

        clientRecord += clientData.getFirstName()  + sep;
        clientRecord += clientData.getLastName() + sep;
        clientRecord += clientData.getEmail()   + sep;
        clientRecord += clientData.getPhone()   + sep;
        clientRecord += clientData.getPinCode()   + sep;
        clientRecord += clientData.getAccountNumber()   + sep;
        clientRecord += to_string(clientData.getAccountBalance());

        return clientRecord;
    }

    static void _saveClientDataIntoFile(string fileName, vector <clsBankClient> vClients)
    {
        fstream myFile;

        myFile.open(fileName, ios::out);

        if (myFile.is_open())
        {
            for (clsBankClient & C : vClients)
            {
                if (C.getDeleteSign() == false)
                {
                    string dataLine = _returnClientData(C);
                    myFile << dataLine << endl;
                }
            }
            myFile.close();
        }
    }

    static void _changeClientRecord(string accountNumber, vector <clsBankClient> & vClients)
    {
        for (clsBankClient & client : vClients)
        {
            if (client._accountNumber == accountNumber)
            {
                cout << "Enter First Name? ";
                client.setFirstName(clsInputValidation::readString());

                cout << "Enter Last Name? ";
                client.setLastName(clsInputValidation::readString());

                cout << "Enter Email? ";
                client.setEmail(clsInputValidation::readString());

                cout << "Enter Phone? ";
                client.setPhone(clsInputValidation::readString());

                cout << "Enter PIN Code? ";
                client._pinCode = clsInputValidation::readString();

                cout << "Enter Account Balance? ";
                client._accountBalance = clsInputValidation::readDblNumber("Invalid Number, Enter A valid Number: ");
            }
        }
    }

    static void _changeClientRecord(clsBankClient & client)
    {
        cout << "Enter First Name? ";
        client.setFirstName(clsInputValidation::readString());

        cout << "Enter Last Name? ";
        client.setLastName(clsInputValidation::readString());

        cout << "Enter Email? ";
        client.setEmail(clsInputValidation::readString());

        cout << "Enter Phone? ";
        client.setPhone(clsInputValidation::readString());

        cout << "Enter PIN Code? ";
        client.setPinCode(clsInputValidation::readString());

        cout << "Enter Account Balance? ";
        client.setAccountBalance(clsInputValidation::readDblNumber("Invalid Number, Enter A valid Number: "));
    }

    static void _markClientDeleteSign(clsBankClient & client, vector <clsBankClient> & vClients)
    {
        client.setDeleteSign(true);
    }

    static void _showClientBalance(clsBankClient clientData)
    {
        cout << "| " << setw(17) << left << clientData.getAccountNumber();
        cout << "| " << setw(20) << left << clientData.FullName();
        cout << "| " << setw(12) << left << clientData.getAccountBalance();
    }

public:

    clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string pinCode, string accountNumber, float accountBalance) : clsPerson(firstName, lastName, email, phone)
    {
        _mode = mode;
        _pinCode = pinCode;
        _accountNumber = accountNumber;
        _accountBalance = accountBalance;
    }

    void setPinCode(string pinCode)
    {
        _pinCode = pinCode;
    }

    void setAccountBalance(float accountBalance)
    {
        _accountBalance = accountBalance;
    }

    void setDeleteSign(bool value)
    {
        _deleteSign = value;
    }

    string getAccountNumber()
    {
        return _accountNumber;
    }

    float getAccountBalance()
    {
        return _accountBalance;
    }

    string getPinCode()
    {
        return _pinCode;
    }

    bool getDeleteSign()
    {
        return _deleteSign;
    }

    void print()
    {
        cout << "\nClient Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << getFirstName() << endl;
        cout << "Last Name: " << getLastName() << endl;
        cout << "Full Name: " << FullName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Phone: " << getPhone() << endl;
        cout << "Account Number: " << getAccountNumber() << endl;
        cout << "PIN Code: " << getPinCode() << endl;
        cout << "Account Balance: " << getAccountBalance() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }

    bool isEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }

    static vector <clsBankClient> getClientListVector(string fileName)
    {
        return _loadDataFileIntoVector(fileName);
    }

    static clsBankClient findClient(string accountNumber)
    {
        vector <clsBankClient> vClients = _loadDataFileIntoVector(ClientsDataFile);
        for (clsBankClient & client: vClients)
        {
            if (client.getAccountNumber() == accountNumber)
            {
                return client;
            }
        }
        return _getEmptyClientObject();
    }

    static clsBankClient & findClientRef(string accountNumber, vector <clsBankClient> & vClients)
    {
        for (clsBankClient & client: vClients)
        {
            if (client.getAccountNumber() == accountNumber)
            {
                return client;
            }
        }
        throw runtime_error("Client Not Found");
    }

    // static clsBankClient find(string accountNumber)
    // {
    //     fstream myFile;
    //     myFile.open(FileName, ios::in);
    //     if (myFile.is_open())
    //     {
    //         string line;
    //         while (getline(myFile, line))
    //         {
    //             clsBankClient client = _convertLineIntoClientObject(line);
    //             if (client._accountNumber == accountNumber)
    //             {
    //                 myFile.close();
    //                 return client;
    //             }
    //         }
    //         myFile.close();
    //     }
    //     return _getEmptyClientObject();
    // }

    static bool isClientExist(string accountNumber)
    {
        clsBankClient client = findClient(accountNumber);
        return (!client.isEmpty());
    }

    void updateInfo()
    {
        vector <clsBankClient> vClients = _loadDataFileIntoVector(ClientsDataFile);

        this->print();

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            if (this->_mode == enMode::UpdateMode)
            {
                cout << "\n--------------------\n";
                cout << "Update Client Info.\n";
                cout << "--------------------\n" << endl;

                _changeClientRecord(*this);

                // * to update the vector and the file with the new client record
                for (clsBankClient &client: vClients)
                {
                    if (client.getAccountNumber() == this->getAccountNumber())
                    {
                        client = *this;
                        break;
                    }
                }

                _saveClientDataIntoFile(ClientsDataFile, vClients);

                cout << "\nClient Updated Successfully." << endl;
            }
            else cout << "\nUpdate Failed, It's an empty object.";
        }
    }

    void deleteInfo()
    {
        vector <clsBankClient> vClients = _loadDataFileIntoVector(ClientsDataFile);

        if (!this->isEmpty())
        {
            this->print();

            char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

            if (tolower(ans) == 'y')
            {
                _markClientDeleteSign(*this, vClients);

                // * to delete the client from the vector and the file.
                for (clsBankClient &client: vClients)
                {
                    if (client.getAccountNumber() == this->getAccountNumber())
                    {
                        client = *this;
                        break;
                    }
                }

                _saveClientDataIntoFile(ClientsDataFile, vClients);
                *this = _getEmptyClientObject();
                cout << "\nClient Deleted Successfully." << endl;
            }
        }
        else cout << "\nAccount Not found, Please Try Again." << endl;
    }

    static double calculateTotalBalances()
    {
        vector <clsBankClient> vClients = _loadDataFileIntoVector(ClientsDataFile);

        double totalBalances;
        for (clsBankClient & client: vClients)
        {
            totalBalances += client.getAccountBalance();
        }
        return totalBalances;
    }

    static void showTotalBalances()
    {
        vector <clsBankClient> vClients = _loadDataFileIntoVector(ClientsDataFile);

        cout << "\n\n";
        cout << "\t\t Clients List (" << vClients.size() << "):" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "| " << left << setw(17) << "Account Number:";
        cout << "| " << left << setw(20) << "Client Name:";
        cout << "| " << left << setw(12) << "Balance:" << endl;
        cout << "-----------------------------------------------------------" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\t\tNo Data Available in the System" << endl;
        }

        for (clsBankClient & client : vClients)
        {
            _showClientBalance(client);
            cout << endl;
        }

        cout << "-----------------------------------------------------------" << endl;
        double totalBalances = calculateTotalBalances();
        cout << "\nTotal Balances: " << totalBalances << endl;
        cout << clsUtil::getNumberInLetterForm(to_string(totalBalances));
    }

    static void changeAccBalance(double amount, vector <clsBankClient> & vClients, clsBankClient & client)
    {
        char ans = clsUtil::confirm("Are you sure you want to perform this transaction? (Y/N) ");

        if (tolower(ans) == 'y')
        {
            client.setAccountBalance(client.getAccountBalance() + amount);
            _saveClientDataIntoFile(ClientsDataFile, vClients);
            cout << "Done Successfully, New Account Total Balance: " << client.getAccountBalance() << endl;
        }
    }

    static string readAccountNumber(enStatus status)
    {
        cout << "Please Enter an Account Number: ";
        string accountNumber = clsInputValidation::readString();

        switch(status)
        {
            case enStatus::Exist:
            {
                while(!clsBankClient::isClientExist(accountNumber))
                {
                    cout << "Account Number not found, Please enter an existed one: ";
                    accountNumber = clsInputValidation::readString();
                }
                break;
            }
            case enStatus::New:
            {
                while(clsBankClient::isClientExist(accountNumber))
                {
                    cout << "Account Number found, Please enter a new one: ";
                    accountNumber = clsInputValidation::readString();
                }
            }
        }


        return accountNumber;
    }

    friend class clsAddNewClientScreen;
    friend class clsDeleteClientScreen;
    friend class clsUpdateClientScreen;
};
