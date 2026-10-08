#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
private:
    int bookId;
    string title;
    string author;
    bool available;

public:
    Book();
    Book(int id, string title, string author, bool available = true);

    int getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    bool isAvailable() const;

    void setAvailable(bool status);

    string toFileString() const;
    void display() const;
};

#endif
