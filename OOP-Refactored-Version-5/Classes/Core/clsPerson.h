/**
 * @file clsPerson.h
 * @brief Defines the `clsPerson` class representing a basic person entity.
 *
 * ## Overview
 * This file contains the declaration of the `clsPerson` class, which models
 * basic personal information such as first name, last name, email, and phone number.
 *
 * ## Key Responsibilities
 * - Encapsulates personal data fields.
 * - Provides setters and getters for managing personal information.
 * - Offers utility methods such as retrieving the full name.
 */
#pragma once
#include <iostream>
using namespace std;

/**
 * @class clsPerson
 * @brief Represents a person with basic personal information.
 *
 * The `clsPerson` class encapsulates details such as first name, last name,
 * email address, and phone number. It provides methods to set and get
 * these details and utility to retrieve a full name string.
 *
 * ## Getters
 * All getters are marked as `const`, ensuring they do not modify the object state.
 */
class clsPerson
{
private:
    string _firstName, _lastName, _email, _phone;

public:

    /**
     * @brief Constructs a person with the given personal details.
     * @param fName First name of the person.
     * @param lName Last name of the person.
     * @param email Email address of the person.
     * @param phone Phone number of the person.
     */
    clsPerson(string fName, string lName, string email, string phone)
    {
        _firstName = fName;
        _lastName = lName;
        _email = email;
        _phone = phone;
    }

    /// @brief Sets the first name of the person.
    /// @param name New first name.
    void setFirstName(string name)
    {
        _firstName = name;
    }

    /// @brief Sets the last name of the person.
    /// @param name New last name.
    void setLastName(string name)
    {
        _lastName = name;
    }

    /// @brief Sets the email of the person.
    /// @param email New email address.
    void setEmail(string email)
    {
        _email = email;
    }

    /// @brief Sets the phone number of the person.
    /// @param phone New phone number.
    void setPhone(string phone)
    {
        _phone = phone;
    }

    /// @brief Retrieves the first name.
    /// @return First name string.
    string getFirstName() const
    {
        return _firstName;
    }

    /// @brief Retrieves the last name.
    /// @return Last name string.
    string getLastName() const
    {
        return _lastName;
    }

    /// @brief Retrieves the full name.
    /// @return Concatenation of first name and last name.
    string FullName() const
    {
        return _firstName + " " + _lastName;
    }

    /// @brief Retrieves the email address.
    /// @return Email string.
    string getEmail() const
    {
        return _email;
    }

    /// @brief Retrieves the phone number.
    /// @return Phone number string.
    string getPhone() const
    {
        return _phone;
    }
};
