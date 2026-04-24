# 📚 C++ Virtual Library Management System

![C++](https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Terminal](https://img.shields.io/badge/Terminal-4D4D4D?style=for-the-badge&logo=windows-terminal&logoColor=white)
![OOP](https://img.shields.io/badge/Architecture-OOP-00C853?style=for-the-badge)

A robust, console-based Library Management application built from scratch using Object-Oriented C++. This system features a dual-role authentication system (Librarian and Customer), complete inventory management, and time-tracked book borrowing.

To demonstrate a deep understanding of core C++ mechanics, this project intentionally avoids standard library containers like `std::vector`, relying entirely on **dynamic memory allocation, raw arrays, and pointers** to manage data structures.

---


## ✨ Key Features

### 🔐 Dual-Role System
* **Librarian (Admin):** Full access to add/remove books, manage the customer database, and oversee all borrowed/available inventory.
* **Customer:** Secure login to browse books, search by keyword, and borrow up to 5 books at a time.

### ⚙️ Core Mechanics
* **Dynamic Memory Management:** Custom generic template functions (`resizeArray`) handle the dynamic growth of arrays on the heap without memory leaks.
* **Smart Borrowing Logic:** Tracks exact borrow dates and automatically calculates a 7-day due date using the `<ctime>` library. 
* **Custom Search Algorithm:** Implements a manual substring matching algorithm (`isSubstr`) for case-insensitive searching by Title, Author, or Category.
* **Data Persistence:** Architecture includes save/load states to write library inventory and customer credentials to `.dat` files upon exiting.
* **Strict Input Validation:** Custom error-handling loops prevent the program from crashing if a user inputs strings instead of integers.

## 🛠️ Built With

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (Classes, Inheritance, Polymorphism)
* **Environment:** CLI / Terminal

---
