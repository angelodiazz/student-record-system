cmake_minimum_required(VERSION 3.20)
project(StudentRecordSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(student_record_system
        src/main.cpp
        src/Student.cpp
        src/StudentDataBase.cpp
)
