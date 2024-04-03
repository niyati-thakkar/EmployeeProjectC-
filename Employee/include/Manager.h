#ifndef _Manager_H_
#define _Manager_H_

#include<string>
#include "Employee.h"
#include<map>

class Manager : public Employee {
public:
    /**********************************************************************************
     *                              Getters
     **********************************************************************************/

    std::string getid() const {
        if (id != 0)
            return std::to_string(id);
        return "";
    }

    std::string getManagerSpecialization() const {
        return ManagerSpecialization;
    }

    std::string getYearsOfManagementExperience() const {
        if (yearsOfManagementExperience != 0)
            return std::to_string(yearsOfManagementExperience);
        return "";
    }

    std::string getEmpId() const {
        if (empId != 0)
            return std::to_string(empId);
        return "";
    }

    bool deleteEmp(std::string id) {
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        std::cout << db.executeQueryD(std::string{ "DELETE FROM EMPLOYEE WHERE ID = '" } + id + "';", true) << "\n";
        return true;
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    static size_t getLastKey() {
        return gettersetter.size() - 1;
    }

    /**********************************************************************************
     *                              Setters
     **********************************************************************************/

    bool setid(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "ManagerId", str)) {
            try {
                id = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Manager with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setManagerSpecialization(std::string str) {
        if (Validation::validateString(str)) {
            ManagerSpecialization = str;
            return true;
        }
        return false;
    }

    bool setEmpId(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable("EMPLOYEE", "EmpId", str)) {
            try {
                empId = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Employee with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setYearsOfManagementExperience(std::string str) {
        try {
            yearsOfManagementExperience = std::stoi(str);
            return true;
        }
        catch (...) {
            return false;
        }
        return false;
    }

    static std::map<int, PropertyMap<Manager>>& getMap() {
        return gettersetter;
    }

    double calculateSalary() override {
        try {
            double yoe = std::stod(getYearsOfExperience());
            double baseSalary = std::stod(getBaseSalary());
            return Employee::calculateSalary() + yoe * yoeBonus * baseSalary / 100;
        }
        catch (...) {
            return 0;
        }
    }

private:
    MID id{};
    EID empId{};
    std::string ManagerSpecialization;
    inline static double yoeBonus = 10.0;
    int yearsOfManagementExperience{};
    static inline std::string TABLE_NAME = "Manager";
    inline static std::map<int, PropertyMap<Manager>> gettersetter = {
        {0, PropertyMap<Manager>{"EmpId",& setEmpId,& getEmpId, false }},
        {1, PropertyMap<Manager>{"ManagerID",& setid,& getid, false }},
        {2, PropertyMap<Manager>{"ManagementSpecialization",& setManagerSpecialization,& getManagerSpecialization, false}},
        {3, PropertyMap<Manager>{"YearsOfManagementExperience",& setYearsOfManagementExperience,& getYearsOfManagementExperience, true}}
    };
};

#endif
