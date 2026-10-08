#include "Loan.h"

Loan::Loan()
{
    bookId = 0;
    memberId = 0;
}

Loan::Loan(int bookId, int memberId)
{
    this->bookId = bookId;
    this->memberId = memberId;
}

int Loan::getBookId() const
{
    return bookId;
}

int Loan::getMemberId() const
{
    return memberId;
}

string Loan::toFileString() const
{
    return to_string(bookId) + "|" + to_string(memberId);
}
