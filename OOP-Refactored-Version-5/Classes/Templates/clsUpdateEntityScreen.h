#pragma once
#include <iostream>
#include <vector>
#include <type_traits> // for std::is_same
#include "../Screens/Misc/clsScreen.h"
#include "../utils/clsUtil.h"
using namespace std;

template <typename EntityType>
class clsUpdateEntityScreen : protected clsScreen
{
public:
    static void updateEntityScreen
    (
        const string& fileName,
        const string& headerTitle,
        const string& successMessage,
        string (*readUniqueKey)(enStatus),
        EntityType & findEntityRef(const string&, vector <EntityType>&),
        void (*printInfo)(EntityType),
        void (*changeRecord)(EntityType &),
        void (*saveData)(const string &, const vector <EntityType> &)
    )
    {
        vector <EntityType> vEntities = EntityType::getListVectorFromFile(fileName);

        _drawScreenHeader(headerTitle);

        string uniqueKey = readUniqueKey(enStatus::Exist);

        if constexpr (is_same<EntityType, clsBankUser>::value)
        {
            if (uniqueKey == "admin")
            {
                cout << "\nThis User Can't Be Updated, Please Contact The Admin For More Information.\n";
                return;
            }
        }

        EntityType &entityToBeUpdated = findEntityRef(uniqueKey, vEntities);

        printInfo(entityToBeUpdated);

        char ans = clsUtil::confirm("Are You sure You want to update this account data (Y/N)? ");

        if (tolower(ans) == 'y')
        {
            if (entityToBeUpdated.isModeUpdated())
            {
                changeRecord(entityToBeUpdated);
                saveData(fileName, vEntities);
                cout << successMessage;
                printInfo(entityToBeUpdated);
            }
            else
                cout << "\nUpdate Failed, It's an empty object.";
        }
    }
};
