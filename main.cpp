#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//................................................

template <typename T>
T* resizeArray(T* oldArr, int& capacity) {
    int newCapacity = capacity + 1;
    T* newArr = new T[newCapacity];
    for (int i = 0; i < capacity; ++i)
        newArr[i] = oldArr[i];
    delete[] oldArr;
    capacity = newCapacity;
    return newArr;
}
int get_valid_integer(const int min, const int max) {
    int choice;
    while (true) {
        if (!(cin >> choice)) {
            cout << "Invalid number. Try again: ";
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');
        if (choice < min || choice > max) {
            cout << "Out of range. Try again: ";
            continue;
        }
        return choice;
    }
}
int len(const string &str) {
    int length = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        length++;
    }
    return length;
}
char toLowerChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 32;
    }
    return c;
}
string toLower(const string &s) {
    string result = s;
    for(int i = 0; i < len(result); ++i)
        result[i] = toLowerChar(result[i]);
    return result;
}
bool isSubstr(const string &str, const string &substr) {
    if (len(substr) > len(str))
        return false;

    for (int i = 0; i <= len(str) - len(substr); ++i) {
        bool match = true;

        for (int j = 0; j < len(substr); ++j) {
            if (str[i + j] != substr[j]) {
                match = false;
                break;
            }
        }

        if (match)
            return true;  // found it
    }

    return false;  // no match found anywhere
}
void save_and_exit() {
    cout << "Saving..." << endl
         << "Goodbye!" << endl;
    exit(0);
}

//................................................

class Book {
private:
    string title, author, category;
    bool isBorrowed;
    time_t borrowDate, dueDate;
public:
    Book() : title("unassigned"), author("unassigned"), category("unassigned"),
             isBorrowed(false), borrowDate(0), dueDate(0) {}

    Book(const string &t, const string &a, const string &c)
        : title(t), author(a), category(c),
          isBorrowed(false), borrowDate(0), dueDate(0) {}

    void setTitle(const string &t)   { title = t; }
    void setAuthor(const string &a)  { author = a; }
    void setCategory(const string &c){ category = c; }

    string getTitle()    const { return title; }
    string getAuthor()   const { return author; }
    string getCategory() const { return category; }
    bool   getIsBorrowed() const { return isBorrowed; }

    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            time(&borrowDate);
            dueDate = borrowDate + 7 * 24 * 60 * 60;
            cout << "Book '" << title << "' is successfully borrowed, Due to 7 days.\n";
        }
        else {
            cout << "Sorry, '" << title << "' is already borrowed.\n";
        }
    }
    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            borrowDate = dueDate = 0;
            cout << "Book '" << title << "' is successfully returned.\n";
        }
        else {
            cout << "HOW! '" << title << "' was not borrowed.\n";
        }
    }

    friend ostream& operator<<(ostream &os, const Book &b) {
        os << "| Title: " << b.title << "\n"
           << "| Author: " << b.author << "\n"
           << "| Category: " << b.category << "\n";
        if (b.isBorrowed) {
            os << "| Borrowed on: " << ctime(&b.borrowDate)
               << "| Due on:      " << ctime(&b.dueDate);
        }
        return os;
    }
};

//................................................

class Library {
private:
    Book* books_arr;
    int   bookCount;
    int   bookCapacity;

public:
    Library() : books_arr(new Book[1]), bookCount(0), bookCapacity(1) {}
    ~Library() {
        delete[] books_arr;
    }

    void addBook() {
        // A) Grow array if full
        if (bookCount == bookCapacity)
            books_arr = resizeArray(books_arr, bookCapacity);

        // B) Gather book details
        string title, author, category;
        cout << "Enter title: ";    cin.ignore(); getline(cin, title);
        cout << "Enter author: ";   getline(cin, author);
        cout << "Enter category: "; getline(cin, category);

        // C) Construct and append
        books_arr[bookCount++] = Book(title, author, category);
        cout << "Book added successfully.\n";
    }
    void removeBook() {
        // A) Count removable books
        int removableCount = 0;
        for (int i = 0; i < bookCount; ++i)
            if (!books_arr[i].getIsBorrowed())
                removableCount++;

        if (removableCount == 0) {
            cout << "No available books to remove.\n";
            return;
        }

        // B) List them with numbers
        cout << "\n--- Available Books for Removal ---\n";
        int displayIdx = 1;
        int mapIdx[removableCount];
        for (int i = 0; i < bookCount; ++i) {
            if (books_arr[i].getIsBorrowed()) continue;
            cout << "[" << displayIdx << "] "
                 << books_arr[i].getTitle()
                 << " by " << books_arr[i].getAuthor()
                 << " (" << books_arr[i].getCategory() << ")\n";
            mapIdx[displayIdx - 1] = i;
            displayIdx++;
        }

        // C) Choose and shift-delete
        cout << "Select [1-" << removableCount << "]: ";
        int choice = get_valid_integer(1, removableCount);
        int removeAt = mapIdx[choice - 1];
        for (int i = removeAt; i < bookCount - 1; ++i)
            books_arr[i] = books_arr[i + 1];
        --bookCount;

        cout << "Book removed successfully.\n";
    }
    void findBook() const {
        cout << "Search by:\n"
             << " 1. Title\n"
             << " 2. Author\n"
             << " 3. Category\n"
             << " 0. Back\n"
             << "Select [0-3]: ";
        int choice = get_valid_integer(0, 3);
        if (choice == 0) return;

        // A) Get a word to search for
        cout << "Enter keyword: ";
        cin.ignore(1000, '\n');
        string substr; getline(cin, substr);
        substr = toLower(substr);

        // B) Scan and match substrings
        bool found = false;
        cout << "\n--- Search Results ---\n";
        for (int i = 0; i < bookCount; ++i) {
            string str;
            if (choice == 1)      {str = books_arr[i].getTitle();}
            else if (choice == 2) {str = books_arr[i].getAuthor();}
            else str = books_arr[i].getCategory();

            // C) If the keyword appears anywhere, print the book
            if (isSubstr(toLower(str), substr)) {
                cout << books_arr[i] << "\n";
                found = true;
            }
        }
        if (!found)
            cout << "No matches found.\n";
    }
    void listAvailableBooks() const {
        cout << "--- Available Books ---\n";
        bool any = false;
        for (int i = 0; i < bookCount; ++i) {
            if (!books_arr[i].getIsBorrowed()) {
                cout << books_arr[i] << "\n";
                any = true;
            }
        }
        if (!any) cout << "No available books right now.\n";
    }
    void listBorrowedBooks() const {
        cout << "--- Borrowed Books ---\n";
        bool any = false;
        for (int i = 0; i < bookCount; ++i) {
            if (books_arr[i].getIsBorrowed()) {
                cout << books_arr[i] << "\n";
                any = true;
            }
        }
        if (!any) cout << "No books are currently borrowed.\n";
    }

    int selectAvailableBookIndex() const {
        // A) Build list and map
        int counter = 0;
        for (int i = 0; i < bookCount; ++i)
            if (!books_arr[i].getIsBorrowed()) counter++;
        if (counter == 0) {
            cout << "No available books.\n";
            return -1;
        }

        cout << "--- Select a Book ---\n";
        int displayIdx = 1;
        int mapIdx[counter];
        for (int i = 0; i < bookCount; ++i) {
            if (books_arr[i].getIsBorrowed()) continue;
            cout << "[" << displayIdx << "] "
                 << books_arr[i].getTitle()
                 << " by " << books_arr[i].getAuthor() << "\n";
            mapIdx[displayIdx - 1] = i;
            displayIdx++;
        }

        // B) Return choice
        cout << "Select [1-" << counter << "]: ";
        int choice = get_valid_integer(1, counter);
        return mapIdx[choice - 1];
    }
    Book& getBookAt(const int indx) const {
        // A) Validate index
        if (indx < 0 || indx >= bookCount) {
            cout << "Invalid book selection. Please try again.\n";
            save_and_exit();  // or: exit(1);
        }

        // B) Otherwise return the shared Book object
        return books_arr[indx];
    }

};


//................................................

class User {
private:
    string ID, username, password;
public:
    User() : ID("unassigned"), username("unassigned"), password("unassigned") {}
    User(const string &i, const string &u, const string &p)
        : ID(i), username(u), password(p) {}

    string getID() const       { return ID; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }

    bool authenticate(const string &i, const string &p) const {
        if (i == ID && p == password) {
            cout << "Welcome, " << username << "!\n";
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream &os, const User &u) {
        os << "| Username: " << u.username << "\n"
           << "| ID:       " << u.ID << "\n";
        return os;
    }
};

//................................................

class Customer : public User {
private:
    Book* borrowed_arr[5];
    int   borrowCount;
    Library* lib;

public:
    Customer() : borrowCount(0), lib(nullptr) {}
    Customer(const string &i, const string &u, const string &p, Library* library) : User(i, u, p), borrowCount(0), lib(library) {}

    void borrowBook() {
        // A) Enforce per‐customer limit
        if (borrowCount >= 5) {
            cout << "You can't borrow more than 5 books.\n";
            return;
        }
        // B) Ask Library to display & select an available book
        lib->listAvailableBooks();                  // prints titles where isBorrowed == false
        cout << "Select a book to borrow: ";
        int index = lib->selectAvailableBookIndex(); // returns the real index in Library::books_arr
        // C) Grab the Book object
        Book& b = lib->getBookAt(index);             // or via reference-return helper
        // D) Record it in Customer’s own list
        borrowed_arr[borrowCount++] = &b;            // store pointer to shared Book
        // E) Mark it borrowed
        b.borrowBook();                              // flips isBorrowed = true on the original object
    }
    void returnBook() {
        // A) Nothing to do if they’ve borrowed 0
        if (borrowCount == 0) {
            cout << "You have no borrowed books.\n";
            return;
        }
        // B) List their own borrowed titles
        cout << "--- Your Borrowed Books ---\n";
        for (int i = 0; i < borrowCount; ++i) {
            cout << "[" << (i+1) << "] "
                 << borrowed_arr[i]->getTitle() << "\n";
        }
        // C) Ask which one to return
        cout << "Select a book to return [1-" << borrowCount << "]: ";
        int choice = get_valid_integer(1, borrowCount);
        // D) Grab pointer, call Book::returnBook() on the shared object
        Book* b = borrowed_arr[choice - 1];
        b->returnBook();
        // E) Remove from their array and shift left
        for (int i = choice - 1; i < borrowCount - 1; ++i) {
            borrowed_arr[i] = borrowed_arr[i + 1];
        }
        borrowCount--;
    }
    void listMyBorrowed() const {
        if (borrowCount == 0) {
            cout << "You haven't borrowed any books.\n";
            return;
        }
        cout << "--- Your Borrowed Books ---\n";
        for (int i = 0; i < borrowCount; ++i)
            cout << *borrowed_arr[i] << "\n";
    }

    void CustomerView() {
        int choice;
        do {
            cout << "\n=== Welcome " << getUsername() << " ===\n"
                 << "1. Borrow a Book\n"
                 << "2. Return a Book\n"
                 << "3. Search for a Book\n"
                 << "4. List Available Books\n"
                 << "5. List My Borrowed Books\n"
                 << "0. LOGOUT\n"
                 << "Select [0-5]: ";
            choice = get_valid_integer(0, 5);

            switch (choice) {
                case 0: save_and_exit();            break;
                case 1: borrowBook();               break;
                case 2: returnBook();               break;
                case 3: lib->findBook();            break;
                case 4: lib->listAvailableBooks();  break;
                case 5: listMyBorrowed();           break;
                default: cout << "Invalid option, try again.\n";
            }
        } while (choice != 0);
    }
};


//................................................

class Librarian : public User {
private:
    Customer* customers_arr;
    int customerCount, customerCapacity;
    Library* lib;

public:
    Librarian(Library* library)
        : User("1", "Admin", "@"), lib(library)
    {
        customers_arr   = new Customer[1];
        customerCount   = 0;
        customerCapacity = 1;
    }
    ~Librarian() {
        delete[] customers_arr;
    }

    void addCustomer() {
        // 1) Grow array if needed
        if (customerCount == customerCapacity)
            customers_arr = resizeArray(customers_arr, customerCapacity);

        // 2) Read customer info
        string id, name, pass;
        cout << "Enter new ID: ";      cin.ignore(); getline(cin, id);
        cout << "Enter username: ";    getline(cin, name);
        cout << "Enter password: ";    getline(cin, pass);

        // 3) Construct with same Library pointer
        customers_arr[customerCount++] = Customer(id, name, pass, lib);
        cout << "Customer added successfully.\n";
    }
    void removeCustomer() {
        // 1) Nothing to do if none
        if (customerCount == 0) {
            cout << "No customers available to remove.\n";
            return;
        }

        // 2) List them
        cout << "--- Customers ---\n";
        for (int i = 0; i < customerCount; ++i) {
            cout << "[" << (i+1) << "] "
                 << customers_arr[i].getUsername()
                 << " (ID: " << customers_arr[i].getID() << ")\n";
        }

        // 3) Pick one
        cout << "Select customer to remove [1-" << customerCount << "]: ";
        int choice = get_valid_integer(1, customerCount);

        // 4) Shift array to delete
        for (int i = choice - 1; i < customerCount - 1; ++i)
            customers_arr[i] = customers_arr[i + 1];
        --customerCount;

        cout << "Customer removed successfully.\n";
    }
    void listCustomers() const {
        if (customerCount == 0) {
            cout << "No customers registered.\n";
            return;
        }
        cout << "--- Registered Customers ---\n";
        for (int i = 0; i < customerCount; ++i)
            cout << customers_arr[i] << "\n";
    }

    Customer* authenticateCustomer(const string& id, const string& p) const {
        for (int i = 0; i < customerCount; ++i) {
            if (customers_arr[i].getID() == id &&
                customers_arr[i].getPassword() == p)
            {
                return &customers_arr[i];
            }
        }
        return nullptr;
    }

    void librarianView() {
        int choice;
        do {
            cout << "\n=== Admin: " << getUsername() << " ===\n"
                 << "-- Book Management --\n"
                 << " 1. Add a Book\n"
                 << " 2. Remove a Book\n"
                 << " 3. List Available Books\n"
                 << " 4. List Borrowed Books\n"
                 << " 5. Search for a Book\n"
                 << "-- Customer Management --\n"
                 << " 6. Add a Customer\n"
                 << " 7. Remove a Customer\n"
                 << " 8. List Customers\n"
                 << " 0. Logout\n"
                 << "Select [0-8]: ";
            choice = get_valid_integer(0, 8);

            switch (choice) {
                case 0: break;
                case 1: lib->addBook();            break;
                case 2: lib->removeBook();         break;
                case 3: lib->listAvailableBooks(); break;
                case 4: lib->listBorrowedBooks();  break;
                case 5: lib->findBook();           break;
                case 6: addCustomer();             break;
                case 7: removeCustomer();          break;
                case 8: listCustomers();           break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 0);
    }
};

//................................................

void loadLibraryFromFile(Library& lib, const string& filename);
void saveLibraryToFile(const Library& lib, const string& filename);
void loadCustomersFromFile(Librarian& admin, const string& filename);
void saveCustomersToFile(const Librarian& admin, const string& filename);

int main() {
    Library mylibrary;
    loadLibraryFromFile(mylibrary, "books.dat");

    Librarian admin(&mylibrary);
    loadCustomersFromFile(admin, "customers.dat");

    cout << "+===========================================+\n"
         << "|    Welcome to the Virtual Library App     |\n"
         << "+===========================================+\n";

    while (true) {
        cout << "\n| 1. Login as Librarian\n"
             << "| 2. Login as Customer\n"
             << "| 0. Exit\n"
             << "Select [0-2]: ";
        int role = get_valid_integer(0, 2);
        if (role == 0) break;

        string id, pw;
        cout << "ID: ";        getline(cin, id);
        cout << "Password: ";  getline(cin, pw);

        if (role == 1) {
            if (admin.authenticate(id, pw)) {
                admin.librarianView();
            }
            else cout << "Incorrect librarian credentials. Try again.\n";
        }
        else {
            Customer* cust = admin.authenticateCustomer(id, pw);
            if (cust) cust->CustomerView();
            else cout << "Customer not found or wrong password. Contact admin.\n";
        }
    }

    saveLibraryToFile(mylibrary, "books.dat");
    saveCustomersToFile(admin,  "customers.dat");

    cout << "All changes saved. Goodbye!\n";
    return 0;
}