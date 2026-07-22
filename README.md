# Student Record System

A C++17 command-line application for creating, reading, updating, deleting, searching, saving, and loading student records.

The project demonstrates structured data management, input validation, Standard Template Library containers, CSV persistence, and filesystem operations.

## Features

- Add student records
- Update records by student ID
- Delete records by student ID
- Find a student by ID
- Search students by exact last name
- List all stored students
- Save records to CSV
- Load records from CSV
- Automatically create the storage directory
- Validate student IDs, academic year, GPA, and course counts during interactive entry

## Student Data

Each student record stores:

- Student ID
- First name
- Last name
- Major
- Academic year
- GPA
- Course list

## Search Implementation

Student records are stored in a `std::vector`.

ID and last-name searches use linear traversal, giving them O(n) time complexity in the number of stored students.

This implementation is appropriate for a small educational application. A future version could add an `std::unordered_map` index for average O(1) ID lookup.

## CSV Persistence

The application stores records in:

```text
data/students.csv
```

String fields are written as quoted CSV fields. Embedded double quotes are escaped by doubling them.

Course names are stored in one quoted field and separated internally with the `|` character.

Rows with missing fields or invalid numeric values are skipped while loading.

## Technologies

- C++17
- Standard Template Library
- `std::vector`
- `std::filesystem`
- File streams
- String streams
- CMake

## Project Structure

```text
student-record-system/
├── src/
│   ├── main.cpp
│   ├── Student.h
│   ├── Student.cpp
│   ├── StudentDataBase.h
│   ├── StudentDataBase.cpp
│   └── Input.h
├── data/
│   └── .gitkeep
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build

Requirements:

- CMake 3.20 or newer
- A C++17-compatible compiler

```bash
cmake -S . -B build
cmake --build build
```

## Run

Run the executable from the repository root so the relative `data/` path is created in the expected location.

```bash
./build/student_record_system
```
