#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <functional>
#include "constants.h"

using namespace std;

void Pause()
{
    cout << endl
         << endl;
    system("PAUSE");
}

void ClearScreen()
{
    system("CLS");
}

void acout(string h, bool skippable = true, int ms = 20)
{
    int index = 0;
    for (char c : h)
    {
        cout << c;
        index++;
        Sleep(ms);
        if (skippable && _kbhit())
        {
            getch();
            string rest = h.substr(index);
            cout << rest;
            break;
        }
    }
}

string Trim(const string &str)
{
    std::string result;
    bool prevIsWhitespace = true; // Initially set to true to remove leading whitespace

    for (char ch : str)
    {
        if (std::isspace(ch))
        {
            if (!prevIsWhitespace)
            {
                result.push_back(' ');
                prevIsWhitespace = true;
            }
        }
        else
        {
            result.push_back(ch);
            prevIsWhitespace = false;
        }
    }

    if (!result.empty() && std::isspace(result.back()))
        result.pop_back();

    return result;
}

bool IsValidPhoneNumber(const std::string &phoneNumber)
{
    // Check if the string contains only valid characters
    for (char ch : phoneNumber)
    {
        if (!std::isdigit(ch) && ch != '-' && ch != '(' && ch != ')' && ch != ' ' && ch != '+')
            return false;
    }

    // Count the number of digits in the string
    int digitCount = 0;
    for (char ch : phoneNumber)
    {
        if (std::isdigit(ch))
            digitCount++;
    }

    // Check if the phone number has at least 10 digits
    if (digitCount < 5)
        return false;

    // The phone number is valid
    return true;
}
bool IsNotValidPhoneNumber(const std::string &phoneNumber)
{
    return !IsValidPhoneNumber(phoneNumber);
}

bool IsEqual(string a, string b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    if (a == b)
    {
        return true;
    }
    int index = 0;
    for (char c : a)
    {
        if (toupper(c) != toupper(b[index]))
        {
            return false;
        }

        index++;
    }
    return true;
}

int InteractiveInput(string label, vector<string> choices, string endLabel = "Press ENTER/SPACE to select. Arrow keys to move. \n")
{
    int _index = 0;
    int c = 0;
    bool looping = true;
    int choiceIndex = 0;
    int maxNum = choices.size() - 1;

    ClearScreen();
    acout(label + "\n\n");
    Sleep(75);
    for (auto h : choices)
    {
        if (_index == choiceIndex)
        {
            cout << "=>";
        }
        else
        {
            cout << "  ";
        }
        cout << h;

        cout << "\n";
        choiceIndex++;
        Sleep(75);
    }
    acout("\n" + endLabel);
    while (looping)
    {
        choiceIndex = 0;
        ClearScreen();
        cout << label << endl
             << endl;

        for (string h : choices)
        {
            if (_index == choiceIndex)
            {
                cout << "=>";
            }
            else
            {
                cout << "  ";
            }
            cout << h;
            cout << endl;
            choiceIndex++;
        }
        cout << endl
             << endLabel;

        switch (c = getch())
        {
        case KEY_UP:
        case KEY_W:
            _index--;
            if (_index < 0)
            {
                _index = maxNum;
            }
            break;
        case KEY_DOWN:
        case KEY_S:
            _index++;
            if (_index > maxNum)
            {
                _index = 0;
            }
            break;
        case KEY_ENTER:
        case KEY_SPACE:
            looping = false;
            break;
        }
    }
    return _index;
}

bool IsEmpty(string h)
{
    return h.empty() || h.find_first_not_of(' ') == string::npos;
}

void GetLine(string label, string &input, function<bool(const std::string &)> invalidator = IsEmpty)
{
    while (invalidator(input))
    {
        acout(label);
        getline(cin, input);
    }
}