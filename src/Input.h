#ifndef STUDENT_RECORD_SYSTEM_INPUT_H
#define STUDENT_RECORD_SYSTEM_INPUT_H

#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

inline void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline std::string readLine(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, s);
        if (!s.empty()) return s;
        std::cout << "Error: input cannot be empty. Try again.\n";
    }
}

inline int readIntInRange(const std::string& prompt, int lo, int hi) {
    int x{};
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> x)) {
            std::cout << "Error: enter a whole number.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();
        if (x < lo || x > hi) {
            std::cout << "Error: enter a value between " << lo << " and " << hi << ".\n";
            continue;
        }
        return x;
    }
}

inline double readDoubleInRange(const std::string& prompt, double lo, double hi) {
    double x{};
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> x)) {
            std::cout << "Error: enter a number.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();
        if (x < lo || x > hi) {
            std::cout << "Error: enter a value between " << lo << " and " << hi << ".\n";
            continue;
        }
        return x;
    }
}

inline bool isDigitsOnly(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) if (!std::isdigit(ch)) return false;
    return true;
}

#endif //STUDENT_RECORD_SYSTEM_INPUT_H