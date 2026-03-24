# Library Management System

A simple, console-based library management system in C++.

## Overview

This program allows:

- **Students** to browse, borrow, and return books
- **Admins** to manage books and view students

## Login

- **Admin**: Enter `999`
- **Student**: Enter your student ID
- **Exit**: Enter `0`

## Features

### Admin Menu

| Option | Action                                  |
| ------ | --------------------------------------- |
| 1      | View all books (shows who borrowed)     |
| 2      | Add a new book                          |
| 3      | View all students (with borrowed books) |
| 0      | Back to main menu                       |

### Student Menu

| Option | Action                 |
| ------ | ---------------------- |
| 1      | Browse available books |
| 2      | Borrow a book          |
| 3      | Return a book          |
| 0      | Back to main menu      |

## Data Storage

Data is stored in text files and persists between sessions:

- `users.txt` - Student records (format: `id|name`)
- `books.txt` - Book records (format: `id|title|author|borrowed_by`)

The `borrowed_by` field stores the student ID who borrowed the book, or `0` if available.

## Code Structure

```
main.cpp
├── Constants
│   └── ADMIN_ID (999)
│
├── Data Structures
│   ├── Student (id, name)
│   └── Book (id, title, author, borrowed_by)
│
├── Global Data
│   ├── students vector
│   └── books vector
│
├── File I/O
│   ├── save()     - Write data to files
│   └── load()     - Read data from files
│
├── Helper Functions
│   ├── next_book_id()    - Generate next book ID
│   ├── find_student()    - Find student by ID
│   ├── find_book()       - Find book by ID
│   └── get_int_input()   - Safe integer input
│
├── Display Functions
│   ├── display_borrowed_books()  - Show student's books
│   ├── display_all_books()       - Show all books with status
│   ├── display_all_students()    - Show all students
│   └── display_available_books() - Show only available books
│
├── Admin Functions
│   ├── add_book()      - Add new book
│   └── admin_menu()    - Admin menu loop
│
├── Student Functions
│   ├── issue_book()    - Borrow a book
│   ├── return_book()   - Return a book
│   └── student_menu()  - Student menu loop
│
└── Main
    └── main() - Program entry point
```

## Changes from Original

| Feature                         | Original         | Current                              |
| ------------------------------- | ---------------- | ------------------------------------ |
| Password login                  | Yes              | No (ID only)                         |
| Balance system                  | Yes              | No                                   |
| ISBN                            | Yes              | No (replaced with auto-generated ID) |
| Data storage                    | Arrays in memory | Text files (persistent)               |
| Book ID                         | N/A              | Auto-generated                       |
| Multiple borrows                | No               | Yes                                  |
| Borrowing persistence           | No               | Yes                                  |
| Student can view borrowed books | No               | Yes                                  |
| Admin can view borrower         | No               | Yes                                  |
| Search books                    | Yes              | No (removed to simplify)             |
| Edit book                       | Yes              | No (removed to simplify)             |
| Code size                       | ~500 lines       | ~250 lines                           |

## Sample Data

### Default Books

1. The Great Gatsby - F. Scott Fitzgerald
2. To Kill a Mockingbird - Harper Lee
3. 1984 - George Orwell
4. Pride and Prejudice - Jane Austen
5. The Catcher in the Rye - J.D. Salinger
   ... (15 total)

### Sample Students

- 20251 - John Smith
- 20255 - Jane Doe
- 20234 - Alice Johnson
