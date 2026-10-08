#include "Book.h"
#include <iostream>

using namespace std;

Book::Book()
{
    bookId = 0;
    title = "";
    author = "";
    available = true;
}

Book::Book(int id, string title, string author, bool available)
{
    this->bookId = id;
    this->title = title;
    this->author = author;
    this->available = available;
}

int Book::getBookId() const
{
    return bookId;
}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

bool Book::isAvailable() const
{
    return available;
}

void Book::setAvailable(bool status)
{
    available = status;
}

string Book::toFileString() const
{
    return to_string(bookId) + "|" + title + "|" + author + "|" +
           (available ? "1" : "0");
}

void Book::display() const
{
    cout << "Book ID: " << bookId << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Status: "
         << (available ? "Available" : "Issued") << endl;

    cout << "-----------------------------" << endl;
}
