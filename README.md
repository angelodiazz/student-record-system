# Student Record System (C++)

A command-line student record management system built in C++ that allows users to store, manage, and retrieve student information using object-oriented programming and file-based persistence.

## Features
- Add new student records
- Update existing student information
- Delete students by ID
- Search students by ID or last name
- List all stored students
- Persistent storage using CSV files
- Input validation to prevent invalid data

## Technologies Used
- C++
- Object-Oriented Programming (OOP)
- File I/O (CSV)
- CMake
- CLion

## Project Structure
src/        # Source code files  
data/       # Runtime data directory (ignored by Git)  
CMakeLists.txt  
.gitignore  

## Build & Run
mkdir build  
cd build  
cmake ..  
cmake --build .  
./student_record_system  

## Notes
- Student records are saved locally using CSV files.
- Runtime data is excluded from version control using `.gitignore`.
