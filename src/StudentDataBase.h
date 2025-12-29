#ifndef STUDENT_RECORD_SYSTEM_STUDENTDATABASE_H
#define STUDENT_RECORD_SYSTEM_STUDENTDATABASE_H

#pragma once
#include "Student.h"
#include <string>
#include <vector>
#include <optional>

class StudentDatabase {
public:
    explicit StudentDatabase(std::string storagePath);

    bool load();            // load from CSV
    bool save() const;      // save to CSV

    bool addStudent(const Student& s);                 // false if ID exists
    bool updateStudentById(const std::string& id, const Student& updated); // false if not found
    bool deleteStudentById(const std::string& id);     // false if not found

    const Student* findById(const std::string& id) const;
    std::vector<const Student*> searchByLastName(const std::string& last) const;

    const std::vector<Student>& all() const;

private:
    std::string path_;
    std::vector<Student> students_;

    int indexOfId(const std::string& id) const;

    // CSV helpers
    static std::string escape(const std::string& s);
    static std::string unescape(const std::string& s);
};

#endif //STUDENT_RECORD_SYSTEM_STUDENTDATABASE_H