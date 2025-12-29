#include <filesystem>
#include "StudentDataBase.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

StudentDatabase::StudentDatabase(std::string storagePath)
    : path_(std::move(storagePath)) {}

int StudentDatabase::indexOfId(const std::string& id) const {
    for (int i = 0; i < static_cast<int>(students_.size()); ++i) {
        if (students_[i].id == id) return i;
    }
    return -1;
}

bool StudentDatabase::addStudent(const Student& s) {
    if (indexOfId(s.id) != -1) return false;
    students_.push_back(s);
    return true;
}

bool StudentDatabase::updateStudentById(const std::string& id, const Student& updated) {
    int idx = indexOfId(id);
    if (idx == -1) return false;
    students_[idx] = updated;
    return true;
}

bool StudentDatabase::deleteStudentById(const std::string& id) {
    int idx = indexOfId(id);
    if (idx == -1) return false;
    students_.erase(students_.begin() + idx);
    return true;
}

const Student* StudentDatabase::findById(const std::string& id) const {
    int idx = indexOfId(id);
    if (idx == -1) return nullptr;
    return &students_[idx];
}

std::vector<const Student*> StudentDatabase::searchByLastName(const std::string& last) const {
    std::vector<const Student*> results;
    for (const auto& s : students_) {
        if (s.lastName == last) results.push_back(&s);
    }
    return results;
}

const std::vector<Student>& StudentDatabase::all() const {
    return students_;
}

// Basic CSV escaping: wrap in quotes, double internal quotes.
std::string StudentDatabase::escape(const std::string& s) {
    std::string out = "\"";
    for (char c : s) {
        if (c == '"') out += "\"\"";
        else out += c;
    }
    out += "\"";
    return out;
}

std::string StudentDatabase::unescape(const std::string& s) {
    // expects quoted field "..."
    if (s.size() < 2 || s.front() != '"' || s.back() != '"') return s;
    std::string inner = s.substr(1, s.size() - 2);
    std::string out;
    for (size_t i = 0; i < inner.size(); ++i) {
        if (inner[i] == '"' && i + 1 < inner.size() && inner[i + 1] == '"') {
            out += '"';
            ++i;
        } else {
            out += inner[i];
        }
    }
    return out;
}

bool StudentDatabase::load() {
    namespace fs = std::filesystem;
    fs::create_directories(fs::path(path_).parent_path());

    students_.clear();

    std::ifstream in(path_);
    if (!in.is_open()) {
        // Not an error if file doesn't exist yet; we’ll create it on save.
        return true;
    }

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::vector<std::string> fields;
        fields.reserve(6);

        // Parse CSV line with quoted fields
        std::string token;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '"' ) {
                token += c;
                // toggle unless it's an escaped quote ""
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    token += '"';
                    ++i;
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (c == ',' && !inQuotes) {
                fields.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        fields.push_back(token);

        if (fields.size() < 6) continue;

        Student s;
        s.id        = unescape(fields[0]);
        s.firstName = unescape(fields[1]);
        s.lastName  = unescape(fields[2]);
        s.major     = unescape(fields[3]);

        try {
            s.year = std::stoi(fields[4]);
            s.gpa  = std::stod(fields[5]);
        } catch (...) {
            continue; // skip bad row
        }

        // Courses are after 6th column, separated by '|'
        if (fields.size() >= 7) {
            std::string courseBlob = unescape(fields[6]);
            std::stringstream ss(courseBlob);
            std::string course;
            while (std::getline(ss, course, '|')) {
                if (!course.empty()) s.courses.push_back(course);
            }
        }

        // Only keep students with a valid ID
        if (!s.id.empty()) students_.push_back(s);
    }

    return true;
}

bool StudentDatabase::save() const {
    namespace fs = std::filesystem;
    fs::create_directories(fs::path(path_).parent_path());

    std::ofstream out(path_);
    if (!out.is_open()) return false;

    out << "id,firstName,lastName,major,year,gpa,courses\n";
    for (const auto& s : students_) {
        std::string courseBlob;
        for (size_t i = 0; i < s.courses.size(); ++i) {
            courseBlob += s.courses[i];
            if (i + 1 < s.courses.size()) courseBlob += "|";
        }

        out
            << escape(s.id) << ","
            << escape(s.firstName) << ","
            << escape(s.lastName) << ","
            << escape(s.major) << ","
            << s.year << ","
            << s.gpa << ","
            << escape(courseBlob)
            << "\n";
    }
    return true;
}