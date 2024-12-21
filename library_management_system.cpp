#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <limits>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

struct Borrower {
    string name;
    string borrowerID;

    Borrower(string n, string id) : name(n), borrowerID(id) {}
};

struct Transaction {
    string borrowerID;
    string ISBN;
    time_t checkoutDate;
    time_t returnDate;

    Transaction(string bID, string isbn) : borrowerID(bID), ISBN(isbn), returnDate(0) {
        checkoutDate = time(0);
    }
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;
    unordered_map<string, int> bookIndex; // Map ISBN to index in books vector
    unordered_map<string, int> borrowerIndex; // Map borrowerID to index in borrowers vector

public:
    void addBook(const Book& book) {
        books.push_back(book);
        bookIndex[book.ISBN] = books.size() - 1;
    }

    void addBorrower(const Borrower& borrower) {
        borrowers.push_back(borrower);
        borrowerIndex[borrower.borrowerID] = borrowers.size() - 1;
    }

    void displayAllBooks() {
        cout << "\nAll Books in the Library:" << endl;
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
        }
    }

    void displayAllBorrowers() {
        cout << "\nAll Borrowers:" << endl;
        for (const auto& borrower : borrowers) {
            cout << "Name: " << borrower.name << ", Borrower ID: " << borrower.borrowerID << endl;
        }
    }

    void displayTransactionHistory() {
        cout << "\nTransaction History:" << endl;
        for (const auto& transaction : transactions) {
            cout << "Borrower ID: " << transaction.borrowerID << ", ISBN: " << transaction.ISBN 
                 << ", Checkout Date: " << ctime(&transaction.checkoutDate) 
                 << ", Return Date: " << (transaction.returnDate == 0 ? "Not Returned" : ctime(&transaction.returnDate)) << endl;
        }
    }

    void searchBook(const string& query) {
        cout << "\nSearch Results:" << endl;
        for (const auto& book : books) {
            if (book.title == query || book.author == query || book.ISBN == query) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            }
        }
    }

    void checkoutBook(const string& borrowerID, const string& ISBN) {
        if (bookIndex.find(ISBN) != bookIndex.end() && borrowerIndex.find(borrowerID) != borrowerIndex.end()) {
            int bookIdx = bookIndex[ISBN];
            if (books[bookIdx].isAvailable) {
                books[bookIdx].isAvailable = false;
                transactions.push_back(Transaction(borrowerID, ISBN));
                cout << "Book checked out successfully." << endl;
            } else {
                cout << "Book is not available." << endl;
            }
        } else {
            cout << "Invalid borrower ID or ISBN." << endl;
        }
    }

    void returnBook(const string& borrowerID, const string& ISBN) {
        if (bookIndex.find(ISBN) != bookIndex.end() && borrowerIndex.find(borrowerID) != borrowerIndex.end()) {
            int bookIdx = bookIndex[ISBN];
            books[bookIdx].isAvailable = true;
            for (auto& transaction : transactions) {
                if (transaction.borrowerID == borrowerID && transaction.ISBN == ISBN && transaction.returnDate == 0) {
                    transaction.returnDate = time(0);
                    double fine = calculateFine(transaction.checkoutDate, transaction.returnDate);
                    cout << "Book returned successfully. Fine: $" << fixed << setprecision(2) << fine << endl;
                    return;
                }
            }
            cout << "No matching transaction found." << endl;
        } else {
            cout << "Invalid borrower ID or ISBN." << endl;
        }
    }

    double calculateFine(time_t checkoutDate, time_t returnDate) {
        const double finePerDay = 0.5;
        double daysOverdue = difftime(returnDate, checkoutDate) / (60 * 60 * 24) - 14; // Assuming 2-week loan period
        return daysOverdue > 0 ? daysOverdue * finePerDay : 0;
    }

    void clearScreen() {
        cout << string(100, '\n'); // Simple way to clear the console screen
    }

    void waitForKeyPress() {
        cout << "\nPress any key to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void mainMenu() {
        while (true) {
            clearScreen();
            cout << "Library Management System" << endl;
            cout << "1. Display All Books" << endl;
            cout << "2. Display All Borrowers" << endl;
            cout << "3. Display Transaction History" << endl;
            cout << "4. Search Book" << endl;
            cout << "5. Checkout Book" << endl;
            cout << "6. Return Book" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                clearScreen();
                displayAllBooks();
                waitForKeyPress();
            } else if (choice == 2) {
                clearScreen();
                displayAllBorrowers();
                waitForKeyPress();
            } else if (choice == 3) {
                clearScreen();
                displayTransactionHistory();
                waitForKeyPress();
            } else if (choice == 4) {
                clearScreen();
                cout << "Enter book title, author, or ISBN to search: ";
                string query;
                cin.ignore();
                getline(cin, query);
                searchBook(query);
                waitForKeyPress();
            } else if (choice == 5) {
                clearScreen();
                cout << "Enter borrower ID: ";
                string borrowerID;
                cin >> borrowerID;
                cout << "Enter book ISBN: ";
                string ISBN;
                cin >> ISBN;
                checkoutBook(borrowerID, ISBN);
                waitForKeyPress();
            } else if (choice == 6) {
                clearScreen();
                cout << "Enter borrower ID: ";
                string borrowerID;
                cin >> borrowerID;
                cout << "Enter book ISBN: ";
                string ISBN;
                cin >> ISBN;
                returnBook(borrowerID, ISBN);
                waitForKeyPress();
            } else if (choice == 7) {
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
                waitForKeyPress();
            }
        }
    }
};

int main() {
    Library library;

    // Adding some books and borrowers
    library.addBook(Book("Computer Science with Python", "Sumita Arora", "1234567890"));
    library.addBook(Book("Computer Concepts and Programming in C", "Balagurusamy", "2345678901"));
    library.addBook(Book("Programming with JAVA", "Balagurusamy", "3456789012"));
    library.addBorrower(Borrower("Raam", "A001"));
    library.addBorrower(Borrower("Shyam", "B002"));

    // Start the main menu
    library.mainMenu();

    return 0;
}

