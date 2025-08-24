#include <iostream>
#include <fstream>
#include "clsBankUser.h"
#include "clsGlobal.h"
#include "../Utils/clsString.h"
#include "../Utils/clsUtil.h"
#include "../Utils/clsInputValidation.h"

using namespace std;

// ----- Private Methods -----
clsBankUser clsBankUser::_convertLineIntoUserObject(const string& userRecord, const string& sep)
{
    vector <string> vUserData;

    clsString::split(userRecord, vUserData, sep);
    return clsBankUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], vUserData[5], stod(vUserData[6]));
}

clsBankUser clsBankUser::_getEmptyUserObject()
{
    return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
}

clsBankUser clsBankUser::_getAddUserObject(const string& userName)
{
    return clsBankUser(enMode::AddMode, "", "", "", "", userName, "", 0);
}

void clsBankUser::_rebuildPermissionsFromAccessValue(clsBankUser & user)
{
    user._permissions.showing        = user._accessValue & 1;
    user._permissions.adding         = user._accessValue & 2;
    user._permissions.deleting       = user._accessValue & 4;
    user._permissions.updating       = user._accessValue & 8;
    user._permissions.finding        = user._accessValue & 16;
    user._permissions.transactions   = user._accessValue & 32;
    user._permissions.managingUsers  = user._accessValue & 64;
    user._permissions.loginRecords   = user._accessValue & 128;
}

vector <clsBankUser> clsBankUser::_loadUserDataFileIntoVector(const string& fileName)
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

int clsBankUser::_manageUserAccess(clsBankUser & user)
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

    answer = clsUtil::confirm("Show LoggedIn Users List? (y/n) ");
    if (tolower(answer) == 'y')
    {
        totalAccess |= 128;
        user._permissions.loginRecords = true;
    }

    return totalAccess;
}

string clsBankUser::_returnUserData(const clsBankUser& userData, string sep)
{
    string userRecord = "";

    userRecord += userData.getFirstName()  + sep;
    userRecord += userData.getLastName() + sep;
    userRecord += userData.getEmail()   + sep;
    userRecord += userData.getPhone()   + sep;
    userRecord += userData.getUserName()   + sep;
    userRecord += userData.getPassword() + sep;
    userRecord += to_string(userData.getAccessValue());

    return userRecord;
}

void clsBankUser::_saveUserDataIntoFile(const string& fileName, const vector <clsBankUser>& vUsers)
{
    fstream myFile;

    myFile.open(fileName, ios::out);

    if (myFile.is_open())
    {
        for (const clsBankUser & C : vUsers)
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

void clsBankUser::_markUserDeleteSign(clsBankUser & user)
{
    user.setDeleteSign(true);
}

void clsBankUser::_changeUserRecord(clsBankUser & user)
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


// ----- Public Methods -----
clsBankUser::clsBankUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, short accessValue) : clsPerson(firstName, lastName, email, phone)
{
    _mode = mode;
    _userName = userName;
    _password = password;
    _accessValue = accessValue;
}

bool clsBankUser::isModeUpdated() const
{
    return (_mode == enMode::UpdateMode);
}

void clsBankUser::setToUpdateMode()
{
    _mode = enMode::UpdateMode;
}

void clsBankUser::print()
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

bool clsBankUser::isEmpty() const
{
    return (_mode == enMode::EmptyMode);
}

vector <clsBankUser> clsBankUser::getListVectorFromFile(const string& fileName)
{
    return _loadUserDataFileIntoVector(fileName);
}

clsBankUser clsBankUser::findUser(const string& userName)
{
    vector <clsBankUser> vUsers = _loadUserDataFileIntoVector(UsersDataFile);

    for (const clsBankUser & user: vUsers)
    {
        if (user.getUserName() == userName)
        {
            return user;
        }
    }

    return _getEmptyUserObject();
}

clsBankUser clsBankUser::findUserByUserNameAndPassword(const string& userName, const string& password)
{
    vector <clsBankUser> vUsers = _loadUserDataFileIntoVector(UsersDataFile);

    for (const clsBankUser & user: vUsers)
    {
        if (user.getUserName() == userName && user.getPassword() == password)
        {
            return user;
        }
    }

    return _getEmptyUserObject();
}

clsBankUser & clsBankUser::findUserRef(const string& userName, vector <clsBankUser> & vUsers)
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

bool clsBankUser::isUserExist(string userName)
{
    clsBankUser user = findUser(userName);
    return (!user.isEmpty());
}

bool clsBankUser::isUserExist(string userName, string password)
{
    clsBankUser user = findUserByUserNameAndPassword(userName, password);
    return (!user.isEmpty());
}

void clsBankUser::updateInfo()
{
    vector <clsBankUser> vUsers = _loadUserDataFileIntoVector(UsersDataFile);

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

void clsBankUser::deleteInfo()
{
    vector <clsBankUser> vUsers = _loadUserDataFileIntoVector(UsersDataFile);

    if (!this->isEmpty())
    {
        this->print();

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            _markUserDeleteSign(*this);

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

void clsBankUser::printAccessDeniedMessage()
{
    cout << "\n\n\t\t\t\t------------------------------------------------------------------\n";
    cout << "\t\t\t\tThis User Doesn't have the permission, Please Contact the Admin.\n";
    cout << "\t\t\t\t------------------------------------------------------------------\n\n";
}

string clsBankUser::readUserName(enStatus status)
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

bool clsBankUser::isUserHasPermission(enPermissions permission)
{
    if (this->getAccessValue() == -1 || (static_cast<short>(permission) & this->getAccessValue()) == static_cast<short>(permission))
        return true;

    return false;
}
