#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------- BOOK CLASS ----------
class Book {
public:
    int bookId;
    string title, author;
    bool issued;

    void input() {
        cout << "Enter Book ID: ";
        cin >> bookId;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        issued = false;
    }

    void display() {
        cout << "\nBook ID: " << bookId;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << endl;
    }
};

// ---------- MEMBER CLASS ----------
class Member {
public:
    int memberId;
    string name;

    void input() {
        cout << "Enter Member ID: ";
        cin >> memberId;
        cin.ignore();
        cout << "Enter Member Name: ";
        getline(cin, name);
    }

    void display() {
        cout << "\nMember ID: " << memberId;
        cout << "\nName: " << name << endl;
    }
};

// ---------- ADD BOOK ----------
void addBook() {
    Book b;
    ofstream file("books.txt", ios::app);
    b.input();
    file << b.bookId << "\n" << b.title << "\n" << b.author << "\n" << b.issued << "\n";
    file.close();
    cout << "Book added successfully!\n";
}

// ---------- DISPLAY BOOKS ----------
void displayBooks() {
    ifstream file("books.txt");
    Book b;

    while (file >> b.bookId) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();
        b.display();
    }
    file.close();
}

// ---------- SEARCH BOOK ----------
void searchBook() {
    ifstream file("books.txt");
    string search;
    bool found = false;

    cout << "Enter title or author: ";
    cin.ignore();
    getline(cin, search);

    Book b;
    while (file >> b.bookId) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if (b.title == search || b.author == search) {
            b.display();
            found = true;
        }
    }

    if (!found) cout << "Book not found!\n";
    file.close();
}

// ---------- ADD MEMBER ----------
void addMember() {
    Member m;
    ofstream file("members.txt", ios::app);
    m.input();
    file << m.memberId << "\n" << m.name << "\n";
    file.close();
    cout << "Member added successfully!\n";
}

// ---------- ISSUE BOOK ----------
void issueBook() {
    int bookId, memberId;
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "Enter Member ID: ";
    cin >> memberId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    Book b;
    bool found = false;

    while (file >> b.bookId) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if (b.bookId == bookId && !b.issued) {
            b.issued = true;
            found = true;

            ofstream record("records.txt", ios::app);
            record << bookId << " " << memberId << "\n";
            record.close();

            cout << "Book issued successfully!\n";
        }

        temp << b.bookId << "\n" << b.title << "\n" << b.author << "\n" << b.issued << "\n";
    }

    file.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found) cout << "Book not available!\n";
}

// ---------- RETURN BOOK ----------
void returnBook() {
    int bookId;
    cout << "Enter Book ID: ";
    cin >> bookId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    Book b;
    bool found = false;

    while (file >> b.bookId) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if (b.bookId == bookId && b.issued) {
            b.issued = false;
            found = true;
            cout << "Book returned successfully!\n";
        }

        temp << b.bookId << "\n" << b.title << "\n" << b.author << "\n" << b.issued << "\n";
    }

    file.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found) cout << "Invalid Book ID!\n";
}

// ---------- MAIN ----------
int main() {
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Add Member\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: addMember(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}