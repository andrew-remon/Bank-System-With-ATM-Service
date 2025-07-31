#pragma once
#include <iostream>
using namespace std;

enum class enChoice
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

enum class enTransactionChoice
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

enum class enUserChoice
{
    ShowUserList = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUserInfo = 4,
    FindUser = 5,
    MainMenu = 6,
};

enum class enStatus
{
    New = 1,
    Exist = 2,
};

enum class enPermissions
{
    showing = 1,
    adding = 2,
    deleting = 4,
    updating = 8,
    finding = 16,
    transactions = 32,
    managingUsers = 64,
};
