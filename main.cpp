#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Employee {
public:
    int id;
    string name;
    int age;

    void inputBasic() {
        cout << "Enter ID: ";
        while (!(cin >> id) || id < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a non-negative ID: ";
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Age (18 to 65): ";
        while (!(cin >> age) || age < 18 || age > 65) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter age between 18 and 65: ";
        }
    }

    void displayBasic() const {
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(6) << age;
    }
};

class FullTimeEmployee : public Employee {
public:
    float baseSalary;
    float allowance;

    void input();

    float getTotalSalary() const {
        return baseSalary + allowance;
    }

    float getTax() const {
        return baseSalary * 0.10f;
    }

    float getAnnualTax() const {
        return getTax() * 12;
    }

    float getAnnualAllowance() const {
        return allowance * 12;
    }

    void display() const {
        displayBasic();
        cout << fixed << setprecision(2)
             << setw(10) << baseSalary
             << setw(10) << allowance
             << setw(12) << getTotalSalary()
             << setw(8) << getTax() << endl;
    }

    string toString() const {
        string nameCopy = name;
        for (char& c : nameCopy) if (c == ' ') c = '_';
        return to_string(id) + " " + nameCopy + " " + to_string(age) + " " + to_string(baseSalary) + " " + to_string(allowance);
    }
};

class PartTimeEmployee : public Employee {
public:
    float hoursWorked;
    float hourlyRate;

    void input();

    float getTotalSalary() const {
        return hoursWorked * hourlyRate;
    }

    float getAnnualTax() const {
        return 0.0f;
    }

    float getAnnualAllowance() const {
        return 0.0f;
    }

    void display() const {
        displayBasic();
        cout << fixed << setprecision(2)
             << setw(10) << hoursWorked
             << setw(10) << hourlyRate
             << setw(12) << getTotalSalary()
             << setw(8) << "N/A" << endl;
    }

    string toString() const {
        string nameCopy = name;
        for (char& c : nameCopy) if (c == '_') c = ' ';
        return to_string(id) + " " + nameCopy + " " + to_string(age) + " " + to_string(hoursWorked) + " " + to_string(hourlyRate);
    }
};

vector<FullTimeEmployee> fullTimeList;
vector<PartTimeEmployee> partTimeList;

void FullTimeEmployee::input() {
    while (true) {
        inputBasic();

        bool idExists = false;
        for (int i = 0; i < fullTimeList.size(); i++) {
            if (fullTimeList[i].id == id) {
                cout << "This ID already exists. Enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
        for (int i = 0; i < partTimeList.size(); i++) {
            if (partTimeList[i].id == id) {
                cout << "This ID already exists. Enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
        if (!idExists) break;
    }

    cout << "Enter Base Salary (> 0): ";
    while (!(cin >> baseSalary) || baseSalary <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter Base Salary greater than 0: ";
    }

    cout << "Enter Allowance (> 0): ";
    while (!(cin >> allowance) || allowance <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter Allowance greater than 0: ";
    }
}

void PartTimeEmployee::input() {
    while (true) {
        inputBasic();

        bool idExists = false;
        for (int i = 0; i < fullTimeList.size(); i++) {
            if (fullTimeList[i].id == id) {
                cout << "This ID already exists. Enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
        for (int i = 0; i < partTimeList.size(); i++) {
            if (partTimeList[i].id == id) {
                cout << "This ID already exists. Enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
        if (!idExists) break;
    }

    cout << "Enter Hours Worked (> 0): ";
    while (!(cin >> hoursWorked) || hoursWorked <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter Hours Worked greater than 0: ";
    }

    cout << "Enter Hourly Rate (> 0): ";
    while (!(cin >> hourlyRate) || hourlyRate <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter Hourly Rate greater than 0: ";
    }
}

void saveToFile() {
    ofstream ftFile("fulltime.txt");
    for (int i = 0; i < fullTimeList.size(); i++) {
        ftFile << fullTimeList[i].toString() << "\n";
    }
    ftFile.close();

    ofstream ptFile("parttime.txt");
    for (int i = 0; i < partTimeList.size(); i++) {
        ptFile << partTimeList[i].toString() << "\n";
    }
    ptFile.close();

    cout << "Data saved.\n";
}

void loadFromFile() {
    ifstream ftFile("fulltime.txt");
    while (ftFile) {
        FullTimeEmployee e;
        string nameFromFile;
        ftFile >> e.id >> nameFromFile >> e.age >> e.baseSalary >> e.allowance;
        if (ftFile) {
            for (char& c : nameFromFile) if (c == '_') c = ' ';
            e.name = nameFromFile;
            fullTimeList.push_back(e);
        }
    }
    ftFile.close();

    ifstream ptFile("parttime.txt");
    while (ptFile) {
        PartTimeEmployee p;
        string ptNameFromFile;
        ptFile >> p.id >> ptNameFromFile >> p.age >> p.hoursWorked >> p.hourlyRate;
        if (ptFile) {
            for (char& c : ptNameFromFile) if (c == '_') c = ' ';
            p.name = ptNameFromFile;
            partTimeList.push_back(p);
        }
    }
    ptFile.close();
}

void displayAll() {
    cout << "\n--- Full-Time Employees ---\n";
    cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age"
         << setw(10) << "Base" << setw(10) << "Allowance"
         << setw(12) << "Salary" << setw(8) << "Tax" << endl;
    for (int i = 0; i < fullTimeList.size(); i++) {
        fullTimeList[i].display();
    }

    cout << "\n--- Part-Time Employees ---\n";
    cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age"
         << setw(10) << "Hours" << setw(10) << "Rate"
         << setw(12) << "Salary" << setw(8) << "Tax" << endl;
    for (int i = 0; i < partTimeList.size(); i++) {
        partTimeList[i].display();
    }
}

void retrieveAnnualTaxByIdOrName() {
    cout << "\nEnter ID or Name to retrieve Annual Tax: ";
    string query;
    cin.ignore(); getline(cin, query);

    bool found = false;
    for (int i = 0; i < fullTimeList.size(); i++) {
        if (to_string(fullTimeList[i].id) == query || fullTimeList[i].name == query) {
            cout << "Annual Tax for " << fullTimeList[i].name << ": " << fullTimeList[i].getAnnualTax() << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        for (int i = 0; i < partTimeList.size(); i++) {
            if (to_string(partTimeList[i].id) == query || partTimeList[i].name == query) {
                cout << "Annual Tax for " << partTimeList[i].name << ": " << partTimeList[i].getAnnualTax() << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) cout << "Employee not found.\n";
}

void retrieveAnnualAllowanceByIdOrName() {
    cout << "\nEnter ID or Name to retrieve Annual Allowance: ";
    string query;
    cin.ignore(); getline(cin, query);

    bool found = false;
    for (int i = 0; i < fullTimeList.size(); i++) {
        if (to_string(fullTimeList[i].id) == query || fullTimeList[i].name == query) {
            cout << "Annual Allowance for " << fullTimeList[i].name << ": " << fullTimeList[i].getAnnualAllowance() << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        for (int i = 0; i < partTimeList.size(); i++) {
            if (to_string(partTimeList[i].id) == query || partTimeList[i].name == query) {
                cout << "Annual Allowance for " << partTimeList[i].name << ": " << partTimeList[i].getAnnualAllowance() << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) cout << "Employee not found.\n";
}

void deleteEmployeeByIdOrName() {
    cout << "\nEnter ID or Name to delete: ";
    string query;
    cin.ignore(); getline(cin, query);

    for (int i = 0; i < fullTimeList.size(); i++) {
        if (to_string(fullTimeList[i].id) == query || fullTimeList[i].name == query) {
            fullTimeList.erase(fullTimeList.begin() + i);
            cout << "Full-time employee deleted.\n";
            return;
        }
    }

    for (int i = 0; i < partTimeList.size(); i++) {
        if (to_string(partTimeList[i].id) == query || partTimeList[i].name == query) {
            partTimeList.erase(partTimeList.begin() + i);
            cout << "Part-time employee deleted.\n";
            return;
        }
    }

    cout << "Employee not found.\n";
}

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n============== Payroll Management System ==============\n";
        cout << "1. Add Full-Time Employee\n";
        cout << "2. Add Part-Time Employee\n";
        cout << "3. Display All Employees\n";
        cout << "4. Retrieve Annual Tax by ID or Name\n";
        cout << "5. Retrieve Annual Allowance by ID or Name\n";
        cout << "6. Delete Employee by ID or Name\n";
        cout << "7. Save and Exit\n";
        cout << "=======================================================\n";

        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        if (choice == 1) {
            FullTimeEmployee e;
            e.input();
            fullTimeList.push_back(e);
        } else if (choice == 2) {
            PartTimeEmployee p;
            p.input();
            partTimeList.push_back(p);
        } else if (choice == 3) {
            displayAll();
        } else if (choice == 4) {
            retrieveAnnualTaxByIdOrName();
        } else if (choice == 5) {
            retrieveAnnualAllowanceByIdOrName();
        } else if (choice == 6) {
            deleteEmployeeByIdOrName();
        } else if (choice == 7) {
            saveToFile();
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
