#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include<iostream>
#include<string>
#include<map>
#include<optional>
#include "Utility.h"
#include <cmath>

class Address {
public:
    std::string getid() const {
        return std::to_string(id);
    }

    std::string getLocation() const {
        return location;
    }

    std::string getCity() const {
        return city;
    }

    std::string getState() const {
        return state;
    }

    std::string getPincode() const {
        return std::to_string(pincode);
    }

    std::string getEmpId() const {
        if (empId != 0)
            return std::to_string(empId);
        return "";
    }

    static std::string getTableName() {
        return TABLE_NAME;
    }

    static std::map<int, PropertyMap<Address>>& getMap() {
        return gettersetter;
    }

    static size_t getLastKey() {
        return gettersetter.size() - 1;
    }

    bool setid(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable(TABLE_NAME, "AddressID", str)) {
            try {
                id = stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Address with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setLocation(std::string loc) {
        if (Validation::validateText(loc)) {
            location = loc;
            return true;
        }
        return false;
    }

    bool setState(std::string st) {
        if (Validation::validateString(st)) {
            state = st;
            return true;
        }
        return false;
    }

    bool setCity(std::string ct) {
        if (Validation::validateString(ct)) {
            city = ct;
            return true;
        }
        return false;
    }

    bool setEmpId(std::string str) {
        if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); Validation::validateID(str) && db.valueExistsInTable("EMPLOYEE", "Empid", str)) {
            try {
                empId = stoi(str);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        std::cout << "Employee with given ID doesn't exist!" << "\n";
        return false;
    }

    bool setPincode(std::string pin) {
        if (Validation::validatePincode(pin)) {
            try {
                int temp = stoi(pin);
                if (temp > 99999) {
                    pincode = temp;
                    return true;
                }
            }
            catch (...) {
                return false;
            }
            return false;
        }
        return false;
    }

private:
    AID id{};
    EID empId{};
    std::string location;
    std::string city;
    std::string state;
    PIN pincode{};
    static inline std::string TABLE_NAME = "ADDRESS";
    inline static std::map<int, PropertyMap<Address>> gettersetter = {
        {0, PropertyMap<Address>{"EmpId",& setEmpId,& getEmpId, false }},
        {1, PropertyMap<Address>{"ID",& setid,& getid, false }},
        {2, PropertyMap<Address>{"Location",& setLocation,& getLocation, false}},
        {3, PropertyMap<Address>{"City",& setCity,& getCity, false}},
        {4, PropertyMap<Address>{"State",& setState,& getState, false}},
        {5, PropertyMap<Address>{"Pincode",& setPincode,& getPincode, false}}
    };
};

#endif
