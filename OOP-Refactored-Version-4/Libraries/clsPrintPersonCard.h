#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsBankUser.h"
using namespace std;

class clsPrintPersonCard
{
public:
    static void printClientInfo(clsBankClient client)
    {
        cout << "\nClient Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << client.getFirstName() << endl;
        cout << "Last Name: " << client.getLastName() << endl;
        cout << "Full Name: " << client.FullName() << endl;
        cout << "Email: " << client.getEmail() << endl;
        cout << "Phone: " << client.getPhone() << endl;
        cout << "Account Number: " << client.getAccountNumber() << endl;
        cout << "PIN Code: " << client.getPinCode() << endl;
        cout << "Account Balance: " << client.getAccountBalance() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }

    static void printUserInfo(clsBankUser user)
    {
        cout << "\nUser Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << user.getFirstName() << endl;
        cout << "Last Name: " << user.getLastName() << endl;
        cout << "Full Name: " << user.FullName() << endl;
        cout << "Email: " << user.getEmail() << endl;
        cout << "Phone: " << user.getPhone() << endl;
        cout << "UserName: " << user.getUserName() << endl;
        cout << "Password: " << user.getPassword() << endl;
        cout << "Access Value: " << user.getAccessValue() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }
};
