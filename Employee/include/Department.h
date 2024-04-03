#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_

#include <string>
#include "Utility.h"
#include <map>

class Department {
public:
    /**********************************************************************************
     *                              Getters
     **********************************************************************************/

    std::string getid() const {
        if (id != 0)
            return std::to_string(id);
        return "";
    }

    std::string getDeptName() const {
        return deptName;
    }

    std::string getDeptManagerId() const {
        if (deptManagerId != 0)
            return std::to_string(deptManagerId);
        return "";
    }

    std::string getDescription() const {
        return description;
    }

    static std::map<int, PropertyMap<Department>>& getMap() {
        return gettersetter;
    }

    static size_t getLastKey() {
        return gettersetter.size();
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    /**********************************************************************************
     *                              Setters
     **********************************************************************************/

    bool setid(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "DepartmentID", str)) {
            try {
                id = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Department with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setDeptName(std::string str) {
        if (Validation::validateString(str)) {
            deptName = str;
            return true;
        }
        return false;
    }

    bool setDeptManagerId(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable("Employee", "EmpId", str)) {
            try {
                deptManagerId = std::stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Employee with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setDescription(std::string str) {
        if (Validation::validateText(str)) {
            description = str;
            return true;
        }
        return false;
    }

private:
    DID id{};
    std::string deptName;
    MID deptManagerId{};
    std::string description;

    inline static std::string TABLE_NAME = "DEPARTMENT";

    inline static std::map<int, PropertyMap<Department>> gettersetter = {
        {1, PropertyMap<Department>{"DepartmentID",& setid,& getid, false }},
        {2, PropertyMap<Department>{"DeptName",& setDeptName,& getDeptName, false}},
        {3, PropertyMap<Department>{"DeptManager",& setDeptManagerId,& getDeptManagerId, false}},
        {4, PropertyMap<Department>{"Description",& setDescription,& getDescription, true}},
    };
};

#endif
