#ifndef _USER_TABLE_H_
#define _USER_TABLE_H_

#include <iostream>
#include <string>
#include <vector>
#include "crud.h"
#include <map>

namespace Table {
    static inline std::map<int, std::string> TYPE{
        {1, "BOOLEAN"},
        {2, "INTEGER"},
        {3, "DOUBLE"},
        {4, "TEXT"},
        {5, "DATE"}
    };

    inline bool createTable() {
        std::cout << "Enter Table Name" << "\n";
        std::string name;
        std::string query = "";
        std::vector<std::string> typesVector;
        for (auto& [key, val] : TYPE) {
            typesVector.push_back(val);
        }
        if (Utility::setInput(name)) {
            name = "UT_" + name;
            query += "CREATE TABLE " + name + "(";
            do {
                std::string colname;
                std::cout << "Enter Column Name" << "\n";
                if (Utility::setInput(colname)) {
                    query += colname + " ";

                    std::cout << "Choose Type of Data To store" << "\n";

                    int typeSelected = Utility::takeOption(false, typesVector);
                    if (typeSelected == 0) return false;
                    query += TYPE[typeSelected] + ", ";
                }
            } while (Utility::takeOption(false, "Add a Column", "Create Table") == 1);
            query = query.substr(0, query.length() - 2) + ");";
            if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); db.executeQueryD(query, true)) {
                std::cout << query << "\n";
                Database::logger.Info("Table Created Successfully");
                return true;
            }

        }

        Database::logger.Error(CRUD::INVALID_INPUT_MSG);
        return false;
    }

    inline bool insertIntoTable() {
        std::cout << "Select the table" << "\n";
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        auto tables = db.getUserTables();
        int opt = Utility::takeOption(false, tables);
        if (opt == 0) return false;
        std::string tableName = tables[opt - 1];

        auto columns = db.getTableColumns(tableName);
        std::string cols;
        for (const auto& column : columns) {
            cols += column.first + ", ";
        }
        cols.pop_back();
        cols.pop_back();

        std::string vals;
        for (size_t i = 0; i < columns.size(); ++i) {
            std::string value;
            std::cout << "Enter value for " << columns[i].first << ": ";
            Utility::setInput(value);
            vals += "'" + value + "', ";
        }
        vals.pop_back(); // Remove the trailing comma
        vals.pop_back(); // Remove the space

        std::string query = QueryE::generateInsertQuery(tableName, cols, vals);
        return db.executeQueryD(query, true);
    }

    inline bool deleteTable() {
        std::cout << "Select the table" << "\n";
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        auto tables = db.getUserTables();
        int opt = Utility::takeOption(false, tables);
        std::string tableName = tables[opt - 1];
        std::string query = "DROP " + tableName + ";";
        return db.executeQueryD(query, true);
    }

    inline bool showTable() {
        std::cout << "Select the table" << "\n";
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        auto tables = db.getUserTables();
        int opt = Utility::takeOption(false, tables);
        std::string tableName = tables[opt - 1];
        std::string query = "SELECT * FROM " + tableName + ";";
        return db.selectQueryD(query);
    }
};

#endif
