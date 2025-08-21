#pragma once

#include <iostream>
using namespace std;

class clsPerson
{
private:
    string _firstName, _lastName, _email, _phone;

public:

    clsPerson(string fName, string lName, string email, string phone)
    {
        _firstName = fName;
        _lastName = lName;
        _email = email;
        _phone = phone;
    }

    void setFirstName(string name)
    {
        _firstName = name;
    }
    void setLastName(string name)
    {
        _lastName = name;
    }
    void setEmail(string email)
    {
        _email = email;
    }
    void setPhone(string phone)
    {
        _phone = phone;
    }

    string getFirstName()
    {
        return _firstName;
    }
    string getLastName()
    {
        return _lastName;
    }

    string FullName()
    {
        return _firstName + " " + _lastName;
    }
    string getEmail()
    {
        return _email;
    }
    string getPhone()
    {
        return _phone;
    }
};
