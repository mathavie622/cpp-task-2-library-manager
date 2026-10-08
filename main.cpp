#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Book.h"
#include "Member.h"
#include "Loan.h"

using namespace std;

vector<Book> books;
vector<Member> members;
vector<Loan> loans;

const string DATA_FILE = "library_data.txt";

// Function declarations
void loadData();
void saveData();

void addBook();
void addMember();
void issueBook();
void returnBook();
void searchBook();
void displayAvailableBooks();
void displayMembers();
void displayIssuedBooks();

Book* findBook(int id);
Member* findMember(int id);


int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       OBJECT-ORIENTED LIBRARY\n";
        cout << "             MANAGER\n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Display Available Books\n";
        cout << "7. Display Members\n";
        cout << "8. Display Issued Books\n";
        cout << "9. Save & Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                addMember();
                break;

            case 3:
                issueBook();
                break;

            case 4:
                returnBook();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                displayAvailableBooks();
                break;

            case 7:
                displayMembers();
                break;

            case 8:
                displayIssuedBooks();
                break;

            case 9:
                saveData();
                cout << "\nData saved successfully!\n";
                cout << "Thank you for using Library Manager.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}


// Find Book
Book* findBook(int id)
{
    for (auto& book : books)
    {
        if (book.getBookId() == id)
        {
            return &book;
        }
    }

    return nullptr;
}


// Find Member
Member* findMember(int id)
{
    for (auto& member : members)
    {
        if (member.getMemberId() == id)
        {
            return &member;
        }
    }

    return nullptr;
}


// Add Book
void addBook()
{
    int id;
    string title;
    string author;

    cout << "\nEnter Book ID: ";
    cin >> id;

    if (findBook(id) != nullptr)
    {
        cout << "Book ID already exists.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    books.push_back(Book(id, title, author));

    cout << "\nBook added successfully!\n";
}


// Add Member
void addMember()
{
    int id;
    string name;

    cout << "\nEnter Member ID: ";
    cin >> id;

    if (findMember(id) != nullptr)
    {
        cout << "Member ID already exists.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, name);

    members.push_back(Member(id, name));

    cout << "\nMember added successfully!\n";
}


// Issue Book
void issueBook()
{
    int bookId;
    int memberId;

    cout << "\nEnter Book ID: ";
    cin >> bookId;

    Book* book = findBook(bookId);

    if (book == nullptr)
    {
        cout << "Book not found.\n";
        return;
    }

    if (!book->isAvailable())
    {
        cout << "Book is already issued.\n";
        return;
    }

    cout << "Enter Member ID: ";
    cin >> memberId;

    Member* member = findMember(memberId);

    if (member == nullptr)
    {
        cout << "Member not found.\n";
        return;
    }

    book->setAvailable(false);

    loans.push_back(Loan(bookId, memberId));

    cout << "\nBook issued successfully!\n";
    cout << "Book: " << book->getTitle() << endl;
    cout << "Member: " << member->getName() << endl;
}


// Return Book
void returnBook()
{
    int bookId;

    cout << "\nEnter Book ID to return: ";
    cin >> bookId;

    Book* book = findBook(bookId);

    if (book == nullptr)
    {
        cout << "Book not found.\n";
        return;
    }

    if (book->isAvailable())
    {
        cout << "This book is already available.\n";
        return;
    }

    book->setAvailable(true);

    loans.erase(
        remove_if(
            loans.begin(),
            loans.end(),
            [bookId](const Loan& loan)
            {
                return loan.getBookId() == bookId;
            }
        ),
        loans.end()
    );

    cout << "\nBook returned successfully!\n";
}


// Search Book
void searchBook()
{
    int choice;

    cout << "\n===== SEARCH BOOK =====\n";
    cout << "1. Search by Book ID\n";
    cout << "2. Search by Title\n";
    cout << "Enter choice: ";

    cin >> choice;

    if (choice == 1)
    {
        int id;

        cout << "Enter Book ID: ";
        cin >> id;

        Book* book = findBook(id);

        if (book != nullptr)
        {
            book->display();
        }
        else
        {
            cout << "Book not found.\n";
        }
    }
    else if (choice == 2)
    {
        string keyword;

        cin.ignore();

        cout << "Enter title keyword: ";
        getline(cin, keyword);

        bool found = false;

        for (const auto& book : books)
        {
            if (book.getTitle().find(keyword) != string::npos)
            {
                book.display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No matching books found.\n";
        }
    }
    else
    {
        cout << "Invalid search option.\n";
    }
}


// Display Available Books
void displayAvailableBooks()
{
    cout << "\n===== AVAILABLE BOOKS =====\n";

    bool found = false;

    for (const auto& book : books)
    {
        if (book.isAvailable())
        {
            book.display();
            found = true;
        }
    }

    if (!found)
    {
        cout << "No books are currently available.\n";
    }
}


// Display Members
void displayMembers()
{
    cout << "\n===== MEMBERS =====\n";

    if (members.empty())
    {
        cout << "No members found.\n";
        return;
    }

    for (const auto& member : members)
    {
        member.display();
    }
}


// Display Issued Books
void displayIssuedBooks()
{
    cout << "\n===== ISSUED BOOKS =====\n";

    if (loans.empty())
    {
        cout << "No books are currently issued.\n";
        return;
    }

    for (const auto& loan : loans)
    {
        Book* book = findBook(loan.getBookId());
        Member* member = findMember(loan.getMemberId());

        if (book != nullptr && member != nullptr)
        {
            cout << "Book ID: " << book->getBookId() << endl;
            cout << "Book: " << book->getTitle() << endl;

            cout << "Member ID: "
                 << member->getMemberId() << endl;

            cout << "Member: "
                 << member->getName() << endl;

            cout << "-----------------------------\n";
        }
    }
}


// Save Data
void saveData()
{
    ofstream file(DATA_FILE);

    if (!file)
    {
        cout << "Error: Unable to save data.\n";
        return;
    }

    file << "[BOOKS]\n";

    for (const auto& book : books)
    {
        file << book.toFileString() << "\n";
    }

    file << "[MEMBERS]\n";

    for (const auto& member : members)
    {
        file << member.toFileString() << "\n";
    }

    file << "[LOANS]\n";

    for (const auto& loan : loans)
    {
        file << loan.toFileString() << "\n";
    }

    file.close();
}


// Load Data
void loadData()
{
    ifstream file(DATA_FILE);

    if (!file)
    {
        cout << "No previous data found.\n";
        cout << "Starting a new library.\n";
        return;
    }

    string line;
    string section;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (line == "[BOOKS]")
        {
            section = "BOOKS";
            continue;
        }

        if (line == "[MEMBERS]")
        {
            section = "MEMBERS";
            continue;
        }

        if (line == "[LOANS]")
        {
            section = "LOANS";
            continue;
        }

        stringstream ss(line);
        string value;

        if (section == "BOOKS")
        {
            vector<string> data;

            while (getline(ss, value, '|'))
            {
                data.push_back(value);
            }

            if (data.size() == 4)
            {
                int id = stoi(data[0]);
                string title = data[1];
                string author = data[2];
                bool available = (data[3] == "1");

                books.push_back(
                    Book(id, title, author, available)
                );
            }
        }
        else if (section == "MEMBERS")
        {
            vector<string> data;

            while (getline(ss, value, '|'))
            {
                data.push_back(value);
            }

            if (data.size() == 2)
            {
                int id = stoi(data[0]);
                string name = data[1];

                members.push_back(
                    Member(id, name)
                );
            }
        }
        else if (section == "LOANS")
        {
            vector<string> data;

            while (getline(ss, value, '|'))
            {
                data.push_back(value);
            }

            if (data.size() == 2)
            {
                int bookId = stoi(data[0]);
                int memberId = stoi(data[1]);

                loans.push_back(
                    Loan(bookId, memberId)
                );
            }
        }
    }

    file.close();

    cout << "Previous library data loaded successfully.\n";
}
