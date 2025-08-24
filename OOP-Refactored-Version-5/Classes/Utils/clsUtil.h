#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:
    enum class enCharType { smallLetter = 1, capitalLetter = 2, specialChar = 3, digit = 4, mixChars = 5 };

    static void sRand()
    {
        srand((unsigned)time(NULL));
    }

    static int pickRandomNumber()
    {
        return rand();
    }

    static int pickRandomNumberFromRange(int from, int to)
    {
        int randomNumber = rand() % (to - from + 1) + from;
        return randomNumber;
    }

    static string encryptText(string name, short encryptionKey = 3)
    {
        string encryptedName = "";
        for(int i = 0; i <= name.length(); i++)
        {
            encryptedName += char( int(name[i]) + encryptionKey);
        }
        name = encryptedName;
        return name;
    }

    static string decryptText(string name, short decryptionKey = 3)
    {
        string decryptedName = "";
        for(int i = 0; i <= name.length(); i++)
        {
            decryptedName += char(int(name[i]) - decryptionKey);
        }
        return decryptedName;
    }

    static char pickRandomCharacter(enCharType charType)
    {
        switch (charType)
        {
        case enCharType::smallLetter:
            return (char)pickRandomNumberFromRange(97, 122);
            break;
        case enCharType::capitalLetter:
            return (char)pickRandomNumberFromRange(65, 90);
            break;
        case enCharType::specialChar:
            return (char)pickRandomNumberFromRange(33, 47);
            break;
        case enCharType::digit:
            return (char)pickRandomNumberFromRange(48, 57);
            break;
        case enCharType::mixChars:
            return (char)pickRandomNumberFromRange(33, 122);
            break;
        }
        return '\0';
    }

    static string generateWord(enCharType charType, int length)
    {
        string word;

        for (int i = 0; i < length; i++)
        {
            word += pickRandomCharacter(charType);
        }

        return word;
    }

    static string generateKey(enCharType charType)
    {
        string key = "";

        for(int j = 1; j <= 19; j++)
        {
            if (j % 5 == 0)
                key += "-";
            else
                key += (char)pickRandomCharacter(charType);
        }

        return key;
    }

    static void generateKeys(int keysNumber, enCharType charType)
    {
        for(int i = 1; i <=keysNumber; i++)
        {
            cout << "key [" << i << "] : ";

            cout << generateKey(charType) << endl;
        }
    }

    static void fillArrayWithNumbers(int arr[100], int arrLength, int from, int to)
    {
        for(int i = 0; i < arrLength; i++)
        {
            arr[i] = pickRandomNumberFromRange(from, to);
        }
    }

    static void fillArrayWithWords(string arr[100], int arrLength, enCharType charType, int wordLength)
    {
        for(int i = 0; i < arrLength; i++)
        {
            arr[i] = generateWord(charType, wordLength);
        }
    }

    static void fillArrayWithKeys(string arr[100], int arrLength, enCharType charType)
    {
        for(int i = 0; i < arrLength; i++)
        {
            arr[i] = generateKey(charType);
        }
    }

    static void showArray(string arr[100], int arrLength)
    {
        for(int i = 0; i < arrLength; i++)
        {
            cout << "Array [" << i << "]: " << arr[i] << endl;
        }
    }

    // note: array is always passed by its original value (pointer), even if it's like a copy.
    static void showArray(int arr[100], int arrLength)
    {
        for(int i = 0; i < arrLength; i++)
        {
            cout << "Array [" << i << "]: " << arr[i] << endl;
        }
    }

    static void swap(int & firstInt, int & secondInt)
    {
        int tempInt;

        tempInt = firstInt;
        firstInt = secondInt;
        secondInt = tempInt;
    }

    static void swap(double & firstDouble, double & secondDouble)
    {
        double tempDouble;

        tempDouble = firstDouble;
        firstDouble = secondDouble;
        secondDouble = tempDouble;
    }

    static void swap(string & firstWord, string & secondWord)
    {
        string tempWord;

        tempWord = firstWord;
        firstWord = secondWord;
        secondWord = tempWord;
    }

    static void swap(clsDate & firstDate, clsDate & secondDate)
    {
        clsDate tempDate;

        tempDate = firstDate;
        firstDate = secondDate;
        secondDate = tempDate;
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[pickRandomNumberFromRange(1, arrLength) - 1], arr[pickRandomNumberFromRange(1, arrLength) - 1]);
        }

    }

    enum enPlaces { thousand = 1, million = 2, billion = 3 };

    static int getNumPartsLength(string number)
    {
        return ceil(float(number.length())/3);
    }

    static void divideNumberIntoParts(vector <string> & vDividedNumbers, string number, int chunkslength)
    {
        int intNumber = stoi(number);

        for (int i = chunkslength; i > 0; i--)
        {
            int part = intNumber%1000;
            intNumber /= 1000;
            vDividedNumbers.push_back(to_string(part));
        }
    }

    static void convertNumberToLetterForm(vector <string> &vNumberInLetter, vector <string> vDividedNumbers, int chunkslength)
    {
        map <char, string> mpNumToLetter, mpTenth;
        map <string, string> mpTenthOfOne;

        mpNumToLetter = {
            {'1', "One"},
            {'2', "Two"},
            {'3', "Three"},
            {'4', "Four"},
            {'5', "Five"},
            {'6', "Six"},
            {'7', "Seven"},
            {'8', "Eight"},
            {'9', "Nine"}
        };
        mpTenthOfOne = {
            {"10", "Ten"},
            {"11", "Eleven"},
            {"12", "Twelve"},
            {"13", "Thirteen"},
            {"14", "Fourteen"},
            {"15", "Fifteen"},
            {"16", "Sixteen"},
            {"17", "Seventeen"},
            {"18", "Eighteen"},
            {"19", "Nineteen"}
        };
        mpTenth = {
            {'2', "Twenty"},
            {'3', "Thirty"},
            {'4', "Forty"},
            {'5', "Fifty"},
            {'6', "Sixty"},
            {'7', "Seventy"},
            {'8', "Eighty"},
            {'9', "Ninety"}
        };

        // Handling The Zero Case
        if (vDividedNumbers.front() == "0" && vDividedNumbers.size() == 1) return vNumberInLetter.push_back("Zero");

        for (int j = chunkslength-1; j >= 0; j--)
        {
            string statement = "";
            for (int i = 0; i < vDividedNumbers[j].size(); i++)
            {
                // If the number is located between 1 and 99
                if (vDividedNumbers[j][i] == '1' && vDividedNumbers[j].size() == 2)
                {
                    statement += mpTenthOfOne[vDividedNumbers[j].substr(i, 2)];
                    break;
                }

                // If the number is Above 99
                if (i == 0 and vDividedNumbers[j].size() == 3)
                {
                    statement += mpNumToLetter[vDividedNumbers[j][i]] + " Hundred ";
                    continue;
                }

                // Handling every digit in every part of divided Number.
                if (i==1 && vDividedNumbers[j][i] == '1')
                {
                    statement += mpTenthOfOne[vDividedNumbers[j].substr(1, 2)];
                    break;
                }
                else if (vDividedNumbers[j].size() == 1)
                {
                    statement += mpNumToLetter[vDividedNumbers[j][i]];
                    break;
                }
                else
                {
                    statement += mpTenth[vDividedNumbers[j][i]] + " ";
                    statement += mpNumToLetter[vDividedNumbers[j][i+1]];
                    break;
                }
            }

            if (vDividedNumbers[j] != "0")
            {
                switch (enPlaces(j))
                {
                case enPlaces::thousand:
                    statement += " Thousand";
                    break;
                case enPlaces::million:
                    statement += " Million";
                    break;
                case enPlaces::billion:
                    statement += " Billion";
                    break;
                }
            }
            vNumberInLetter.push_back(statement);
        }
    }

    static string getNumberInLetterForm(vector <string> vNumberInLetter)
    {
        string letterForm = "";
        for (int i = 0; i < vNumberInLetter.size(); i++) letterForm += vNumberInLetter.at(i) + " ";
        return letterForm;
    }

    static string getNumberInLetterForm(string number)
    {
        vector <string> vDividedNumbers, vNumberInLetter;

        int chunkslength = getNumPartsLength(number);

        divideNumberIntoParts(vDividedNumbers, number, chunkslength);
        convertNumberToLetterForm(vNumberInLetter, vDividedNumbers, chunkslength);
        string numInLetter = getNumberInLetterForm(vNumberInLetter);
        return numInLetter;
    }

    static char confirm(string message)
    {
        char ans = 'n';
        cout << "\n\n" << message;
        cin >> ans;
        return ans;
    }
};
