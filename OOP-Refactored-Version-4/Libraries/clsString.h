#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
    string _value;

    static char invertLetterCase(char ch)
    {
        return (isupper(ch) ? tolower(ch) : toupper(ch));
    }

    static bool isVowel(char ch)
    {
        char arVowels[] = {'a', 'e', 'i', 'o', 'u'};

        for (char &vowel : arVowels)
        {
            if (tolower(ch) == vowel) return true;
        }

        return false;
    }

public:
    clsString()
    {
        _value = "";
    }

    clsString(string value)
    {
        _value = value;
    }

    void setValue(string newValue)
    {
        _value = newValue;
    }

    string getValue()
    {
        return _value;
    }

    static string capitalize(string s)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {
            if(s[i] != ' ' && isFirstLetter) s[i] = toupper(s[i]);

            // cout << s[i];

            isFirstLetter = (s[i] == ' ' ? true : false);
        }

        return s;
    }

    void capitalize()
    {
        _value = capitalize(_value);
    }

    static string decapitalize(string s)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {
            if(s[i] != ' ' && isFirstLetter) s[i] = tolower(s[i]);

            // cout << s[i];

            isFirstLetter = (s[i] == ' ' ? true : false);
        }

        return s;
    }

    void decapitalize()
    {
        _value = decapitalize(_value);
    }

    static string upperCase(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = toupper(s[i]);
        }
        return s;
    }

    void upperCase()
    {
        _value =  upperCase(_value);
    }

    static string lowerCase(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    void lowerCase()
    {
        _value = lowerCase(_value);
    }

    static string invertCase(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = invertLetterCase(s[i]);
        }

        return s;
    }

    void invertCase()
    {
        _value = invertCase(_value);
    }

    static int countLetter(string s, char ch)
    {
        int counter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ch) counter++;
        }

        return counter;
    }

    int countLetter(char ch)
    {
        return countLetter(_value, ch);
    }

    static int countVowelLetters(string s)
    {
        int counter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (isVowel(s[i])) counter++;
        }

        return counter;
    }

    int countVowelLetters()
    {
        return countVowelLetters(_value);
    }

    static void printVowelLetters(string s)
    {
        int counter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (isVowel(s[i])) cout << s[i] << " ";
        }
    }

    void printVowelLetters()
    {
        printVowelLetters(_value);
    }

    static void printEachWord(string s)
    {
        string divider = " ";
        int pos = 0;

        while ((pos = s.find(divider)) != s.npos)
        {
            string sWord = s.substr(0, pos);
            if (sWord != "") cout << sWord << endl;
            s.erase(0, pos+divider.length());
        }

        if (s != "") cout << s;
    }

    void printEachWord()
    {
        printEachWord(_value);
    }

    static short countWords(string s)
    {
        string divider = " ";
        short pos = 0, counter = 0;

        while ((pos = s.find(divider)) != s.npos)
        {
            string sWord = s.substr(0, pos);
            if (sWord != "") counter++;
            s.erase(0, pos+divider.length()); // pos + 1 to include the whitespace char.
        }

        if (s != "") counter++;

        return counter;
    }

    short countWords()
    {
        return countWords(_value);
    }

    static void split(string s, vector <string> &vWords, string divider = " ")
    {
        short pos = 0;

        while ((pos = s.find(divider)) != s.npos)
        {
            string token = s.substr(0, pos);
            if (token != "") vWords.push_back(token);
            s.erase(0, pos+divider.length()); // pos + 1 to include the whitespace char.
        }

        if (s != "") vWords.push_back(s);
    }

    void split(vector <string> &vWords, string divider = " ")
    {
        split(_value, vWords);
    }

    static string leftTrim(string s)
    {
        char divider = ' ';
        string newS = "";

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == divider) continue;
            else
            {
                newS = s.substr(i, s.size());
                break;
            }
        }
        return newS;
    }

    void leftTrim()
    {
        _value = leftTrim(_value);
    }

    static string rightTrim(string s)
    {
        char divider = ' ';
        string newS = "";
        for (int i = s.length()-1; i >= 0; i--)
        {
            if (s[i] == divider) continue;
            else
            {
                newS = s.substr(0, i+1);
                break;
            }
        }
        return newS;
    }

    void rightTrim()
    {
        _value = rightTrim(_value);
    }

    static string trim(string s)
    {
        return leftTrim(rightTrim(s));
    }

    void trim()
    {
        _value = trim(_value);
    }

    static string join(vector <string> &vWords, string separator = " ")
    {
        string statement = "";

        for (string word : vWords)
        {
            if (word == vWords[vWords.size()-1]) statement = statement + word;
            else statement = statement + word + separator;
        }

        return statement;
    }

    static string reverse(string s, vector <string> &vWords, string separator = " ")
    {

        split(s, vWords);

        string statement = "";

        for (int i = vWords.size()-1; i >= 0; i--)
        {
            if (i == 0) statement = statement + vWords[i];
            else statement = statement + vWords[i] + separator;
        }

        return statement;
    }

    void reverse(vector <string> vWords, string separator = " ")
    {
        _value = reverse(_value, vWords);
    }

    static string replace(string oldWord, string newWord, string & s, vector <string> &vWords)
    {
        split(s, vWords);

        for (string &word : vWords)
        {
            if (oldWord == word) word = newWord;
        }

        return join(vWords);
    }

    void replace(string oldWord, string newWord, vector <string> &vWords)
    {
        _value = replace(oldWord, newWord, _value, vWords);
    }

    static string removePunctuation(string s)
    {
        string newString = "";
        for (char ch : s)
        {
            if (!ispunct(ch)) newString += ch;
        }

        return newString;
    }

    void removePunctuation()
    {
        _value = removePunctuation(_value);
    }

    static short length(string s)
    {
        return s.length();
    }

    short length()
    {
        return _value.length();
    }
};
