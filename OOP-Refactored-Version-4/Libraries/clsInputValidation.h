#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;

class clsInputValidation
{

public:
    static bool isNumberBetween(int number, int from, int to)
    {
        return (number >= from && number <= to);
    }

    static bool isNumberBetween(double number, double from, double to)
    {
        return (number >= from && number <= to);
    }

    static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo)
    {
        if ((!dateFrom.isLessThanDate2(dateTo))) clsDate::swapDates(dateFrom, dateTo);

        clsDate::stPeriodDates period {dateFrom, dateTo};

        return (date.isDateWithinPeriod(date, period));
    }

    // static int readIntNumber(string errorMessage)
    // {
    //     int number;
    //     bool notValid;
    //     cout << "Please enter a Number: ";
    //     do
    //     {
    //         cin >> number;
    //         notValid = cin.fail();

    //         if (notValid)
    //         {
    //             cin.clear();
    //             cin.ignore(1000, '\n');
    //             cout << errorMessage << endl;
    //         }
    //     } while (notValid);

    //     return number;
    // }

    static int readIntNumber(string errorMessage = "Invalid Input, Please enter a Number")
    {
        string input;
        int number;
        bool notValid;
        cout << "Please enter a Number: ";
        do
        {
            getline(cin, input);
            notValid = false;

            try
            {
                size_t pos;
                number = stoi(input, &pos);

                if (pos != input.length())
                {
                    throw invalid_argument("Trailing characters");
                }
            }

            catch(...)
            {
                cout << errorMessage << endl;
                notValid = true;
            }

        } while (notValid);

        return number;
    }
    static int readShortNumber(string errorMessage = "Invalid Input, Please enter a Number")
    {
        string input;
        short number;
        bool notValid;
        cout << "Please enter a Number: ";
        do
        {
            getline(cin, input);
            notValid = false;

            try
            {
                size_t pos;
                number = stoi(input, &pos);

                if (pos != input.length())
                {
                    throw invalid_argument("Trailing characters");
                }
            }

            catch(...)
            {
                cout << errorMessage << endl;
                notValid = true;
            }

        } while (notValid);

        return number;
    }

    static int readDblNumber(string errorMessage)
    {
        double number;
        bool notValid;
        do
        {
            cin >> number;
            notValid = cin.fail();
            if (notValid)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << errorMessage << endl;
            }
        } while (notValid);

        return number;
    }

    static int readIntNumberBetween(int from, int to, string errorMessage)
    {
        while (true)
        {
            int number = readIntNumber();
            if (isNumberBetween(number, from, to)) return number;
            else cout << errorMessage << endl;
        }
    }

    static short readShortNumberBetween(short from, short to, string errorMessage)
    {
        return readIntNumberBetween(from, to, errorMessage);
    }

    static string readString()
    {
        string statement;
        getline(cin >> ws, statement);
        return statement;
    }

    static bool isValidDate(clsDate date)
    {
        return date.isDateValidated();
    }

};
