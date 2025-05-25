# Bank System with ATM Service

This is an alpha version of a **Bank Management System with ATM functionalities**, written in C++. It simulates a banking environment with client records, user access control, and a separate ATM service module. 

The system uses a **text file as a local database** to store client information such as name, account number, PIN code, and account balance.

---

## 🔧 Project Components

### 🧑‍💼 Users
- Users are administrators or employees who manage clients.
- Each user has:
  - Name
  - Password
  - Permissions (which define what client functions they can access)

### 👥 Clients
- Client info is stored in a `.txt` file and includes:
  - Full Name
  - Account Number
  - PIN Code
  - Account Balance

---

## ✨ Main Features

### 👨‍💼 User Panel
- User login with name and password
- Role-based permission system
- User functions:
  - Show user list
  - Add new user
  - Update user info (permissions & password)
  - Delete user
  - Find user info
  - Exit

### 🏦 Bank System (Admin Panel)
- Client management (permission-controlled):
  - Show client list
  - Add new client
  - Delete client
  - Update client info
  - Find a client
  - Transactions (deposit, withdraw, check total balance)
  - Exit

> ⚠️ If a user lacks permission for an action, a message will appear:  
> `"This User Doesn't Have the Permission, Please Contact the Admin."`

### 🏧 ATM Service (Client Panel)
- Uses same client `.txt` file
- Allows clients to:
  - Deposit
  - Withdraw
  - Quick Withdraw (small, predefined amounts)
  - Check balance
  - logout

---

## 🗂 File Structure
- There are Several Folders that determine the different versions (updates) of the project as every update contain new functionalities to the system at all.
- 
- The Final Version (till now) is Third Version Folder.

/Bank-System-With-ATM-Service/
│
├── clients.txt # Text file database for all clients
├── BankSystem.cpp # Main bank system code
├── ATMService.cpp # ATM functionality module (in a different Folder named ATM Service Version)
├── users.txt # User accounts with permissions
└── README.md # This file

---

## 🏁 How to Run

1. Make sure you have a C++ compiler (like g++ or use Visual Studio Code).
2. Download, Compile and run the main bank system (And The ATM Service).

---

## 👤 Author
Andrew Remon
1st-year Computer Science student
Passionate about systems programming and software architecture.

---

## 📜 License
This project is under development and currently for learning purposes only. No license has been specified yet.

---

## 📝 Notes

- This is an alpha version — expect changes and improvements.
- The text files (`clients.txt`, `users.txt`) must exist before running the system.
- Be cautious when editing the text files manually — incorrect formatting may crash the program.
- Permissions are checked before each client function — unauthorized users will be blocked.
- ATM Service assumes correct account number and PIN inputs; no encryption is implemented yet.
- The Project Text Files Contains Some Predefined Data just to make sure the project runs well, Feel free to change, add, update the info through you project scope :)
