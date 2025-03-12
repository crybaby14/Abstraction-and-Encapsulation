#include <iostream>
#include <vector>
using namespace std;

// Base class for Employee
class Employee {
protected:
    int id;
    string name;
    double salary;
public:
    Employee(int id, string name, double salary) : id(id), name(name), salary(salary) {}
    virtual void displaySalary() = 0; // Abstract method
    virtual ~Employee() = default; // Virtual destructor
    int getId() { return id; }
};

// Full-time Employee
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int id, string name, double salary) : Employee(id, name, salary) {}
    void displaySalary() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

// Part-time Employee
class PartTimeEmployee : public Employee {
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyRate, int hoursWorked) 
        : Employee(id, name, hourlyRate), hoursWorked(hoursWorked) {}
    void displaySalary() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << salary << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << salary * hoursWorked << "\n\n";
    }
};

// Contractual Employee
class ContractualEmployee : public Employee {
    int projectsCompleted;
public:
    ContractualEmployee(int id, string name, double paymentPerProject, int projectsCompleted) 
        : Employee(id, name, paymentPerProject), projectsCompleted(projectsCompleted) {}
    void displaySalary() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salary << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << salary * projectsCompleted << "\n\n";
    }
};

bool isUniqueID(int id, vector<Employee*>& employees) {
    for (auto& emp : employees) {
        if (emp->getId() == id) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<Employee*> employees;
    int choice;
    
    do {
        cout << "\n***** M e n u *****\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid input! Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        if (choice == 1 || choice == 2 || choice == 3) {
            int id;
            string name;
            double salary;
            
            do {
                cout << "Enter ID: ";
                while (!(cin >> id) || id <= 0) {
                    cout << "Invalid ID! Please enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                if (!isUniqueID(id, employees)) {
                    cout << "Duplicate ID! Please enter a unique ID.\n";
                }
            } while (!isUniqueID(id, employees));
            
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            if (choice == 1) {
                cout << "Enter Fixed Salary: ";
                while (!(cin >> salary) || salary <= 0) {
                    cout << "Invalid salary! Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                employees.push_back(new FullTimeEmployee(id, name, salary));
            } 
            else if (choice == 2) {
                int hoursWorked;
                cout << "Enter Hourly Rate: ";
                while (!(cin >> salary) || salary <= 0) {
                    cout << "Invalid rate! Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cout << "Enter Hours Worked: ";
                while (!(cin >> hoursWorked) || hoursWorked <= 0) {
                    cout << "Invalid hours! Please enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                employees.push_back(new PartTimeEmployee(id, name, salary, hoursWorked));
            } 
            else if (choice == 3) {
                int projectsCompleted;
                cout << "Enter Payment Per Project: ";
                while (!(cin >> salary) || salary <= 0) {
                    cout << "Invalid amount! Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cout << "Enter Number of Projects Completed: ";
                while (!(cin >> projectsCompleted) || projectsCompleted <= 0) {
                    cout << "Invalid number! Please enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                employees.push_back(new ContractualEmployee(id, name, salary, projectsCompleted));
            }
        }
        else if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            for (auto& emp : employees) {
                emp->displaySalary();
            }
            
            char retry;
            cout << "Would you like to go back to the menu? (y/n): ";
            while (!(cin >> retry) || (retry != 'y' && retry != 'n')) {
                cout << "Invalid input! Please enter 'y' or 'n': ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            if (retry == 'n') break;
        }
    } while (choice != 5);
    
    for (auto emp : employees) {
        delete emp;
    }
    return 0;
}
