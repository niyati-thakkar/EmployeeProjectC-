#ifndef _MENU_H_
#define _MENU_H_

#include "Engineer.h"
#include "Manager.h"
#include "HR.h"
#include "Department.h"
#include "insert.h"
#include "select.h"
#include "update.h"
#include "delete.h"
#include "UserTable.h"
#include "Salary.h"

#include <iostream>

namespace Menu {
    inline void employeeMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("Employee Menu");
            int option = Utility::takeOption(true, "Insert Employee(s)", "View Employee(s)", "Update Employee(s)", "Delete Employee(s)");
            if (option == 0) return;
            Employee e;
            switch (option) {
            case 1: {
                CRUD::Insert::insertEntity<Employee>(e);
                break;
            }
            case 2: {
                CRUD::Select::view<Employee>(e);
                break;
            }
            case 3: {
                CRUD::Update::updateEntity<Employee>(e);
                break;
            }
            case 4: {
                CRUD::Delete::deleteEntity<Employee>(e);
                break;
            }
            }
        } while (whileFlag);
    }

    inline void departmentMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("Department Menu");
            int option = Utility::takeOption(true, "Insert Department", "View Department(s)", "Update Department(s)", "Delete From Department(s)");
            if (option == 0) return;
            Department e;
            switch (option) {
            case 1: {
                CRUD::Insert::insertEntity<Department>(e);
                break;
            }
            case 2: {
                CRUD::Select::view<Department>(e);
                break;
            }
            case 3: {
                CRUD::Update::updateEntity<Department>(e);
                break;
            }
            case 4: {
                CRUD::Delete::deleteEntity<Department>(e);
                break;
            }
            }
        } while (whileFlag);
    }

    inline void EngineerMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("Engineer Menu");
            int option = Utility::takeOption(true, "Insert Engineer(s)", "View Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)", "View Engineer Salary");
            if (option == 0) return;
            Engineer t;
            switch (option) {
            case 1: {
                CRUD::Insert::insertChildParent<Employee, Engineer>(t);
                break;
            }
            case 2: {
                CRUD::Select::viewC<Employee, Engineer>(t);
                break;
            }
            case 3: {
                CRUD::Update::updateEntitiesWithCascade<Employee, Engineer>(t);
                break;
            }
            case 4: {
                CRUD::Delete::deleteEntitiesWithCascade<Employee, Engineer>(t);
                break;
            }
            case 5: {
                CRUD::Salary::emplSalary<Employee, Engineer>(t);
                break;
            }
            }
        } while (whileFlag);
    }

    inline void ManagerMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("Manager Menu");
            int option = Utility::takeOption(true, "Insert Manager(s)", "View Manager(s)", "Update Manager(s)", "Delete Manager(s)", "View Manager Salary");
            if (option == 0) return;
            Employee e;
            Manager m;
            switch (option) {
            case 1: {
                CRUD::Insert::insertChildParent<Employee, Manager>(m);
                break;
            }
            case 2: {
                CRUD::Select::viewC<Employee, Manager>(m);
                break;
            }
            case 3: {
                CRUD::Update::updateEntitiesWithCascade<Employee, Manager>(m);
                break;
            }
            case 4: {
                CRUD::Delete::deleteEntitiesWithCascade<Employee, Manager>(m);
                break;
            }
            case 5: {
                CRUD::Salary::emplSalary<Employee, Manager>(m);
                break;
            }
            }
        } while (whileFlag);
    }

    inline void HRMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("HR Menu");
            int option = Utility::takeOption(true, "Insert HR(s)", "View HR(s)", "Update HR(s)", "Delete HR(s)", "View HR Salary");
            if (option == 0) return;
            Employee e;
            HR h;
            switch (option) {
            case 1: {
                CRUD::Insert::insertChildParent<Employee, HR>(h);
                break;
            }
            case 2: {
                CRUD::Select::viewC<Employee, HR>(h);
                break;
            }
            case 3: {
                CRUD::Update::updateEntitiesWithCascade<Employee, HR>(h);
                break;
            }
            case 4: {
                CRUD::Delete::deleteEntitiesWithCascade<Employee, HR>(h);
                break;
            }
            case 5: {
                CRUD::Salary::emplSalary<Employee, HR>(h);
                break;
            }
            }
        } while (whileFlag);
    }

    inline void userTables() {
        bool whileFlag = true;
        do {
            Utility::printHeading("User Defined Tables");
            int option = Utility::takeOption(true, "Create Table", "Insert Into Table", "View Table", "Delete Table");
            if (option == 0) return;
            switch (option) {
            case 1: {
                Table::createTable();
                break;
            }
            case 2: {
                Table::insertIntoTable();
                break;
            }
            case 3: {
                Table::showTable();
                break;
            }
            case 4: {
                Table::deleteTable();
                break;
            }
            }
        } while (whileFlag);
    }

    inline void mainMenu() {
        bool whileFlag = true;
        do {
            Utility::printHeading("Main menu");
            int option = Utility::takeOption(true, "User Defined Tables", "Employees", "Departments", "Manager", "Engineer", "HR and Finance");
            if (option == 0) return;
            switch (option) {
            case 1: {
                userTables();
                break;
            }
            case 2: {
                employeeMenu();
                break;
            }
            case 3: {
                departmentMenu();
                break;
            }
            case 4: {
                ManagerMenu();
                break;
            }
            case 5: {
                EngineerMenu();
                break;
            }
            case 6: {
                HRMenu();
                break;
            }
            }
        } while (whileFlag);
    }
}

#endif
