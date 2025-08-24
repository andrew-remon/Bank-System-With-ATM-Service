#include <iostream>
#include "clsGlobal.h"
#include "clsBankUser.h"
using namespace std;

const std::string ClientsDataFile = "Database Text Files/Clients.txt";
const std::string UsersDataFile = "Database Text Files/Users.txt";
const std::string LoginRegisterFile = "Database Text Files/LoginRegister.txt";
const std::string TransferLogsFile = "Database Text Files/Transfer.txt";
clsBankUser currentUser = clsBankUser::findUserByUserNameAndPassword("", "");

