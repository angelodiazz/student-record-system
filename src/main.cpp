#include "StudentDatabase.h"
#include "Input.h"
#include <iostream>
#include <iomanip>

static void printStudent(const Student& s) {
    std::cout << "----------------------------------\n";
    std::cout << "ID:      " << s.id << "\n";
    std::cout << "Name:    " << s.fullName() << "\n";
    std::cout << "Major:   " << s.major << "\n";
    std::cout << "Year:    " << s.year << "\n";
    std::cout << "GPA:     " << std::fixed << std::setprecision(2) << s.gpa << "\n";
    std::cout << "Courses: ";
    if (s.courses.empty()) std::cout << "(none)";
    for (size_t i = 0; i < s.courses.size(); ++i) {
        std::cout << s.courses[i];
        if (i + 1 < s.courses.size()) std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "----------------------------------\n";
}

static Student buildStudentFromUser(const std::string& forcedId = "") {
    Student s;

    if (!forcedId.empty()) {
        s.id = forcedId;
    } else {
        while (true) {
            s.id = readLine("Enter student ID (digits only): ");
            if (isDigitsOnly(s.id)) break;
            std::cout << "Error: ID must be digits only.\n";
        }
    }

    s.firstName = readLine("Enter first name: ");
    s.lastName  = readLine("Enter last name: ");
    s.major     = readLine("Enter major: ");
    s.year      = readIntInRange("Enter year (1-5): ", 1, 5);
    s.gpa       = readDoubleInRange("Enter GPA (0.0-4.0): ", 0.0, 4.0);

    int courseCount = readIntInRange("How many courses? (0-10): ", 0, 10);
    s.courses.clear();
    for (int i = 0; i < courseCount; ++i) {
        s.courses.push_back(readLine("  Course " + std::to_string(i + 1) + ": "));
    }

    return s;
}

static void listAll(const StudentDatabase& db) {
    const auto& v = db.all();
    if (v.empty()) {
        std::cout << "No students found.\n";
        return;
    }
    for (const auto& s : v) printStudent(s);
}

int main() {
    // Storage file path (relative).
    StudentDatabase db("data/students.csv");

    if (!db.load()) {
        std::cout << "Warning: could not load database.\n";
    }

    while (true) {
        std::cout << "\n===== Student Record System =====\n";
        std::cout << "1) Add student\n";
        std::cout << "2) Update student (by ID)\n";
        std::cout << "3) Delete student (by ID)\n";
        std::cout << "4) Find student (by ID)\n";
        std::cout << "5) Search students (by last name)\n";
        std::cout << "6) List all students\n";
        std::cout << "7) Save\n";
        std::cout << "0) Exit\n";

        int choice = readIntInRange("Choose an option: ", 0, 7);

        if (choice == 0) {
            // Auto-save on exit (best UX)
            if (!db.save()) {
                std::cout << "Warning: could not save database.\n";
            }
            std::cout << "Goodbye.\n";
            break;
        }

        if (choice == 1) {
            Student s = buildStudentFromUser();
            if (!db.addStudent(s)) {
                std::cout << "Error: a student with ID " << s.id << " already exists.\n";
            } else {
                std::cout << "Student added.\n";
            }
        }
        else if (choice == 2) {
            std::string id = readLine("Enter ID to update: ");
            const Student* found = db.findById(id);
            if (!found) {
                std::cout << "Not found.\n";
            } else {
                std::cout << "Current record:\n";
                printStudent(*found);
                std::cout << "Enter new values:\n";
                Student updated = buildStudentFromUser(id); // ID stays the same
                db.updateStudentById(id, updated);
                std::cout << "Student updated.\n";
            }
        }
        else if (choice == 3) {
            std::string id = readLine("Enter ID to delete: ");
            if (!db.deleteStudentById(id)) {
                std::cout << "Not found.\n";
            } else {
                std::cout << "Student deleted.\n";
            }
        }
        else if (choice == 4) {
            std::string id = readLine("Enter ID to find: ");
            const Student* s = db.findById(id);
            if (!s) std::cout << "Not found.\n";
            else printStudent(*s);
        }
        else if (choice == 5) {
            std::string last = readLine("Enter last name to search: ");
            auto results = db.searchByLastName(last);
            if (results.empty()) {
                std::cout << "No matches.\n";
            } else {
                std::cout << results.size() << " match(es):\n";
                for (const auto* s : results) printStudent(*s);
            }
        }
        else if (choice == 6) {
            listAll(db);
        }
        else if (choice == 7) {
            if (!db.save()) std::cout << "Error: save failed.\n";
            else std::cout << "Saved.\n";
        }
    }

    return 0;
}