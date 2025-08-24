/**
 * @file clsLoginScreen.h
 * @brief Declares the `clsLoginScreen` class for handling user login functionality.
 *
 * ## Overview
 * The `clsLoginScreen` class is responsible for providing the login interface
 * of the system. It displays the login screen, validates user credentials,
 * and redirects the user to the main menu upon successful authentication.
 *
 * ## Responsibilities
 * - Prompt users to enter their credentials.
 * - Authenticate users against stored records.
 * - Restrict access after multiple failed attempts.
 * - Register successful logins for auditing purposes.
 *
 * ## Relationships
 * - **Inherits from:** `clsScreen` (for header display).
 * - **Uses:**
 *   - `clsBankUser` for validating credentials.
 *   - `clsGlobal` to set the logged-in user (`currentUser`).
 *   - `clsLoginLogger` for storing login attempts in a log file.
 *   - `clsMainScreen` to redirect upon successful login.
 */
#pragma once
#include <iostream>
#include "../Misc/clsScreen.h"
using namespace std;


/**
 * @class clsLoginScreen
 * @brief Manages the login process for system users.
 *
 * ## Overview
 * The `clsLoginScreen` class displays the login interface, validates the entered
 * username and password, and enforces a maximum number of login attempts.
 * Once a user is authenticated, it redirects to the main system menu.
 *
 * ## Features
 * - Displays a login screen with header.
 * - Handles user credential input.
 * - Enforces up to 3 login attempts.
 * - Logs successful logins.
 *
 * ## Design
 * - **Static methods**: Ensures login is accessible globally without instantiation.
 * - **Protected inheritance**: Inherits screen header functionality from `clsScreen`.
 */
class clsLoginScreen : protected clsScreen
{
    /**
     * @brief Handles the login process by validating user credentials.
     *
     * ## Behavior
     * - Prompts the user to enter a username and password.
     * - Verifies credentials against system records.
     * - Allows up to 3 attempts before locking access.
     * - Logs successful login attempts.
     * - On success, redirects to the main menu.
     *
     * @note This method is private and only used internally by `showLogInScreen()`.
     */
    static void _login();

public:
    /**
     * @brief Displays the login screen to the user.
     *
     * ## Behavior
     * - Draws a formatted header using `clsScreen`.
     * - Invokes `_login()` to handle the authentication process.
     *
     * Displays the login screen and handles authentication.
     */
    static void showLogInScreen();
};


