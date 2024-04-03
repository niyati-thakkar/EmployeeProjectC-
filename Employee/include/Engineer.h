#ifndef _Engineer_H_
#define _Engineer_H_

#include<string>
#include "Employee.h"
#include<map>

class Engineer : public Employee {
public:
    /**********************************************************************************
     *                              Getters
     **********************************************************************************/

    std::string getid() const {
        if (id != 0)
            return std::to_string(id);
        return "";
    }

    std::string getEngineerSpecialization() const {
        return EngineerSpecialization;
    }

    std::string getCurrentProject() const {
        return currentProject;
    }

    std::string getEmpId() const {
        if (empId != 0)
            return std::to_string(empId);
        return "";
    }

    static std::map<int, PropertyMap<Engineer>>& getMap() {
        return gettersetter;
    }

    static size_t getLastKey() {
        return gettersetter.size() - 1;
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    /**********************************************************************************
     *                              Setters
     **********************************************************************************/

    bool setid(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "EngineerId", str)) {
            try {
                id = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Engineer with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setEngineerSpecialization(std::string str) {
        if (Validation::validateString(str)) {
            EngineerSpecialization = str;
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

    bool setCurrentProject(std::string str) {
        if (Validation::validateString(str)) {
            currentProject = str;
            return true;
        }
        return false;
    }

    double calculateSalary() override {
        try {
            double yoe = std::stod(getYearsOfExperience());
            double basesalary = std::stod(getBaseSalary());
            return Employee::calculateSalary() + yoe * yoeBonus * basesalary / 100;
        }
        catch (...) {
            return 0;
        }
    }

private:
    TID id{};
    EID empId{};
    std::string EngineerSpecialization;
    std::string currentProject;
    inline static double yoeBonus = 9.0;
    inline static std::string TABLE_NAME = "Engineer";
    inline static std::map<int, PropertyMap<Engineer>> gettersetter = {
        {
            0,
            PropertyMap<Engineer>{"EmpId",& setEmpId,& getEmpId, false}
        },
        {
            1,
            PropertyMap<Engineer>{"EngineerID",& setid,& getid, false}
        },
        {
            2,
            PropertyMap<Engineer>{"EngineerSpecialization",& setEngineerSpecialization,& getEngineerSpecialization, false}
        },
        {
            3,
            PropertyMap<Engineer>{"CurrentProject",& setCurrentProject,& getCurrentProject, true}
        }
    };
};

#endif
