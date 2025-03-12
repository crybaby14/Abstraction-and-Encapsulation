#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_EMPLOYEES = 100;

// Base class for Employee
class Employee {
private:
    int id;
    string name;
    double salary;
public:
    Employee(int id, string name, double salary) : id(id), name(name), salary(salary) {}
    virtual void displaySalary() const = 0; // Abstract method with const
    virtual ~Employee() = default; // Virtual destructor
    int getId() const { return id; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
};

// Full-time Employee
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int id, string name, double salary) : Employee(id, name, salary) {}
    void displaySalary() const override {
        cout << "Employee: " << getName() << " (ID: " << getId() << ")\n";
        cout << "Fixed Monthly Salary: $" << getSalary() << "\n\n";
    }
};

// Part-time Employee
class PartTimeEmployee : public Employee {
    double hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyRate, double hoursWorked) 
        : Employee(id, name, hourlyRate), hoursWorked(hoursWorked) {}
    void displaySalary() const override {
        cout << "Employee: " << getName() << " (ID: " << getId() << ")\n";
        cout << "Hourly Wage: $" << getSalary() << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << getSalary() * hoursWorked << "\n\n";
    }
};

// Contractual Employee
class ContractualEmployee : public Employee {
    int projectsCompleted;
public:
    ContractualEmployee(int id, string name, double paymentPerProject, int projectsCompleted) 
        : Employee(id, name, paymentPerProject), projectsCompleted(projectsCompleted) {}
    void displaySalary() const override {
        cout << "Employee: " << getName() << " (ID: " << getId() << ")\n";
        cout << "Contract Payment Per Project: $" << getSalary() << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << getSalary() * projectsCompleted << "\n\n";
    }
};

Employee* employees[MAX_EMPLOYEES];
int employeeCount = 0;

bool isUniqueID(int id) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i]->getId() == id) {
            return false;
        }
    }
    return true;
}

bool isValidNumber(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidName(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

int getValidChoice() {
    string input;
    cout << "\nMenu\n";
    cout << "1 - Full-time Employee\n";
    cout << "2 - Part-time Employee\n";
    cout << "3 - Contractual Employee\n";
    cout << "4 - Display Payroll Report\n";
    cout << "5 - Exit\n";
    
    do {
        cout << "Enter your choice: ";
        cin >> input;
        
        if (isValidNumber(input)) {
            int choice = stoi(input);
            if (choice >= 1 && choice <= 5) {
                return choice;
            }
        }
        
        cout << "Invalid input! Please enter a number between 1 and 5.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        
    } while (true);
}

int main() {
    int choice;
    do {
        choice = getValidChoice(); // Ensures only numeric input is accepted

        if (choice == 1 || choice == 2 || choice == 3) {
            if (employeeCount >= MAX_EMPLOYEES) {
                cout << "Employee list is full!\n";
                continue;
            }
            
            string idStr;
            int id;
            string name;
            double salary;
            
            cout << "Enter ID: ";
            cin >> idStr;
            while (!isValidNumber(idStr) || !isUniqueID(stoi(idStr))) {
                cout << "Invalid or duplicate ID! Please enter a unique numeric ID: ";
                cin >> idStr;
            }
            id = stoi(idStr);
            
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            while (!isValidName(name)) {
                cout << "Invalid name! Please enter alphabetic characters only: ";
                getline(cin, name);
            }

            if (choice == 1) {
                cout << "Enter Fixed Salary: ";
                cin >> salary;
                employees[employeeCount++] = new FullTimeEmployee(id, name, salary);
            } else if (choice == 2) {
                double hoursWorked;
                cout << "Enter Hourly Rate: ";
                cin >> salary;
                cout << "Enter Hours Worked: ";
                cin >> hoursWorked;
                employees[employeeCount++] = new PartTimeEmployee(id, name, salary, hoursWorked);
            } else if (choice == 3) {
                int projectsCompleted;
                cout << "Enter Payment Per Project: ";
                cin >> salary;
                cout << "Enter Number of Projects Completed: ";
                cin >> projectsCompleted;
                employees[employeeCount++] = new ContractualEmployee(id, name, salary, projectsCompleted);
            }
        }
        else if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            for (int i = 0; i < employeeCount; i++) {
                employees[i]->displaySalary();
            }
            
            char retry;
            cout << "Would you like to go back to the menu? (y/n): ";
            cin >> retry;
            if (retry == 'n') break;
        }
    } while (choice != 5);
    
    // Clean up dynamically allocated memory
    for (int i = 0; i < employeeCount; i++) {
        delete employees[i];
    }
    return 0;
}
