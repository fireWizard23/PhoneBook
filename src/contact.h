#include <iostream>
#include <string>

using namespace std;

struct Contact
{
    string number;
    string name;
    string address;

    Contact() : Contact("", "", ""){};

    Contact(string number, string name, string address) : number(number), name(name), address(address){};

    string GetDisplayText()
    {
        string n = "\n";
        return "Name: " + name + n + "Number: " + number + n + "Address: " + address + n;
    }

    void TrimMembers()
    {
        number = Trim(number);
        name = Trim(name);
        address = Trim(address);
    }
};

bool ContactCompare(const Contact &a, const Contact &b)
{
    // smallest comes first
    return a.name < b.name;
}