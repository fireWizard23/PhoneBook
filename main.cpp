#include <iostream>
#include <vector>
#include<conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <functional>


using namespace std;


#pragma region ---------------------------- Function Declarations
void HomePage();
void ViewAllContactsPage();
void DeleteContactPage();
void AddContactPage();
void FindContactPage();
void RetrieveData();
void SaveToFile();
string Trim(const string& str);
bool IsNotValidPhoneNumber(const string& number);
#pragma endregion





#pragma region ---------------------------- Constants

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_SPACE = 32;
const int KEY_W = 119;
const int KEY_S = 115;

#pragma endregion




struct Contact {
    string number;
    string name;
    string address;


    Contact() : Contact("", "", ""){};

    Contact(string number, string name, string address) :
            number(number), name(name), address(address) {};


    string GetDisplayText() {
        string n = "\n";
        return "Name: " + name + n + "Number: " + number + n + "Address: " + address + n;
    }

    void TrimMembers() {
        number = Trim(number);
        name = Trim(name);
        address = Trim(address);
    }


};


#pragma region ----------------------------Global Variables

vector<Contact> allContacts;

#pragma endregion


int main() {

    RetrieveData();
    HomePage();
    SaveToFile();
    return 0;
}



#pragma region ---------------------------- General functions


bool IsValidPhoneNumber(const std::string& phoneNumber)
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
bool IsNotValidPhoneNumber(const std::string& phoneNumber) {
    return !IsValidPhoneNumber(phoneNumber);
}


string Trim(const string& str)
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

void Pause() {
    cout << endl << endl;
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

bool ContactCompare(const Contact& a, const Contact& b)
{
    // smallest comes first
    return a.name < b.name;
}



bool IsEqual(string a, string b) {
    if(a.size() != b.size()) {
        return false;
    }

    if(a == b) {
        return true;
    }
    int index = 0;
    for(char c : a) {
        if(toupper(c) != toupper(b[index])) {
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

bool IsEmpty(string h) {
    return h.empty() || h.find_first_not_of(' ') == string::npos;
}

void GetLine(string label, string& input, function<bool(const std::string&)> invalidator=IsEmpty) {
    while(invalidator(input)) {
        acout(label);
        getline(cin, input);
    }
}

#pragma endregion


#pragma region ---------------------------- File saving functions

void SaveToFile() {
    ofstream file ("contacts_save.txt", ios::out);
    if(file.is_open()) {
        char n = '\n';
        for(Contact c : allContacts) {
            file << c.name << n;
            file << c.number << n;
            file << c.address << n;
            file << "\n";
        }
    }
    file.close();
}

void RetrieveData() {
    fstream file ("contacts_save.txt", ios::in);
    if(file.is_open()) {
        string t;
        Contact contact;
        int index = 0;
        while(getline(file, t)) {
            cout << t << " " << index << endl;
            switch(index) {
            case 0:
                contact.name = t;
                break;
            case 1:
                contact.number = t;
                break;
            case 2:
                contact.address = t;
                break;
            }
            if(index + 1 == 3) {

                allContacts.push_back(contact);
            }
            if(!IsEmpty(t)) {
                index = (index + 1) % 3;
            }


        }
    }
    file.close();
}
#pragma endregion

#pragma region ---------------------------- Pages

void HomePage() {
    int a = InteractiveInput(
                     "PhoneBook \n \nWhat would you like to do?",
                     {"View All Contacts", "Find contact", "Add Contact", "Delete Contact", "Quit"});
    switch(a) {
    case 0:
        ViewAllContactsPage();
        break;
    case 1:
        FindContactPage();
        break;
    case 2:
        AddContactPage();
        break;
    case 3:
        DeleteContactPage();
        break;
    }

}

void ViewAllContactsPage() {
    ClearScreen();
    cout << "All contacts list" << endl<<endl;
    if(allContacts.size() ==0) {
        acout( "No contacts to show :( \n");
    }
    sort(allContacts.begin(), allContacts.end(), ContactCompare);
    int index = 0;
    for(Contact h : allContacts) {
        cout << index + 1 << ".) ";
        cout << h.GetDisplayText() << endl;
        index++;
        Sleep(70);
    }

    Pause();
    HomePage();
}

void AddContactPage() {
    ClearScreen();
    cout << "Create a new contact\n\n";
    Contact newContact;
    GetLine("Enter name: ", newContact.name);
    GetLine("Enter Number: ", newContact.number, IsNotValidPhoneNumber);
    GetLine("Enter Address: ", newContact.address);
    cout << endl;


    bool isUsed = false;
    for(Contact c : allContacts) {
        if(c.number == newContact.number) {
            acout("Contact number is already in used.");
            isUsed = true;
            break;
        }
    }
    if(!isUsed) {
        newContact.TrimMembers();
        allContacts.push_back(newContact);
        cout << "Added sucessfully!";
    }

    Pause();
    HomePage();

}

void FindContactPage() {
    ClearScreen();
    cout << "Find a contact\n\n";
    string name = "";
    vector<Contact> contactsFound;

    GetLine("Enter name: ", name);
    cout  << endl ;
    for(Contact c : allContacts) {
        if(IsEqual(c.name, name)) {
            contactsFound.push_back(c);
        }
    }

    if(contactsFound.size() > 0) {
        cout<< "Here are the contacts with the name: " << endl <<endl;
        for(Contact c : contactsFound) {
            cout << c.GetDisplayText() << endl;
        }
    } else {
        acout("No contact found with the name. :(");
    }
    Sleep(300);
    Pause();
    HomePage();
}

void DeleteContactPage() {
    ClearScreen();
    cout << "Delete a contact\n\n";
    string name = "";
    vector<Contact> contactsFound;
    vector<int> indexes;
    int index = 0;
    GetLine("Enter name: ", name);
    for(Contact c : allContacts) {
        if(IsEqual(c.name, name)) {
            contactsFound.push_back(c);
            indexes.push_back(index);
        }
        index++;
    }


    if(contactsFound.size() > 0) {
        if(contactsFound.size() == 1) {
            Contact n = contactsFound[0];
            cout << n.GetDisplayText();
            int res = InteractiveInput(
                 "Are you sure you want to delete \n\n" + n.GetDisplayText(),
                 {
                     "Back", "Delete"
                 }
            );
            if(res == 1) {
                allContacts.erase(allContacts.begin() + indexes[0]);
                cout << endl;
                acout("Contact deleted!");
            }
        } else {
            vector<string> choices = {"Back"};
            for(Contact c : contactsFound) {
                choices.push_back(c.GetDisplayText());
            }

            int res = InteractiveInput("Select contact to delete: ", choices);
            switch(res) {
            case 0:
                break;
            default:
                Contact n = contactsFound[res -1];
                cout << n.GetDisplayText();
                int res1 = InteractiveInput(
                     "Are you sure you want to delete \n\n" + n.GetDisplayText(),
                     {
                         "Back", "Delete"
                     }
                );
                if(res1 == 1) {
                    allContacts.erase(allContacts.begin() + indexes[res-1]);
                    cout << endl;
                    acout("Contact deleted!");
                }
                break;
            }
        }
    } else {
        acout("No contact found with the name. :(");
    }

    Pause();
    HomePage();
}

#pragma endregion


