# Student Record System (C++)

A C++ application for managing student academic records using validated user input and structured file handling. This project was built to demonstrate clean program organization, defensive input validation, and modular object-oriented design.

## Features
- Create and manage **student profiles** with unique identifiers
- Store, update, and retrieve **student academic records**
- **Input validation** to prevent duplicate or invalid entries
- **File-based persistence** to save and load student data
- Clear **separation of concerns** across data models, logic, and file I/O

## Design Overview
The program is structured into focused components:
- **Student data models** represent individual student records
- **Database logic** handles searching, adding, updating, and deleting students
- **File I/O utilities** manage persistent storage of records
- **User input handling** is centralized to ensure valid and consistent data entry

This design improves maintainability, accuracy, and extensibility.

## Project Structure
```text
student-record-system/
├── src/
│   ├── main.cpp
│   ├── Student.h
│   ├── Student.cpp
│   ├── StudentDatabase.h
│   ├── StudentDatabase.cpp
│   ├── FileManager.h
│   ├── FileManager.cpp
│   ├── Input.h
│   └── Input.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build & Run
This project uses **CMake** and **C++17**.

```bash
cmake -S . -B build
cmake --build build
