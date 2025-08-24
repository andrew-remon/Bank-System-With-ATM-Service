/**
 * @file clsAddNewEntityScreen.h
 * @brief Template class for adding new entities (e.g., users, clients) while following the DRY principle.
 *
 * ## Overview
 * The `clsAddNewEntityScreen` class provides a reusable screen for adding new entities
 * (such as users or clients) by using function pointers and template specialization.
 * It removes redundancy between `clsAddNewUserScreen` and `clsAddNewClientScreen`.
 *
 * ### Key Features:
 * - Template-based design for flexibility (`EntityType` can be any class that supports the required methods).
 * - Reads a unique key for the new entity.
 * - Creates, modifies, and saves the entity.
 * - Automatically persists the updated entity list to a file.
 * - Prints confirmation and entity details after saving.
 *
 * ### Relationships:
 * - **Inherits from:** `clsScreen` — for drawing screen headers and providing
 *   shared screen utilities.
 */

#pragma once
#include <iostream>
#include <vector>
#include <type_traits> // for std::is_same
#include "../Screens/Misc/clsScreen.h"
using namespace std;

/**
 * @class clsAddNewEntityScreen
 * @brief A template screen for adding new entities (clients, users, etc.).
 *
 * @tparam EntityType The type of the entity to be added (e.g., `clsBankClient`, `clsUser`).
 *
 * This class inherits from `clsScreen` to reuse the standard screen header.
 * It expects the entity type to implement certain functions such as `getListVectorFromFile()`
 * and `setToUpdateMode()`.
 */
template <typename EntityType>
class clsAddNewEntityScreen : protected clsScreen
{
public:
    /**
     * @brief Displays the screen for adding a new entity and handles the full process.
     *
     * @param fileName The path to the file where entities are stored.
     * @param headerTitle The title displayed in the screen header.
     * @param readUniqueKey Function pointer to read a unique key for the entity (takes `enStatus`).
     * @param getAddObject Function pointer that creates and returns a new entity object given a unique key.
     * @param changeRecord Function pointer to modify the newly created entity (e.g., fill in details).
     * @param saveData Function pointer to save the updated list of entities to the file.
     * @param printInfo Function pointer to print the entity’s details after adding.
     *
     * ### Workflow:
     * 1. Loads the current list of entities from the file.
     * 2. Displays the screen header.
     * 3. Reads the unique key for the new entity.
     * 4. Creates a new entity object with the key.
     * 5. Updates entity data through `changeRecord`.
     * 6. Sets entity mode to update before saving.
     * 7. Appends the new entity to the list.
     * 8. Saves the updated list back to the file.
     * 9. Prints a success message and entity details.
     */
    static void addNewEntityScreen(
        const string& fileName,                                       // path to entity file
        const string& headerTitle,                                    // Header to display
        const string& successMessage,                                 // Header to display
        string (*readUniqueKey)(enStatus),                            // Function to read key
        EntityType (*getAddObject)(const string &),                   // Function to create new object
        void (*changeRecord)(EntityType &),                           // Function to modify data
        void (*saveData)(const string &, const vector<EntityType> &), // Save function
        void (*printInfo)(EntityType)                                 // Print function
    )
    {
        // Load existing entities
        vector<EntityType> entities = EntityType::getListVectorFromFile(fileName);

        // Draw header
        _drawScreenHeader(headerTitle);

        // Read unique key for the new entity
        string uniqueKey = readUniqueKey(enStatus::New);

        // Create a new entity object
        EntityType newEntity = getAddObject(uniqueKey);

        // Modify entity data
        changeRecord(newEntity);

        // Set mode to update before saving
        newEntity.setToUpdateMode();

        // Add to the list
        entities.push_back(newEntity);

        // Save updated list
        saveData(fileName, entities);

        // print the successful message indicating the new entity has been added.
        cout << successMessage;

        // Print entity info
        printInfo(newEntity);
    }
};
