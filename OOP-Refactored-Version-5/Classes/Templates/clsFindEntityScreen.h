#pragma once
#include <iostream>
#include <vector>
#include <type_traits> // for std::is_same
#include "../Screens/Misc/clsScreen.h"
using namespace std;

template <typename EntityType>
class clsFindEntityScreen : protected clsScreen
{
public:

    static void findEntityScreen
    (
        const string& fileName,
        const string& headerTitle,
        string (*readUniqueKey)(enStatus),
        EntityType (*findEntity)(const string&),
        void (*printInfo)(EntityType)
    )
    {
        vector <EntityType> vEntities = EntityType::getListVectorFromFile(fileName);

        _drawScreenHeader(headerTitle);

        string uniqueKey = readUniqueKey(enStatus::Exist);

        EntityType entityFound = findEntity(uniqueKey);

        if (!entityFound.isEmpty())
        {
            if constexpr (is_same<EntityType, clsBankClient>::value)
            cout << "\nClient is Found :)\n";
            else if constexpr(is_same<EntityType, clsBankUser>::value)
            cout << "\nUser is Found :)\n";

            printInfo(entityFound);
        }
    }
};
