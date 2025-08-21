// note: we implement this library to separate the logic code from the UI.

#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidation.h"
#include "clsScreen.h"
#include "clsEnums.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    static short _readMainMenuChoice()
    {
        cout << setw(31) << left << " " << "Choose What Do You Want to do? [1 to 8]? " ;
        short choice = clsInputValidation::readShortNumberBetween(1, 8, "Enter a Number from 1 to 8");
        return choice;
    }

    static void _performMainMenuChoice(enChoice choice);

public:
    static void showMainMenu();
};
