#include <iostream>
#include <vector>
#include<conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include<string.h>

using namespace std;


struct Contact {
    string number;
    string name;
    string address;


    Contact() : Contact("", "", ""){};

    Contact(string number, string name, string address) :
            number(number), name(name), address(address) {};


    string GetDisplayText() {
        string n = "\n";
        return n+"Name: " + name + n + "Number: " + number + n + "Address: " + address + n;
    }


};

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_SPACE = 32;
const int KEY_W = 119;
const int KEY_S = 115;

void home();

void pause() {
    cout << endl << endl;
    system("PAUSE");

}

void clear_screen()
{
    system("CLS");
}

void clear_input()
{
    cin.clear();
    while (cin.get() != '\n')
    {
    }
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



int interactiveInput(string label, vector<string> choices, string endLabel = "Press ENTER/SPACE to select. Arrow keys to move. \n")
{
    int _index = 0;
    int c = 0;
    bool looping = true;
    int choiceIndex = 0;
    int maxNum = choices.size() - 1;

    clear_screen();
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
        clear_screen();
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

bool isEmpty(string h) {
    return h.empty() || h.find_first_not_of(' ') == string::npos;
}

void getLine(string label, string& input) {
    while(isEmpty(input)) {
        acout(label);
        getline(cin, input);
    }
}


vector<Contact> allContacts;
int contactListCount = 0;


void ViewAllContactsPage() {
    clear_screen();
    if(allContacts.size() ==0) {
        acout( "No contacts to show :( \n");
    }
    int index = 0;
    for(Contact h : allContacts) {
        cout << index + 1 << ".) ";
        cout << h.GetDisplayText() << endl;
        index++;
        Sleep(70);
    }

    pause();
    home();
}

void AddContactPage() {
    clear_screen();
    Contact newContact;
    getLine("Enter name: ", newContact.name);
    getLine("Enter Number: ", newContact.number);
    getLine("Enter Address: ", newContact.address);
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
        allContacts.push_back(newContact);
        cout << "Added sucessfully!";
    }

    pause();
    home();

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


void FindContactPage() {
    clear_screen();
    string name = "";
    vector<Contact> contactsFound;

    getLine("Enter name: ", name);
    for(Contact c : allContacts) {
        if(IsEqual(c.name, name)) {
            contactsFound.push_back(c);
        }
    }

    if(contactsFound.size() > 0) {
        for(Contact c : contactsFound) {
            cout << c.GetDisplayText();
        }
    } else {
        acout("No contact found with the name. :(");
    }

    pause();
    home();
}


void DeleteContactPage() {
    clear_screen();

    string name;
    Contact n;
    bool foundContact = false;
    getLine("Enter name: ", name);
    int index = 0;
    for(Contact c : allContacts) {
        if(c.name == name) {
            n = c;
            foundContact = true;
            index++;
            break;
        }
        index++;
    }

    if(foundContact) {
        cout << n.GetDisplayText();
        int res = interactiveInput(
             "Are you sure you want to delete " + n.GetDisplayText(),
             {
                 "Back", "Delete"
             }
        );
        if(res == 1) {
            allContacts.erase(allContacts.begin() + index);
            cout << endl;
            acout("Contact deleted!");
        }
    } else {
        acout("No contact found with the name. :(");
    }

    pause();
    home();
}




void home() {
    int a = interactiveInput(
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

void saveToFile() {
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

void retrieveData() {
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
            if(!isEmpty(t)) {
                index = (index + 1) % 3;
            }


        }
    }
    file.close();
}


int main() {

    retrieveData();
    home();
    saveToFile();
}
