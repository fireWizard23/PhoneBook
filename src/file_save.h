#pragma once

#include <fstream>
#include <vector>
#include "contact.h"

void SaveToFile(vector<Contact> allContacts)
{
    ofstream file("contacts_save.txt", ios::out);
    if (file.is_open())
    {
        char n = '\n';
        for (Contact c : allContacts)
        {
            file << c.name << n;
            file << c.number << n;
            file << c.address << n;
            file << "\n";
        }
    }
    file.close();
}

vector<Contact> RetrieveData()
{
    vector<Contact> allContacts;
    fstream file("../contacts_save.txt", ios::in);
    if (file.is_open())
    {
        string t;
        Contact contact;
        int index = 0;
        while (getline(file, t))
        {
            cout << t << " " << index << endl;
            switch (index)
            {
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
            if (index + 1 == 3)
            {

                allContacts.push_back(contact);
            }
            if (!IsEmpty(t))
            {
                index = (index + 1) % 3;
            }
        }
    }
    file.close();
    return allContacts;
}
