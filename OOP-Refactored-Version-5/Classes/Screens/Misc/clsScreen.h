/**
 * @file clsScreen.h
 * @brief Declares the `clsScreen` base class for displaying formatted screen headers.
 *
 * ## Overview
 * This file provides the `clsScreen` class, which serves as a protected base class
 * for other UI screens in the system. It includes functionality to draw a
 * standardized header section containing:
 * - A title (screen name).
 * - An optional subtitle (screen context).
 * - The current logged-in user’s full name.
 * - The current date.
 *
 * ## Relationships
 * - **Inherits by:** Screen-related classes (e.g., `clsMainScreen`, `clsUserScreen`).
 * - **Uses:**
 *   - `clsDate` for date formatting.
 *   - `clsGlobal` for accessing the `currentUser`.
 *   - `clsBankUser` for user information.
 */

#pragma once
#include <iostream>
#include "../../Utils/clsDate.h"
#include "../../Core/clsGlobal.h"
#include "../../Core/clsBankUser.h"
using namespace std;

/**
 * @class clsScreen
 * @brief Base class for UI screens, providing a reusable screen header.
 *
 * ## Overview
 * The `clsScreen` class is intended to be inherited by other screen classes
 * that need to display a consistent header layout.
 *
 * ## Features
 * - Displays a formatted screen header with:
 *   - Title
 *   - Optional subtitle
 *   - Current user information
 *   - Current date
 *
 * ## Design
 * - **Protected Methods**: Ensures that only derived screen classes can call header rendering.
 * - **Consistency**: Provides a unified look across all system screens.
 */
class clsScreen
{
protected :
    /**
     * @brief Draws a formatted header for a screen.
     *
     * @param title The main title of the screen.
     * @param subTitle (optional) A subtitle providing more context for the screen.
     *
     * ## Output
     * The header is printed in the following format:
     * ```
     * ____________________________________________
     *                  <Title>
     *                 <Subtitle>
     * ____________________________________________
     *        User: <Full Name of currentUser>
     *        Date: <Current Date>
     * ```
     *
     * ## Example
     * ```cpp
     * _drawScreenHeader("Main Menu", "Manage Users");
     * ```
     *
     * Would output:
     * ```
     * ____________________________________________
     *                  Main Menu
     *                 Manage Users
     * ____________________________________________
     *               User: John Smith
     *               Date: 2025-08-20
     * ```
     */
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
    }
};
