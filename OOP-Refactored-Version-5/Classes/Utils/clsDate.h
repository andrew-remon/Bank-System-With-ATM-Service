#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
    int _day, _month, _year, _hour, _min, _sec;
    enum enDays {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
    enum enDateCompare {Before = -1, Equal = 0, After = 1};

public:
    struct stPeriodDates;

    clsDate()
    {
        time_t currentTime = time(0);
        tm * now = localtime(&currentTime);

        _day = now->tm_mday;
        _month = now->tm_mon + 1;
        _year = now->tm_year + 1900;
        _hour = now->tm_hour;
        _min = now->tm_min;
        _sec = now->tm_sec;
    }

    clsDate(string date)
    {
        vector <string> vWords;
        clsString::split(date, vWords, "/");

        _day = stoi(vWords[0]);
        _month = stoi(vWords[1]);
        _year = stoi(vWords[2]);
    }

    clsDate(int day, int month, int year)
    {
        _day = day;
        _month = month;
        _year = year;
    }

    clsDate(int totalDays, int year)
    {
        getDateFromYearStart(totalDays, year);
    }

    int getDay()
    {
        return _day;
    }

    int getMonth()
    {
        return _month;
    }

    int getYear()
    {
        return _year;
    }

    int getHour()
    {
        return _hour;
    }

    int getMin()
    {
        return _min;
    }

    int getSec()
    {
        return _sec;
    }

    void print()
    {
        cout << _day << "/" << _month << "/" << _year << endl;
    }

    static bool isLeapYear(int year)
    {
        return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
    }

    bool isLeapYear()
    {
        return isLeapYear(_year);
    }

    static int getMonthDays(int year, int month)
    {
        int arrMonthDays[] ={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int monthDays = 0;

        (isLeapYear(year) && month == 2) ? monthDays = 29: monthDays = arrMonthDays[month];

        return monthDays;
    }

    static int getMonthDays(clsDate date)
    {
        int arrMonthDays[] ={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int monthDays = 0;

        (isLeapYear(date._year) && date._month ==2) ? monthDays = 29: monthDays = arrMonthDays[date._month];

        return monthDays;
    }

    int getMonthDays()
    {
        return getMonthDays(*this);
    }

    void getDateFromYearStart(int totalDays, int year)
    {
        int monthCounter = 1;
        while (totalDays > 28)
        {
            totalDays -= getMonthDays(year, monthCounter);
            monthCounter++;
        }

        _day = totalDays;
        _month = monthCounter;
        _year = year;
    }

    static int calcDaysInYear(int year)
    {
        return (isLeapYear(year)) ? 366: 365;
    }

    int calcDaysInYear()
    {
        return calcDaysInYear(_year);
    }

    static int calcHoursInYear(int year)
    {
        return (calcDaysInYear(year)*24);
    }

    int calcHoursInYear()
    {
        return calcHoursInYear(_year);
    }

    static int calcMinutesInYear(int year)
    {
        return (calcHoursInYear(year)*60);

    }

    int calcMinutesInYear()
    {
        return calcMinutesInYear(_year);
    }

    static int calcSecondsInYear(int year)
    {
        return (calcMinutesInYear(year)*60);
    }

    int calcSecondsInYear()
    {
        return calcSecondsInYear(_year);
    }

    static int getDayOrderOfWeek(int year, int month, int day)
    {
        int a = (14-month)/12;

        int y = year - a;

        int m = month + 12*a - 2;

        int d = (day + y + (y/4) - (y/100) + (y/400) + (31*m /12)) % 7;

        return d;
    }

    static int getDayOrderOfWeek(clsDate date)
    {
        int a = (14-date._month)/12;

        int y = date._year - a;

        int m = date._month + 12*a - 2;

        int d = (date._day + y + (y/4) - (y/100) + (y/400) + (31*m /12)) % 7;

        return d;
    }

    int getDayOrderOfWeek()
    {
        return getDayOrderOfWeek(_year, _month, _day);
    }

    static string getMonthName(int month)
    {
        string dayName[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return dayName[month];
    }

    string getMonthName()
    {
        return getMonthName(_month);
    }

    static void printMonthCalendar(int year, int month)
    {
        string monthName = getMonthName(month);
        int current = getDayOrderOfWeek(year, month, 1);
        int monthDays = getMonthDays(year, month);

        cout << "\n  ------------- " << monthName << " ---------------\n";
        cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

        int i;
        for (i = 0; i < current; i++)
        {
            printf("     ");
        }

        for (int j = 1; j <= monthDays; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        cout << endl << "  ---------------------------------" << endl;
    }

    void printMonthCalendar()
    {
        printMonthCalendar(_year, _month);
    }

    static void printYearCalendar(int year)
    {
        cout << "\n  ---------------------------------\n";
        cout << "           Calendar - " << year << endl;
        cout << "  ---------------------------------\n";

        for (int i = 1; i <=12;i++)
        {
            printMonthCalendar(year, i);
            cout << endl;
        }
    }

    void printYearCalendar()
    {
        printYearCalendar(_year);
    }

    static int getDaysNumFromBeginOfYear(int year, int month, int day)
    {
        int totalDays = 0;

        for (int i = 1; i < month; i++)
        {
            int monthDays = getMonthDays(year, i);
            totalDays += monthDays;
        }

        totalDays += day;

        return totalDays;
    }

    int getDaysNumFromBeginOfYear()
    {
        return getDaysNumFromBeginOfYear(_year, _month, _day);
    }

    static void incrementMonth(int& year, int& month)
    {
        if (month == 12)
        {
            month = 1;
            ++year;
        }
        else ++month;
    }

    void incrementMonth()
    {
        incrementMonth(_year, _month);
    }

    static void printNewDateAfterAddingDays(int year, int month, int day, int addedDays)
    {
        // * 10/10/2022 ==> 2500 days ==> 14/8/2029
        cout << "Date After Adding [" << addedDays << "] Days is: ";

        int current = getMonthDays(year, month);
        int remaining = current - day;
        day += remaining;
        incrementMonth(year, month);
        addedDays -= remaining;

        while (addedDays > getMonthDays(year, month))
        {
            addedDays -= getMonthDays(year, month);
            incrementMonth(year, month);
        }

        day = addedDays;

        cout << day << "/" << month << "/" << year << endl;
    }

    void printNewDateAfterAddingDays(int addedDays)
    {
        printNewDateAfterAddingDays(_year, _month, _day, addedDays);
    }

    static bool isDate1LessThanDate2(clsDate firstDate, clsDate secondDate)
    {
        if (firstDate._year < secondDate._year) return true;
        else if (firstDate._year == secondDate._year)
        {
            if (firstDate._month < secondDate._month) return true;
            else if (firstDate._month == secondDate._month)
            {
                if (firstDate._day < secondDate._day) return true;
                else return false;
            }
        }
        return false;
    }

    bool isLessThanDate2(clsDate secondDate)
    {
        return isDate1LessThanDate2(*this, secondDate);
    }

    static bool isDate1EqualToDate2(clsDate firstDate, clsDate secondDate)
    {
        return (firstDate._day == secondDate._day && firstDate._month == secondDate._month && firstDate._year == secondDate._year) ? true : false;
    }

    bool isEqualToDate2(clsDate secondDate)
    {
        return isDate1EqualToDate2(*this ,secondDate);
    }

    static bool isLastDayInMonth(clsDate date)
    {
        return date._day == getMonthDays(date._year, date._month);
    }

    bool isLastDayInMonth()
    {
        return isLastDayInMonth(*this);
    }

    static bool isLastMonthInYear(int month)
    {
        return month == 12;
    }

    bool isLastMonthInYear()
    {
        return isLastMonthInYear(_month);
    }

    static void incrementDateByOneDay(clsDate & date)
    {
        if (isLastDayInMonth(date))
        {
            date._day = 1;
            if (isLastMonthInYear(date._month))
            {
                date._month = 1;
                date._year++;
            }
            else date._month++;
        }
        else date._day++;
    }

    void incrementDateByOneDay()
    {
        incrementDateByOneDay(*this);
    }

    static int getDiffBetweenTwoDates(clsDate date1, clsDate date2, bool includeLastDay = false)
    {
        int diffDays = 0, directionValue = 1;

        if (!isDate1LessThanDate2(date1, date2))
        {
            swapDates(date1, date2);
            directionValue = -1;
        }

        while (isDate1LessThanDate2(date1, date2))
        {
            ++diffDays;
            incrementDateByOneDay(date1);
        }

        return (includeLastDay) ? ++diffDays: diffDays;
    }

    int getDiffBetweenTwoDates(clsDate date2, bool includeLastDay = false)
    {
        return getDiffBetweenTwoDates(*this, date2, includeLastDay);
    }

    static void swapDates(clsDate & firstDate, clsDate & secondDate)
    {
        clsDate tempDate;

        tempDate._day = firstDate._day;
        tempDate._month = firstDate._month;
        tempDate._year = firstDate._year;

        firstDate._day = secondDate._day;
        firstDate._month = secondDate._month;
        firstDate._year = secondDate._year;

        secondDate._day = tempDate._day;
        secondDate._month = tempDate._month;
        secondDate._year = tempDate._year;
    }

    void swapDates(clsDate & secondDate)
    {
        swapDates(*this, secondDate);
    }

    static void incrementDateByXDays(clsDate & date, short X)
    {
        for (int i = 1; i <= X; i++) incrementDateByOneDay(date);
    }

    void incrementDateByXDays(short X)
    {
        incrementDateByXDays(*this, X);
    }

    static void incrementDateByOneWeek(clsDate & date)
    {
        for (int i = 1; i <= 7; i++) incrementDateByOneDay(date);
    }

    void incrementDateByOneWeek()
    {
        incrementDateByOneWeek(*this);
    }

    static void incrementDateByXWeeks(clsDate & date, int X)
    {
        for (int i = 1; i <= X; i++) incrementDateByOneWeek(date);
    }

    void incrementDateByXWeeks(short X)
    {
        incrementDateByXWeeks(*this, X);
    }

    static void incrementDateByOneMonth(clsDate & date)
    {
        if (date._month == 12)
        {
            date._month = 1;
            date._year++;
        }
        else date._month++;

        int numOfDays = getMonthDays(date._year, date._month);

        if (date._day > numOfDays) date._day = numOfDays;
    }

    void incrementDateByOneMonth()
    {
        incrementDateByOneMonth(*this);
    }

    static void incrementDateByXMonths(clsDate & date, int X)
    {
        for (int i = 1; i <= X; i++) incrementDateByOneMonth(date);
    }

    void incrementDateByXMonths(short X)
    {
        incrementDateByXMonths(*this, X);
    }

    static void incrementDateByOneYear(clsDate & date)
    {
        date._year++;
    }

    void incrementDateByOneYear()
    {
        incrementDateByOneYear(*this);
    }

    static void incrementDateByXYear(clsDate & date, int X)
    {
        date._year += X;
    }

    void incrementDateByXYear(short X)
    {
        incrementDateByXYear(*this, X);
    }

    static void incrementDateByOneDecade(clsDate & date)
    {
        for (int i = 1; i <= 10; i++) incrementDateByOneYear(date);
        // OR
        // date.Year += 10;
    }

    void incrementDateByOneDecade()
    {
        incrementDateByOneDecade(*this);
    }

    static void incrementDateByXDecade(clsDate & date, int X)
    {
        date._year += X * 10;
    }

    void incrementDateByXDecade(int X)
    {
        incrementDateByXDecade(*this, X);
    }

    static void incrementDateByOneCentury(clsDate & date)
    {
        incrementDateByXDecade(date, 10);
        // Or
        // date.year += 100;
    }

    void incrementDateByOneCentury()
    {
        incrementDateByOneCentury(*this);
    }

    static void incrementDateByOneMillennium(clsDate & date)
    {
        for (int i = 1; i <= 10; i++) incrementDateByOneCentury(date);
        // Or
        // date.Year += 1000;
    }

    void incrementDateByOneMillennium()
    {
        incrementDateByOneMillennium(*this);
    }

    static bool isWeekEnd(int year,int month, int day)
    {
        enDays dayIndex = (enDays) getDayOrderOfWeek(year, month, day);

        return (dayIndex == enDays::Saturday || dayIndex == enDays::Friday) ? true : false;
    }

    static bool isWeekEnd(clsDate date)
    {
        enDays dayIndex = (enDays) getDayOrderOfWeek(date);

        return (dayIndex == enDays::Saturday || dayIndex == enDays::Friday) ? true : false;
    }

    bool isWeekEnd()
    {
        return isWeekEnd(*this);
    }

    static bool isBusinessDay(int year,int month, int day)
    {
        return (isWeekEnd(year, month, day)) ? false : true;
    }

    static bool isBusinessDay(clsDate date)
    {
        return (isWeekEnd(date)) ? false : true;
    }

    bool isBusinessDay()
    {
        return isBusinessDay(*this);
    }

    static int getDaysTillEndOfWeek(int year,int month, int day)
    {
        return int(enDays::Saturday) - getDayOrderOfWeek(year, month, day);
    }

    int getDaysTillEndOfWeek()
    {
        return getDaysTillEndOfWeek(_year, _month, _day);
    }

    static int getDaysTillEndOfMonth(int year,int month, int day)
    {
        return getMonthDays(year, month) - day;
    }

    int getDaysTillEndOfMonth()
    {
        return getDaysTillEndOfMonth(_year, _month, _day);
    }

    static int getDaysTillEndOfYear(int year, int month, int day)
    {
        int daysLeft = getDaysTillEndOfMonth(year, month, day);

        for (int i = month+1; i <= 12; i++)
        {
            daysLeft += getMonthDays(year, i);
        }

        return daysLeft;
    }

    int getDaysTillEndOfYear()
    {
        return getDaysTillEndOfYear(_year, _month, _day);
    }

    static int getVacationDays(clsDate dateFrom, clsDate dateTo)
    {
        int vacationDays = 0;
        while (isDate1LessThanDate2(dateFrom, dateTo))
        {
            if (!isWeekEnd(dateFrom)) vacationDays++;
            incrementDateByOneDay(dateFrom);
        }
        return vacationDays;
    }

    int getVacationDays(clsDate dateTo)
    {
        return getVacationDays(*this, dateTo);
    }

    static clsDate getReturnDateAfterVacation(clsDate dateFrom, int vacationDays)
    {
        clsDate returnDate;
        while(true)
        {
            if (isBusinessDay(dateFrom)) vacationDays--;
            incrementDateByOneDay(dateFrom);

            if (vacationDays == 0)
            {
                returnDate = dateFrom;
                return returnDate;
            }
        }
        return {};
    }

    static enDateCompare compareDate(clsDate firstDate, clsDate secondDate)
    {
        if (isDate1LessThanDate2(firstDate, secondDate)) return enDateCompare::Before;
        else if (isDate1EqualToDate2(firstDate, secondDate)) return enDateCompare::Equal;
        else return enDateCompare::After;
    }

    enDateCompare compareDate(clsDate secondDate)
    {
        return compareDate(*this, secondDate);
    }


    // static bool isOverlapPeriods(clsDate fDatePeriod1, clsDate sDatePeriod1, clsDate fDatePeriod2, clsDate sDatePeriod2)
    // {
    //     if (compareDate(sDatePeriod1, fDatePeriod2) == enDateCompare::Before
    //         || compareDate(fDatePeriod1, sDatePeriod2) == enDateCompare::After) return false;
    //     else return true;
    // }


    static bool isDateValidated(clsDate date)
    {
        int monthDays = getMonthDays(date);

        if (date._day > monthDays) return false;

        if (date._month > 12) return false;

        return true;
    }

    bool isDateValidated()
    {
        return isDateValidated(*this);
    }

    static string DateToString(clsDate date)
	{
		return  to_string(date.getDay()) + "/" + to_string(date.getMonth()) + "/" + to_string(date.getYear());
	}
    static string HourToString(clsDate date)
	{
		return  to_string(date.getHour()) + ":" + to_string(date.getMin()) + ":" + to_string(date.getSec());
	}

    static string TimeToString(clsDate date)
    {
        return DateToString(date) + " - " + HourToString(date);
    }

    static bool isOverlapPeriods(stPeriodDates period1, stPeriodDates period2);

    static int getPeriodDaysLength(stPeriodDates period, bool includeLastDay = false);

    static bool isDateWithinPeriod(clsDate date, stPeriodDates period);

    int countOverlappedDays(stPeriodDates period1, stPeriodDates period2);
};


// ! Period Struct related functions
struct clsDate::stPeriodDates
{
    clsDate startDate;
    clsDate endDate;
};

inline bool clsDate::isOverlapPeriods(stPeriodDates period1, stPeriodDates period2)
{
    if (compareDate(period1.endDate, period2.startDate) == enDateCompare::Before
        || compareDate(period1.startDate, period2.endDate) == enDateCompare::After) return false;
    else return true;
}

// note: in function declaration, we assign the default parameter, but in its declaration, there's no need, we just write the parameter with no default value.
inline int clsDate::getPeriodDaysLength(stPeriodDates period, bool includeLastDay)
{
    return getDiffBetweenTwoDates(period.startDate, period.endDate, includeLastDay);
}

inline bool clsDate::isDateWithinPeriod(clsDate date, stPeriodDates period)
{
    return !(compareDate(date, period.startDate) == enDateCompare::Before
            || compareDate(date, period.endDate) == enDateCompare::After);
}

inline int clsDate::countOverlappedDays(stPeriodDates period1, stPeriodDates period2)
{
    int period1Length = getPeriodDaysLength(period1, true);
    int period2Length = getPeriodDaysLength(period2, true);

    int overlappedDays = 0;

    if (!isOverlapPeriods(period1, period2)) return 0;

    if (period1Length < period2Length)
    {
        while (isDate1LessThanDate2(period1.startDate, period1.endDate))
        {
            if (isDateWithinPeriod(period1.startDate, period2)) overlappedDays++;
            incrementDateByOneDay(period1.startDate);
        }
    }

    else
    {
        while (isDate1LessThanDate2(period2.startDate, period2.endDate))
        {
            if (isDateWithinPeriod(period2.startDate, period1)) overlappedDays++;
            incrementDateByOneDay(period2.startDate);
        }
    }

    return overlappedDays;
}
