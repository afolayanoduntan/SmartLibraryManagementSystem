cmake_minimum_required(VERSION 3.20)
project(SmartLibraryManagementSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(SmartLibraryManagementSystem
        Admin.cpp
        Admin.h
        Book.cpp
        Book.h
        Librarian.cpp
        Librarian.h
        Library.cpp
        Library.h
        Member.cpp
        Member.h
        main.cpp
        User.cpp
        User.h)
