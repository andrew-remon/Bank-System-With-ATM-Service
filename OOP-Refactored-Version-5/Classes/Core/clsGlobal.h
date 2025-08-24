/**
 * @file clsGlobal.h
 * @brief Declares global constants and variables used across the Bank System.
 *
 * ## Overview
 * This file centralizes global values that need to be accessed throughout the project,
 * including file paths for persistent storage and the currently logged-in user.
 * It ensures consistency by keeping these values in one place.
 *
 * ## Key Responsibilities
 * - Defines the file paths used for storing and retrieving client, user, login,
 *   and transfer data.
 * - Provides a global `currentUser` object to track the logged-in user session.
 *
 * ## Globals
 * - ClientsDataFile: Path to the clients data file.
 * - UsersDataFile: Path to the users data file.
 * - LoginRegisterFile: Path to the login activity log file.
 * - TransferLogsFile: Path to the transfer log file.
 * - currentUser: Represents the currently logged-in user (session state).
 */
#pragma once
#include <iostream>
#include <string>

class clsBankUser; // forward definition to avoid Circular Dependency Issue.

extern const std::string ClientsDataFile;  // Declare, but don’t define
extern const std::string UsersDataFile;
extern const std::string LoginRegisterFile;
extern const std::string TransferLogsFile;
extern clsBankUser currentUser;
