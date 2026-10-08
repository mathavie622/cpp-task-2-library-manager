#ifndef LOAN_H
#define LOAN_H

#include <string>
using namespace std;

class Loan
{
private:
    int bookId;
    int memberId;

public:
    Loan();
    Loan(int bookId, int memberId);

    int getBookId() const;
    int getMemberId() const;

    string toFileString() const;
};

#endif
