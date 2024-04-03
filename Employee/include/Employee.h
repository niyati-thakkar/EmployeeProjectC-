#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>
#include <string>
#include <map>
#include <optional>
#include <cmath>
#include "Address.h"

class Employee {
public:
    /**********************************************************************************
     *                              Getters
     **********************************************************************************/

    std::string getid() const {
        if (id != 0)
            return std::to_string(id);
        return "";
    }

    std::string getPerformanceRating() const {
        if (performanceRating != 0)
            return std::to_string(performanceRating);
        return "";
    }

    std::string getBaseSalary() const {
        if (baseSalary != 0)
            return std::to_string(baseSalary);
        return "";
    }

    std::string getYearsOfExperience() const {
        if (yearsOfExperience != 0)
            return std::to_string(yearsOfExperience);
        return "";
    }

    std::string getFname() const {
        return fname;
    }

    std::string getMname() const {
        return mname;
    }

    std::string getLname() const {
        return lname;
    }

    std::string getContact() const {
        return contact;
    }

    std::string getEmail() const {
        return email;
    }

    Address& getAddress() {
        return empAddr;
    }

    std::string getDeptId() const {
        if (deptId != 0)
            return std::to_string(deptId);
        return "";
    }

    std::string getReportingManagerId() const {
        if (reportingManagerId != 0)
            return std::to_string(reportingManagerId);
        return "";
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    std::string getDOB() const {
        return DOB;
    }

    std::string getJoiningDate() const {
        return joiningDate;
    }

    static std::map<int, PropertyMap<Employee>>& getMap() {
        return gettersetter;
    }

    static size_t getLastKey() {
        return gettersetter.size();
    }

    /**********************************************************************************
     *                              Setters
     **********************************************************************************/

    bool setid(std::string i) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(i) && db.valueExistsInTable(TABLE_NAME, "EmpId", i)) {
            try {
                id = std::stoi(i);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Employee with given ID doesn't exist!" << "\n";
        return false;
    };

    bool setFname(std::string str) {
        if (Validation::validateString(str)) {
            fname = str;
            return true;
        }
        return false;
    }

    bool setMname(std::string str) {
        if (str[0] == '#') {
            mname = "";
            return true;
        }
        if (Validation::validateString(str)) {
            mname = str;
            return true;
        }
        return false;
    }

    bool setLname(std::string str) {
        if (Validation::validateString(str)) {
            lname = str;
            return true;
        }
        return false;
    }

    bool setAddress(Address a) {
        empAddr = a;
        return true;
    }

    bool setContact(std::string str) {
        if (Validation::validateContact(str)) {
            contact = str;
            return true;
        }
        return false;
    }

    bool setEmail(std::string str) {
        if (str[0] == '#') {
            email = "";
            return true;
        }
        if (Validation::validateEmail(str)) {
            email = str;
            return true;
        }
        return false;
    }

    bool setDOB(std::string str) {
        if (Validation::validateDate(str)) {
            DOB = str;
            return true;
        }
        return false;
    }

    bool setJoiningDate(std::string str) {
        if (Validation::validateDate(str)) {
            joiningDate = str;
            return true;
        }
        return false;
    }

    bool setDeptId(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable("Department", "DepartmentID", str)) {
            try {
                deptId = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Department with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setReportingManagerId(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "EmpId", str)) {
            try {
                reportingManagerId = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        if (str[0] == '#') return true;
        std::cout << "Employee with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setYearsOfExperience(std::string e) {
        try {
            yearsOfExperience = std::stoi(e);
        }
        catch (...) {
            return false;
        }
        if (yearsOfExperience < 0 || yearsOfExperience > 100) {
            yearsOfExperience = 0;
            return false;
        }
        return true;
    }

    bool setPerformanceRating(std::string e) {
        try {
            performanceRating = std::round(std::stod(e) * 100) / 100;
        }
        catch (...) {
            return false;
        }
        if (performanceRating < 0 || performanceRating > 5) {
            performanceRating = 0;
            return false;
        }
        return true;
    }

    bool setBaseSalary(std::string e) {
        try {
            baseSalary = std::round(std::stod(e) * 100) / 100;
        }
        catch (...) {
            return false;
        }
        if (baseSalary < 0) {
            baseSalary = 0;
            return false;
        }
        return true;
    }

    virtual double calculateSalary() {
        return (expenseAllowence + baseSalary + performanceRating * 4 * baseSalary / 100);
    }

private:
    EID id{};
    std::string fname;
    std::string mname;
    std::string lname;
    std::string contact;
    std::string email;
    std::string DOB;
    std::string joiningDate;
    DID deptId{};
    EID reportingManagerId{};
    int yearsOfExperience{};
    double performanceRating{};
    double baseSalary{};
    Address empAddr;

    inline static double expenseAllowence = 5000;
    static inline std::string TABLE_NAME = "EMPLOYEE";
    inline static std::map<int, PropertyMap<Employee>> gettersetter = {
        {1, PropertyMap<Employee>{"EmpId",& setid,& getid, false }},
        {2, PropertyMap<Employee>{"FirstName",& setFname,& getFname, false}},
        {3, PropertyMap<Employee>{"MiddleName",& setMname,& getMname, true}},
        {4, PropertyMap<Employee>{"LastName",& setLname,& getLname, false}},
        {5, PropertyMap<Employee>{"Contact",& setContact,& getContact, false}},
        {6, PropertyMap<Employee>{"Email",& setEmail,& getEmail, true}},
        {7, PropertyMap<Employee>{"DOB",& setDOB,& getDOB, false}},
        {8, PropertyMap<Employee>{"JoiningDate",& setJoiningDate,& getJoiningDate, false}},
        {9, PropertyMap<Employee>{"DepartmentID",& setDeptId,& getDeptId, false}},
        {10, PropertyMap<Employee>{"ReportingManagerID",& setReportingManagerId,& getReportingManagerId, true}},
        {11, PropertyMap<Employee>{"BaseSalary",& setBaseSalary,& getBaseSalary, false}},
        {12, PropertyMap<Employee>{"PerformanceRating",& setPerformanceRating,& getPerformanceRating, false}},
        {13, PropertyMap<Employee>{"YearsOfExperience",& setYearsOfExperience,& getYearsOfExperience, false}},
    };
};

#endif
