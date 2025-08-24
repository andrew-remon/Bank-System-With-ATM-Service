# Bank Management System: A C++ Development Journey

![Final application main screen](Assets/Images/Version5(2).png)

## Table of Contents
- [Project Overview](#project-overview)
- [Project Features](#project-features)
- [Versions and Development Stages](#versions-and-development-stages)
  - [Structured-Version-1](#structured-version-1)
  - [Structured-Version-2](#structured-version-2)
  - [Structured-Version-3](#structured-version-3)
  - [OOP-Refactored-Version-4](#oop-refactored-version-4)
  - [OOP-Refactored-Version-5](#oop-refactored-version-5)
  - [Structured-ATM-Service](#structured-atm-service)
- [How to Run a Specific Version](#how-to-run-a-specific-version)
- [Technologies Used](#technologies-used)
- [Author](#author)

---

## Overview

This project is a console-based **Bank Management System** written in C++. It simulates a complete banking environment, demonstrating the evolution from a structured, procedural design to an Object-Oriented Programming (OOP) paradigm. 
The system includes robust **client and user management**, an authentication process with access control, and a separate **ATM service module**.

All data, including client and user information, transaction logs, and login histories, is persisted locally in text files. Key features include:
- **Client & User Management:** Comprehensive CRUD (Create, Read, Update, Delete) operations.
- **Secure Authentication:** User login with password masking and bitmask-based access control.
- **Detailed Logging:** Tracks user logins and financial transfers, providing a full audit trail.

The project's primary goal is to illustrate the transition from a procedural, structured programming approach to a more robust and scalable Object-Oriented Programming (OOP) paradigm.
Each folder represents a distinct version, highlighting the architectural changes, refactoring efforts, and improvements made throughout the development process.

---

## 🌟 Project Features

- **Client & User Management:** Complete CRUD operations for clients and system users.
- **Secure Authentication:** User login with password masking and controlled access via a login screen.
- **Financial Transactions:** Supports deposits, withdrawals, and secure money transfers between accounts.
- **Detailed Logging:** Tracks and displays login attempts and financial transfer histories.
- **Data Persistence:** All data is stored and managed using local text files.

---
  
## ✨ Versions And Development Stages

### Structured-Version-1
**Description**: This is the initial release of the bank system, built entirely on a procedural and structured programming model. The focus of this version is to establish the foundational client management features. It includes a basic user interface and core functionalities for managing client data.

**Key Features**:
- **Client Management**: Supports basic CRUD operations for clients.
- **Data Storage**: All client data is stored in a simple text file, with functions handling the reading and writing processes.

**Architectural Notes**:  The code is organized into a set of functions, with data being passed between them. It represents a straightforward, top-down design approach.

<br>

### Structured-Version-2
**Description**: Building upon the initial version, this release expands the system's functionality by introducing financial transaction features. While still operating within the structured programming paradigm, this version adds the capability for clients to perform withdrawals and deposits.

**Key Features**:
- **Withdrawal & Deposit**: New screens were implemented to allow for monetary transactions.
- **Total Balance View**: A feature was added to display the aggregated total balance of all accounts in the system.

**Architectural Notes**: This version introduces more complex transaction logic and state management, but still relies on procedural functions to manage all operations.
<br>

### Structured-Version-3
**Description**: This is the final release within the structured programming series. It marks a significant upgrade by introducing user authentication and access control. This version establishes the groundwork for a multi-user environment, where different users can log in and perform actions based on their permissions.

**Key Features**: 
- **Login Screen**: A dedicated login screen was created to authenticate users.
- **User Management**: A new set of CRUD operations for system users was implemented.
- **Controlled Access**: The system now restricts access to certain functionalities based on user credentials. The Access is defined by Bitmask flags using bitwise operators.

**Architectural Notes**: The introduction of user management and access control highlights the growing complexity of the structured design, paving the way for the need to refactor into a more scalable paradigm.

<br>

### OOP-Refactored-Version-4
**Description**: This is the project's most critical release, representing a complete **refactoring from a structured to an Object-Oriented Programming (OOP) architecture.** The core entities of the system *(Client and User)* are now encapsulated into classes, which dramatically improves code organization, reusability, and maintainability.

**Key Architectural Changes**: 
- **Full OOP Refactoring**: The entire system was rebuilt using classes for Client, User, and other relevant entities.
- **UI Optimization**: All UI screens were updated to dynamically display the currently logged-in user and the current date, enhancing the user experience and demonstrating proper state management within an OOP context.

**Purpose**: This version serves as the central showcase of transitioning a project from one architectural style to another, demonstrating a deeper understanding of software design principles.

<br>

### OOP-Refactored-Version-5
**Description**: This is the final and most robust version of the bank management system. It builds upon the solid OOP foundation established in Version 4 by adding several new features and significant code enhancements. This version demonstrates a refined and polished application.

**Key Features & Enhancements**:
- **Transfer Functionality**: A new feature was added to allow for secure money transfers between two client accounts. Transfer logs are now tracked and viewable.
- **Login Security**: The system now automatically closes after three consecutive failed login attempts, improving security.
- **Login Logs**: A new screen was implemented to display the history of all user login attempts.
- **Code Restructuring**: The CRUD operations for both users and clients were standardized using a C++ template, which improves code reusability and reduces redundancy.
- **Clean File Structure**: Header and source files were reorganized into well-defined, clean-named folders, improving project navigation and professional appearance.
- **Comprehensive Documentation**: This is the only version of the project that includes **professional-level documentation for every file, class, and method**. This effort demonstrates a commitment to writing clean, maintainable code and providing clear instructions for future developers.

<br>

### Structured-ATM-Service
**Description**: This folder stands as an independent module separate from the main development journey. It is a standalone ATM service built using the original structured programming paradigm. Its purpose is to showcase how the structured approach could be applied to a specific, self-contained service within the banking system ecosystem.

**Key Features**:
- **Client Authentication**: The service requires clients to authenticate with their account number and PIN.
- **ATM Transactions**: Provides core ATM functionalities, including quick withdrawal, specific withdrawal amounts, deposits, and balance inquiry.

**Purpose**: This module demonstrates proficiency in creating a functional, targeted service as a **client panel** and highlights the difference in design philosophy compared to the main, more complex OOP-based application.

--- 

## 🏁 How to Run a Specific Version
Make sure you have a C++ compiler (like g++ or use Visual Studio Code).
Each folder is self-contained. To run any version, navigate to its directory in your terminal and execute the main script.\

1.  Open your terminal.
2.  Navigate to the project root directory.
3.  Enter the specific folder you want to run:
    ```bash
    cd OOP-Refactored-Version-5
    ```
4.  Run the main script (assuming `main.cpp` is the entry point):
    ```bash
    main.cpp
    ```
    *(Note: Replace `main.cpp` with the actual name of your main script if it's different.)*

---

## 🔧 Technologies Used

* **Primary Language:** C++
* **Concepts & Paradigms:**
    * Object-Oriented Programming (OOP)
    * Structured Programming
    * Data Structures (Vectors, Text Files for data persistence)
    * File Handling
* **C++ Standard Library:**
    * `<iostream>` and `<string>` for basic input/output and string manipulation.
    * `<iomanip>` for input/output manipulation (e.g., formatting tables and numbers).
    * `<type_traits>` for compile-time type information, specifically using `is_same()`.
    * Other standard headers used for various functionalities (e.g., `<vector>`, `<fstream>`).
 
---

## 👤 Author

**Andrew Remon** - [My GitHub Profile](https://github.com/andrew-remon)
<br>
let's connect on [LinkedIn](https://www.linkedin.com/in/andrewremon)
