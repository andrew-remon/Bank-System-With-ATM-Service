#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidation.h"
#include "clsUtil.h"
#include "clsGlobal.h"
#include "clsEnums.h"
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class clsBankUser : public clsPerson
{
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddMode = 2};
    struct stPermissions
    {
        bool showing = false, adding = false, deleting = false, updating = false, finding = false,
            transactions = false, managingUsers = false;
    };

    string _userName, _password;
    enMode _mode;
    stPermissions _permissions;
    short _accessValue;
    bool _deleteSign = false;

    static clsBankUser _convertLineIntoUserObject(string statement, string sep)
    {
        vector <string> vUserDate;

        clsString::split(statement, vUserDate, sep);
        return clsBankUser(enMode::UpdateMode, vUserDate[0], vUserDate[1], vUserDate[2], vUserDate[3], vUserDate[4], vUserDate[5], stod(vUserDate[6]));
    }

    static clsBankUser _getEmptyUserObject()
    {
        return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static clsBankUser _getAddUserObject(string userName)
    {
        return clsBankUser(enMode::AddMode, "", "", "", "", userName, "", 0);
    }

    static void _rebuildPermissionsFromAccessValue(clsBankUser & user)
    {
        user._permissions.showing        = user._accessValue & 1;
        user._permissions.adding         = user._accessValue & 2;
        user._permissions.deleting       = user._accessValue & 4;
        user._permissions.updating       = user._accessValue & 8;
        user._permissions.finding        = user._accessValue & 16;
        user._permissions.transactions   = user._accessValue & 32;
        user._permissions.managingUsers  = user._accessValue & 64;
    }

    static vector <clsBankUser> _loadUserDataFileIntoVector(string fileName)
    {
        vector <clsBankUser> vUsers;

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line;

            while(getline(myFile, line))
            {
                clsBankUser user = _convertLineIntoUserObject(line, "#//#");

                // add the permissions flags after extracting the data from the file.
                _rebuildPermissionsFromAccessValue(user);

                vUsers.push_back(user);
            }
            myFile.close();
        }

        return vUsers;
    }

    static int _manageUserAccess(clsBankUser & user)
    {
        int totalAccess = 0;
        char answer;

        answer = clsUtil::confirm("Do You want to Full Access? (y/n) ");

        if (tolower(answer) == 'y') return -1;

        cout << "\nDo you want to give Access to: \n";

        answer = clsUtil::confirm("Show User List? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 1;
            user._permissions.showing = true;
        }

        answer = clsUtil::confirm("Add New User? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 2;
            user._permissions.adding = true;
        }

        answer = clsUtil::confirm("Delete User? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 4;
            user._permissions.deleting = true;
        }

        answer = clsUtil::confirm("Update User? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 8;
            user._permissions.updating = true;
        }

        answer = clsUtil::confirm("Find User? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 16;
            user._permissions.finding = true;
        }

        answer = clsUtil::confirm("Transactions? (y/n)");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 32;
            user._permissions.transactions = true;
        }

        answer = clsUtil::confirm("Manage Users? (y/n) ");
        if (tolower(answer) == 'y')
        {
            totalAccess |= 64;
            user._permissions.managingUsers = true;
        }

        return totalAccess;
    }

    static string _returnUserData(clsBankUser userData, string sep = "#//#")
    {
        string userRecord = "";

        userRecord += userData.getFirstName()  + sep;
        userRecord += userData.getLastName() + sep;
        userRecord += userData.getEmail()   + sep;
        userRecord += userData.getPhone()   + sep;
        userRecord += userData.getUserName()   + sep;
        userRecord += userData.getPassword()   + sep;
        userRecord += to_string(userData.getAccessValue());

        return userRecord;
    }

    static void _saveUserDataIntoFile(string fileName, vector <clsBankUser> vUsers)
    {
        fstream myFile;

        myFile.open(fileName, ios::out);

        if (myFile.is_open())
        {
            for (clsBankUser & C : vUsers)
            {
                if (C.getDeleteSign() == false)
                {
                    string dataLine = _returnUserData(C);
                    myFile << dataLine << endl;
                }
            }
            myFile.close();
        }
    }

    static void _markUserDeleteSign(clsBankUser & user, vector <clsBankUser> & vUsers)
    {
        user.setDeleteSign(true);
    }

    static void _changeUserRecord(clsBankUser & user)
    {
        cout << "Enter First Name? ";
        user.setFirstName(clsInputValidation::readString());

        cout << "Enter Last Name? ";
        user.setLastName(clsInputValidation::readString());

        cout << "Enter Email? ";
        user.setEmail(clsInputValidation::readString());

        cout << "Enter Phone? ";
        user.setPhone(clsInputValidation::readString());

        cout << "Enter Password? ";
        user.setPassword(clsInputValidation::readString());

        user.setAccessValue(_manageUserAccess(user));
    }

public:

    clsBankUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, short accessValue) : clsPerson(firstName, lastName, email, phone)
    {
        _mode = mode;
        _userName = userName;
        _password = password;
        _accessValue = accessValue;
    }

    string getUserName()
    {
        return _userName;
    }

    void setUserName(string UserName)
    {
        _userName = UserName;
    }

    void setPassword(string Password)
    {
        _password = Password;
    }

    string getPassword()
    {
        return _password;
    }

    void setAccessValue(int value)
    {
        _accessValue = value;
    }

    short getAccessValue()
    {
        return _accessValue;
    }

    bool getDeleteSign()
    {
        return _deleteSign;
    }

    void setDeleteSign(bool value)
    {
        _deleteSign = value;
    }

    void print()
    {
        cout << "\nUser Card:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << "First Name: " << getFirstName() << endl;
        cout << "Last Name: " << getLastName() << endl;
        cout << "Full Name: " << FullName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Phone: " << getPhone() << endl;
        cout << "UserName: " << getUserName() << endl;
        cout << "Password: " << getPassword() << endl;
        cout << "Access Value: " << getAccessValue() << endl;
        cout << "- - - - - - - - - - - - - - - - - - -\n\n";
    }

    bool isEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }

    static vector <clsBankUser> getUserListVector(string fileName)
    {
        return _loadUserDataFileIntoVector(fileName);
    }

    static clsBankUser findUser(string userName)
    {
        vector <clsBankUser> vUsers = getUserListVector(UsersDataFile);

        for (clsBankUser & user: vUsers)
        {
            if (user.getUserName() == userName)
            {
                return user;
            }
        }

        return _getEmptyUserObject();
    }

    static clsBankUser findUserByUserNameAndPassword(string userName, string password)
    {
        vector <clsBankUser> vUsers = getUserListVector(UsersDataFile);

        for (clsBankUser & user: vUsers)
        {
            if (user.getUserName() == userName && user.getPassword() == password)
            {
                return user;
            }
        }

        return _getEmptyUserObject();
    }

    static clsBankUser & findUserRef(string userName, vector <clsBankUser> & vUsers)
    {
        for (clsBankUser & user: vUsers)
        {
            if (user.getUserName() == userName)
            {
                return user;
            }
        }
        throw runtime_error("User Not Found");
    }

    static bool isUserExist(string userName)
    {
        clsBankUser user = findUser(userName);
        return (!user.isEmpty());
    }

    static bool isUserExist(string userName, string password)
    {
        clsBankUser user = findUserByUserNameAndPassword(userName, password);
        return (!user.isEmpty());
    }

    void updateInfo()
    {
        vector <clsBankUser> vUsers = getUserListVector(UsersDataFile);

        this->print();

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            if (this->_mode == enMode::UpdateMode)
            {
                cout << "\n--------------------\n";
                cout << "Update User Info.\n";
                cout << "--------------------\n" << endl;

                _changeUserRecord(*this);

                // * to update the vector and the file with the new user record
                for (clsBankUser &user: vUsers)
                {
                    if (user.getUserName() == this->getUserName())
                    {
                        user = *this;
                        break;
                    }
                }

                _saveUserDataIntoFile(UsersDataFile, vUsers);

                cout << "\nUser Updated Successfully." << endl;
            }
            else cout << "\nUpdate Failed, It's an empty object.";
        }
    }

    void deleteInfo()
    {
        vector <clsBankUser> vUsers = getUserListVector(UsersDataFile);

        if (!this->isEmpty())
        {
            this->print();

            char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

            if (tolower(ans) == 'y')
            {
                _markUserDeleteSign(*this, vUsers);

                //* to delete the user from the vector and the file.
                for (clsBankUser &user: vUsers)
                {
                    if (user.getUserName() == this->getUserName())
                    {
                        user = *this;
                        break;
                    }
                }

                _saveUserDataIntoFile(UsersDataFile, vUsers);
                *this = _getEmptyUserObject();
                cout << "\nUser Deleted Successfully." << endl;
            }
        }
        else cout << "\nAccount Not found, Please Try Again." << endl;
    }

    static void printAccessDeniedMessage()
    {
        cout << "\n\n\t\t\t\t------------------------------------------------------------------\n";
        cout << "\t\t\t\tThis User Doesn't have the permission, Please Contact the Admin.\n";
        cout << "\t\t\t\t------------------------------------------------------------------\n\n";
    }

    static string readUserName(enStatus status)
    {
        cout << "Please Enter a User Name: ";
        string userName = clsInputValidation::readString();

        switch(status)
        {
            case enStatus::Exist:
            {
                while(!clsBankUser::isUserExist(userName))
                {
                    cout << "User with [" << userName << "] do not exist, enter an existed one: ";
                    userName = clsInputValidation::readString();
                }
                break;
            }
            case enStatus::New:
            {
                while(clsBankUser::isUserExist(userName))
                {
                    cout << "User with [" << userName << "] exists, enter New UserName: ";
                    userName = clsInputValidation::readString();
                }
            }
        }
        return userName;
    }

    // note: a way to use struct with enums to manage permissions.
    // static bool isUserHasPermission(enChoice permission)
    // {
    //     if (currentUser.getAccessValue() == -1) return true;

    //     else
    //     {
    //         switch (permission)
    //         {
    //         case enChoice::AddNewClient :
    //         {
    //             if (currentUser._permissions.adding == true) return true;
    //             break;
    //         }
    //         case enChoice::ShowClientList :
    //         {
    //             if (currentUser._permissions.showing == true) return true;
    //             break;
    //         }
    //         case enChoice::DeleteClient :
    //         {
    //             if (currentUser._permissions.deleting == true) return true;
    //             break;
    //         }
    //         case enChoice::UpdateClientInfo :
    //         {
    //             if (currentUser._permissions.updating == true) return true;
    //             break;
    //         }
    //         case enChoice::FindClient :
    //         {
    //             if (currentUser._permissions.finding == true) return true;
    //             break;
    //         }
    //         case enChoice::Transactions :
    //         {
    //             if (currentUser._permissions.transactions == true) return true;
    //             break;
    //         }
    //         case enChoice::ManageUsers :
    //         {
    //             if (currentUser._permissions.managingUsers == true) return true;
    //             break;
    //         }
    //         default:
    //             return false;
    //         }
    //     }
    //     return false;
    // }

    // note: only with enums to manage permissions.
    bool isUserHasPermission(enPermissions permission)
    {
        if (this->getAccessValue() == -1 || (static_cast<short>(permission) & this->getAccessValue()) == static_cast<short>(permission))
            return true;

        return false;
    }


    friend class clsAddNewUserScreen;
    friend class clsDeleteUserScreen;
    friend class clsUpdateUserScreen;
};
