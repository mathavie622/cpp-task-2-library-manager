#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member
{
private:
    int memberId;
    string name;

public:
    Member();
    Member(int id, string name);

    int getMemberId() const;
    string getName() const;

    string toFileString() const;
    void display() const;
};

#endif
