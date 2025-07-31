#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsBankUser.h"
#include "clsGlobal.h"
using namespace std;

class clsScreen
{
protected :
    static void _drawScreenHeader(string title, string subTitle = "")
    {
        cout << "\n\n\t\t\t\t\t____________________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;
        if (subTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\t\t\t\t\t____________________________________________\n\n";
        cout << "\n\t\t\t\t\t\t     User: " << currentUser.FullName() << "\n";
        cout << "\n\t\t\t\t\t\t     Date: " << clsDate::DateToString(clsDate()) << "\n\n";
        // currentDate.print();
        // cout << "\n\n";
    }

};
