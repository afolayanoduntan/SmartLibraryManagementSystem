Smart Library Management System (SLMS)

This is a Smart Library Management System programmed using c++ whichs enable the users to borrow, return and reserve books and the management of book catalog by administrators

Overview

This system is created as a component of the Object Oriented Programming course, which is a module of the COM5012. It replicates the real world library management system where students have the ability to control book borrowings, and administrators are able to control the library catalog.

Features

Member (Student) Features:

Access with student email address(@bucks.ac.uk) with safe access.

Search through the library catalog of books.

Search books by their titles(not case sensitive).

Borrow books

Return borrowed books

Reserved books which are either in use or borrowed.

Borrowed books and access personal information.

Admin Features:

Special privileged admin log in.

View all books

Addition of new books (ISBN generated automatically)

Remove books from catalog

Update book information

View all registered members

View overdue books

Class Relationships:

User (Base class)- basic user attributes.

Member (Derived from User)- Represents library members/students.

Admin ( Derived off User ) - is used by library administrators.

Book - Is a symbol of books in the library.

Library - Deals with book collections and customers.

OOP Concepts Demonstrated

Inheritance

User is an abstract base class, and Member and Admin classes derive out of it.

Class children have common attributes (name, email, password) and introduce specific ones.

Encapsulation

Privacy and public getters/setters.

Data hiding (status of the book, passwords, etc.).

Member class borrowedBooks array is privated.


Polymorphism

User class Virtual functions overridden by Member and Admin.

The displayMenu is different depending on the user role.

Display role-specific information is shown using displayInfo ()


Set Up

In order to implement this project with Visual Studio, you must have installed the following:

Visual Studio (including Desktop development using C++).

Cmake(lastest version).

A compiler (Using C++ - Visual Studio is included with a C++ compiler).

Default System Credentials

Admin

Email: admin@bucks.ac.uk

Password: admin123

Librarian

Email: librarian@bucks.ac.uk

Password: lib123

Member

Email: 11112222@bucks.ac.uk

Password: password