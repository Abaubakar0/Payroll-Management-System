# Payroll Management System
## Project Description :
The Payroll Management System is a Command-Line Interface (CLI) application built in C++ that simplifies the tracking and management of employee records. It supports both full-time and part-time employees, allowing users to calculate salaries, compute annual taxes, and determine allowances based on the employee's employment type.

The system features persistent data storage, meaning all employee records are automatically saved to text files and loaded the next time the program runs. It also includes robust input validation to ensure data integrity.

## Key Features
Manage Different Employee Types: Add and distinguish between Full-Time (base salary + allowance) and Part-Time (hourly rate × hours worked) employees.

Automatic Calculations: Dynamically calculates total salary, annual tax deductions (10% for full-time), and annual allowances.

Data Persistence: Automatically saves employee data to fulltime.txt and parttime.txt and retrieves it upon startup.

Search and Delete: Retrieve specific tax/allowance details or delete an employee's record using their unique ID or Name.

Input Validation: Prevents duplicate IDs, negative salaries, and invalid age inputs (restricted to 18-65).

## Programming Language & Technologies
Language: C++

Concepts Used: Object-Oriented Programming (Inheritance, Polymorphism), File Handling (I/O Streams), and the Standard Template Library (Vectors).

Tools: Standard standard libraries (<iostream>, <fstream>, <vector>, <iomanip>). No external dependencies required
## Output Png : https://github.com/Abaubakar0/Payroll-Management-System/blob/main/image_2026-04-08_183501925.png
