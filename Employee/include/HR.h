#ifndef _HR_H_
#define _HR_H_

#include<string>
#include "Employee.h"
#include<map>

class HR : public Employee {
public:
    /**********************************************************************************
     *                              Getters
     **********************************************************************************/

    std::string getid() const {
        if (id != 0)
            return std::to_string(id);
        return "";
    }

    std::string getEmpId() const {
        if (empId != 0)
            return std::to_string(empId);
        return "";
    }

    std::string getProficientLanguage() const {
        return proficientLanguage;
    }

    std::string getRecruitingExperience() const {
        if (recruitingExperience != 0)
            return std::to_string(recruitingExperience);
        return "";
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    static std::map<int, PropertyMap<HR>>& getMap() {
        return gettersetter;
    }

    static size_t getLastKey() {
        return gettersetter.size() - 1;
    }

    /**********************************************************************************
     *                              Setters
     **********************************************************************************/

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

    bool setid(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "HRID", str)) {
            try {
                id = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "HR with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setProficientLanguage(std::string str) {
        if (Validation::validateString(str)) {
            proficientLanguage = str;
            return true;
        }
        return false;
    }

    bool setRecruitingExperience(std::string str) {
        try {
            recruitingExperience = std::stoi(str);
            return true;
        }
        catch (...) {
            return false;
        }
        return false;
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
    HID id{};
    EID empId{};
    std::string proficientLanguage;
    int recruitingExperience{};
    inline static double yoeBonus = 8.0;
    inline static std::string TABLE_NAME = "HR";
    inline static std::map<int, PropertyMap<HR>> gettersetter = {
        {0, PropertyMap<HR>{"EmpId",& setEmpId,& getEmpId, false }},
        {1, PropertyMap<HR>{"HRID",& setid,& getid, false }},
        {2, PropertyMap<HR>{"ProficientLanguage",& setProficientLanguage,& getProficientLanguage, false}},
        {3, PropertyMap<HR>{"RecruitingExperience",& setRecruitingExperience,& getRecruitingExperience, true}}
    };
};

#endif
