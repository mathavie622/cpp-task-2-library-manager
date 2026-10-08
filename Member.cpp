#include "Member.h"
#include <iostream>

using namespace std;

Member::Member()
{
    memberId = 0;
    name = "";
}

Member::Member(int id, string name)
{
    this->memberId = id;
    this->name = name;
}

int Member::getMemberId() const
{
    return memberId;
}

string Member::getName() const
{
    return name;
}

string Member::toFileString() const
{
    return to_string(memberId) + "|" + name;
}

void Member::display() const
{
    cout << "Member ID: " << memberId << endl;
    cout << "Name: " << name << endl;
    cout << "-----------------------------" << endl;
}
