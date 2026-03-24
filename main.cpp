// ============================================
// LIBRARY MANAGEMENT SYSTEM
// A simple system for managing books and students
// ============================================

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// CONSTANTS

constexpr int ADMIN_ID = 999;

// DATA STRUCTURES

struct Student {
  int id;
  std::string name;
};

struct Book {
  int id;
  std::string title;
  std::string author;
  int borrowed_by = 0; // 0 means available
};

// GLOBAL DATA

std::vector<Student> students;
std::vector<Book> books;

// FILE I/O

void save() {
  // Save students (format: id|name)
  std::ofstream user_file("users.txt");
  for (auto &s : students) {
    user_file << s.id << "|" << s.name << "\n";
  }

  // Save books (format: id|title|author|borrowed_by)
  std::ofstream book_file("books.txt");
  for (auto &b : books) {
    book_file << b.id << "|" << b.title << "|" << b.author << "|" << b.borrowed_by << "\n";
  }
}

void load() {
  // Load students
  std::ifstream user_file("users.txt");
  std::string line;

  while (getline(user_file, line)) {
    if (line.empty())
      continue;

    int pipe_pos = line.find("|");
    if (pipe_pos == std::string::npos)
      continue;

    Student s;
    s.id = stoi(line.substr(0, pipe_pos));
    s.name = line.substr(pipe_pos + 1);
    students.push_back(s);
  }

  // Load books
  std::ifstream book_file("books.txt");

  while (getline(book_file, line)) {
    if (line.empty())
      continue;

    int first_pipe = line.find("|");
    int second_pipe = line.find("|", first_pipe + 1);
    int third_pipe = line.find("|", second_pipe + 1);

    if (first_pipe == std::string::npos || second_pipe == std::string::npos)
      continue;

    Book b;
    b.id = stoi(line.substr(0, first_pipe));
    b.title = line.substr(first_pipe + 1, second_pipe - first_pipe - 1);
    b.author = line.substr(second_pipe + 1, third_pipe - second_pipe - 1);
    
    // If borrowed_by field exists, parse it
    if (third_pipe != std::string::npos) {
      b.borrowed_by = stoi(line.substr(third_pipe + 1));
    } else {
      b.borrowed_by = 0; // Default to available
    }
    
    books.push_back(b);
  }
}

// HELPER FUNCTIONS

int next_book_id() {
  if (books.empty())
    return 1;
  return books.back().id + 1;
}

int find_student(int id) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i].id == id)
      return i;
  }
  return -1;
}

int find_book(int id) {
  for (int i = 0; i < books.size(); i++) {
    if (books[i].id == id)
      return i;
  }
  return -1;
}

int get_int_input() {
  int value;
  if (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return -1;
  }
  return value;
}

// DISPLAY FUNCTIONS

void display_borrowed_books(int student_id) {
  std::cout << "\nMy borrowed books:\n";

  bool has_borrowed = false;
  for (auto &b : books) {
    if (b.borrowed_by == student_id) {
      std::cout << "  [" << b.id << "] " << b.title << "\n";
      has_borrowed = true;
    }
  }

  if (!has_borrowed) {
    std::cout << "  None\n";
  }
}

void display_all_books() {
  std::cout << "\nBooks:\n";

  for (auto &b : books) {
    std::cout << "[" << b.id << "] " << b.title << " by " << b.author;

    if (b.borrowed_by == 0) {
      std::cout << " (available)\n";
    } else {
      int student_index = find_student(b.borrowed_by);
      if (student_index >= 0) {
        std::cout << " (borrowed by " << students[student_index].name << ")\n";
      } else {
        std::cout << " (borrowed)\n";
      }
    }
  }
}

void display_all_students() {
  std::cout << "\nStudents:\n";

  for (auto &s : students) {
    std::cout << s.id << " - " << s.name << "\n";

    for (auto &b : books) {
      if (b.borrowed_by == s.id) {
        std::cout << "  Borrowed: " << b.title << "\n";
      }
    }
  }
}

void display_available_books() {
  std::cout << "\nAvailable books:\n";

  for (auto &b : books) {
    if (b.borrowed_by == 0) {
      std::cout << "[" << b.id << "] " << b.title << " by " << b.author << "\n";
    }
  }
}

// ADMIN FUNCTIONS
void add_book() {
  Book new_book;
  new_book.id = next_book_id();

  std::cout << "Title: ";
  std::cin.ignore();
  getline(std::cin, new_book.title);

  std::cout << "Author: ";
  getline(std::cin, new_book.author);

  books.push_back(new_book);
  save();

  std::cout << "Book added!\n";
}

// UI for Admin
void admin_menu() {
  while (true) {
    std::cout << "\n--- Admin ---\n";
    std::cout << "1. Books  2. Add book  3. Students  0. Back\n";
    std::cout << "Choice: ";

    int choice = get_int_input();

    if (choice < 0) {
      std::cout << "Invalid input.\n";
      continue;
    }

    switch (choice) {
    case 0:
      return;

    case 1:
      display_all_books();
      break;

    case 2:
      add_book();
      break;

    case 3:
      display_all_students();
      break;

    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

// STUDENT FUNCTIONS

void issue_book(int student_id) {
  std::cout << "Book ID to issue: ";
  int book_id = get_int_input();

  if (book_id < 0) {
    std::cout << "Invalid ID.\n";
    return;
  }

  int book_index = find_book(book_id);

  if (book_index < 0 || books[book_index].borrowed_by != 0) {
    std::cout << "Not available.\n";
    return;
  }

  books[book_index].borrowed_by = student_id;
  save();
  std::cout << "Issued: " << books[book_index].title << "\n";
}

void return_book(int student_id) {
  std::cout << "Book ID to return: ";
  int book_id = get_int_input();

  if (book_id < 0) {
    std::cout << "Invalid ID.\n";
    return;
  }

  int book_index = find_book(book_id);

  if (book_index < 0 || books[book_index].borrowed_by != student_id) {
    std::cout << "You didn't borrow this book.\n";
    return;
  }

  books[book_index].borrowed_by = 0;
  save();
  std::cout << "Returned: " << books[book_index].title << "\n";
}

// UI for Student
void student_menu(int student_id) {
  while (true) {
    display_borrowed_books(student_id);

    std::cout << "\n--- Student Menu ---\n";
    std::cout << "1. Browse books  2. Issue  3. Return  0. Back\n";
    std::cout << "Choice: ";

    int choice = get_int_input();

    if (choice < 0) {
      std::cout << "Invalid input.\n";
      continue;
    }

    switch (choice) {
    case 0:
      return;

    case 1:
      display_available_books();
      break;

    case 2:
      issue_book(student_id);
      break;

    case 3:
      return_book(student_id);
      break;

    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

// MAIN
int main() {
  load();

  while (true) {
    std::cout << "\nLibrary System\n";
    std::cout << "ID (999=Admin, 0=Exit): ";

    int id = get_int_input();

    if (id < 0) {
      std::cout << "Please enter a valid number.\n";
      continue;
    }

    if (id == 0)
      break;

    if (id == ADMIN_ID) {
      admin_menu();
      continue;
    }

    int student_index = find_student(id);

    if (student_index < 0) {
      std::cout << "Not found. Register? (y/n): ";
      char confirm;
      std::cin >> confirm;
      std::cin.ignore();

      if (confirm == 'y' || confirm == 'Y') {
        Student new_student;
        new_student.id = id;

        std::cout << "Name: ";
        getline(std::cin, new_student.name);

        students.push_back(new_student);
        save();
        std::cout << "Registered!\n";
      }
    } else {
      student_menu(id);
    }
  }

  return 0;
}
