#ifndef STUDENT_RECORD_SYSTEM_STUDENT_H
#define STUDENT_RECORD_SYSTEM_STUDENT_H

#pragma once
#include <string>
#include <vector>

struct Student {
    std::string id;                 // unique (ex: "100123")
    std::string firstName;
    std::string lastName;
    std::string major;
    int year = 1;                   // 1..5
    double gpa = 0.0;               // 0.0..4.0
    std::vector<std::string> courses;

    std::string fullName() const;
};

#endif //STUDENT_RECORD_SYSTEM_STUDENT_H