#ifndef _INSERT_H_
#define _INSERT_H

#include <string>
#include "crud.h"

namespace CRUD {
    namespace InsertHelper {
        template<typename T1, typename T2 = T1>
        bool processPropertyInsertion(T2& entity, std::map<int, PropertyMap<T2>>& propertyMap) {
            auto performInsertion = [&entity](PropertyMap<T2>& property) -> bool {
                if (property.isOptional) {
                    std::cout << "Enter " << property.name << " (Optional):\n";
                    std::string temp;
                    if (!Utility::setInput(temp) || temp[0] == '#' || !(entity.*property.setter)(temp)) {
                        std::cout << "Optional Field is left blank!\n";
                    }
                }
                else {
                    if (!Utility::getUserInput(entity, property)) {
                        clear(entity);
                        return false;
                    }
                }
                return true;
                };

            return applyToAllProperties(entity, propertyMap, 2, T2::getLastKey() + 1, performInsertion);
        }

        template<typename T>
        void processInsertedProperties(T& entity, std::map<int, PropertyMap<T>>& propertyMap, std::string& columns, std::string& values) {

            auto gatherQuery = [&](PropertyMap<T>& property)-> bool {
                auto& getter = property.getter;
                auto value = (entity.*getter)();
                if (!value.empty()) {
                    columns += property.name + ", ";
                    values += "'" + value + "', ";
                }
                return true;
                };


            if (propertyMap.find(0) != propertyMap.end()) {
                gatherQuery(propertyMap[0]);
            }

            applyToAllProperties(entity, propertyMap, 2, T::getLastKey() + 1, gatherQuery);

            if (columns.length() > 2 && values.length() > 2) {
                columns.pop_back();
                columns.pop_back();
                values.pop_back();
                values.pop_back();
            }
        }

        template<typename T>
        bool performInsert(Database& db, T& entity, std::map<int, PropertyMap<T>>& propertyMap) {
            if (std::string columns, values;  processPropertyInsertion<T>(entity, propertyMap)) {
                processInsertedProperties(entity, propertyMap, columns, values);
                std::string query = QueryE::generateInsertQuery(T::getTableName(), columns, values);
                return db.executeQueryD(query, true);
            }
            return false;
        }
    }

    namespace Insert {
        template<typename T>
        bool insertEntity(T& entity) {
            auto& entityMap = T::getMap();
            std::string tableName = T::getTableName();
            if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();  InsertHelper::performInsert<T>(db, entity, entityMap)) {
                Database::logger.Info(tableName, "Inserted successfully!");
                return true;
            }
            Database::logger.Error(tableName, "Insertion Failed!");
            return false;
        }

        template<typename T1, typename T2>
        bool insertChildParent(T2& child) {
            auto& parentMap = T1::getMap();
            auto& childMap = T2::getMap();
            auto parentTableName = T1::getTableName();
            auto childTableName = T2::getTableName();
            bool operationPerformed = true;

            std::string employeeid;

            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();

            if (!insertEntity<T1>(child)) {
                operationPerformed = false;
            }
            employeeid = db.lastInsertedValue();
            if (!std::bind(childMap[0].setter, &child, std::placeholders::_1)(employeeid) || !operationPerformed || !InsertHelper::performInsert<T2>(db, child, childMap)) {
                operationPerformed = false;
            }

            if (operationPerformed) {
                Address& address = child.getAddress();
                auto& addrMap = Address::getMap();
                std::bind(addrMap[0].setter, &address, std::placeholders::_1)(employeeid);
                std::string addressTableName = address.getTableName();
                insertEntity(address);

                Database::logger.Info(childTableName, "Inserted successfully!");
                return true;
            }
            else {
                db.executeQueryD(("DELETE FROM " + childTableName + "WHERE empid = " + employeeid + ";"), true);
                Database::logger.Error(childTableName, "Insertion Failed!");
                return false;
            }
        }
    }
}
#endif

