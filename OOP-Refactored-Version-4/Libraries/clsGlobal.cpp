#include <iostream>
#include "clsGlobal.h"
#include "clsBankUser.h"
using namespace std;

// ! need to define here the global variables to allocate memory
const std::string ClientsDataFile = "Clients.txt";
const std::string UsersDataFile = "Users.txt";
clsBankUser currentUser = clsBankUser::findUserByUserNameAndPassword("", "");
