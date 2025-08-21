#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsGlobal.h"
#include "clsInputValidation.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
    static void _login();

public:
    static void showLogInScreen();
};


