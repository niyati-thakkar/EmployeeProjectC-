#ifndef _DATABASE_H_
#define _DATABASE_H_

#include<iostream>
#include<string>
#include <sqlite3.h>
#include "Log.h"

class Database {
    friend class DatabaseWrapper;
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    Database(const Database& d) = delete;
    Database(Database&& d) = delete;

    Database(const std::string& path) {
        rc = sqlite3_open(path.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "can't open db" << "\n";
            return;
        }
        else {
            sqlite3_exec(db, "PRAGMA case_sensitive_like = ON;", callback, 0, &zErrMsg);
            sqlite3_exec(db, "PRAGMA foreign_keys = ON;", callback, 0, &zErrMsg);
        }
    }

    ~Database() {
        sqlite3_exec(db, "PRAGMA foreign_keys = OFF;", callback, 0, &zErrMsg);
        sqlite3_close(db);
    }

public:
    inline static Lognspace::Log logger{ Lognspace::Log::Level::LevelInfo, "Database\\EmployeeLogger.txt" };

    static int callbackPrint(void* count, int argc, char** argv, char** azColName) {
        int* cnt = (static_cast<int*>(count));
        (*cnt)++;
        int maxColumnNameWidth = 30;
        int maxColumnValueWidth = 60;
        int totalWidth = maxColumnNameWidth + maxColumnValueWidth + 5;

        std::cout << "+";
        for (int i = 0; i < totalWidth; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
        std::cout << std::setfill(' ');

        // Print table
        for (int i = 0; i < argc; ++i) {
            std::cout << "| " << std::left << std::setw(maxColumnNameWidth) << azColName[i] << " | ";
            std::cout << std::setw(maxColumnValueWidth) << (argv[i] ? argv[i] : "-") << " |" << std::endl;
        }

        std::cout << "+";

        for (int i = 0; i < totalWidth; i++) {
            std::cout << "-";
        }

        std::cout << "+" << std::endl;
        std::cout << std::setfill(' ');

        return 0;
    }

    static int callback(void* /*unused*/, int /*unused*/, char** /*unused*/, char** /*unused*/) {
        // This callback function is empty because we only need to execute the PRAGMA statements
        // There's no need to process any results, so we can leave it empty.
        return 0;
    }

    static int callbackCounter(void* count, int argc, char** argv, char** azColName) {
        int* cnt = (static_cast<int*>(count));
        (*cnt)++;
        return 0;
    }

    bool executeQueryD(std::string query, bool warn) {
        const char* sqlq = query.c_str();
        rc = sqlite3_exec(db, sqlq, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        }
        else {
            if (warn && sqlite3_changes(db) == 0) {
                logger.Warn("No records Affected!");
                return false;
            }
        }
        return true;
    }

    bool selectQueryD(std::string query, int(*callbackfunc)(void*, int, char**, char**) = callbackPrint) {
        const char* sql = query.c_str();
        int count = 0;
        rc = sqlite3_exec(db, sql, callbackfunc, &count, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        }
        else {
            if (count == 0) {
                logger.Warn("No Records Found.");
                return false;
            }
            return true;
        }
    }

    virtual int valueExistsInTable(const std::string& tableName, const std::string& col, const std::string& value) {
        std::string query = "SELECT * FROM " + tableName + " WHERE " + col + " = '" + value + "'; ";
        const char* sql = query.c_str();
        int count = 0;
        rc = sqlite3_exec(db, sql, callbackCounter, &count, &zErrMsg);
        return count;
    }

    std::string lastInsertedValue() {
        const char* query = "SELECT last_insert_rowid();";
        std::string lastID;

        // Callback function to retrieve last inserted row ID
        auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
            if (argc > 0 && argv[0] != nullptr) {
                *static_cast<std::string*>(data) = argv[0];
            }
            return 0;
            };

        char* zErrMsg = nullptr;
        int rc = sqlite3_exec(db, query, callback, &lastID, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }

        return lastID;
    }

    std::string getColValue(const std::string& tableName, const std::string& columnName, const std::string& primaryKey, const std::string& columnToFetch) {
        sqlite3_stmt* stmt;
        std::string result;

        std::string sql = "SELECT " + columnToFetch + " FROM " + tableName + " WHERE " + columnName + " = ?;";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return "";
        }

        rc = sqlite3_bind_text(stmt, 1, primaryKey.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return "";
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            const unsigned char* colValue = sqlite3_column_text(stmt, 0);
            if (colValue)
                result = reinterpret_cast<const char*>(colValue);
        }
        else if (rc == SQLITE_DONE) {
            std::cerr << "No rows returned." << std::endl;
        }
        else {
            std::cerr << "Error fetching row: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);

        return result;
    }

    bool getPrimaryKeys(std::string query, std::vector<std::string>& empids) {
        rc = sqlite3_exec(db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
            std::vector<std::string>* empids = static_cast<std::vector<std::string>*>(data);
            for (int i = 0; i < argc; i++) {
                empids->push_back(argv[i]);
            }
            return 0;
            }, &empids, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        }

        return true;
    }

    std::vector<std::string> getUserTables() {
        std::vector<std::string> tables{};

        std::string query = "SELECT name FROM sqlite_master WHERE type='table' AND name LIKE 'UT_%';";

        auto callbackFunction = [](void* data, int argc, char** argv, char** /*unused*/) -> int {
            std::vector<std::string>* tables = static_cast<std::vector<std::string>*>(data);
            for (int i = 0; i < argc; ++i) {
                tables->push_back(argv[i]);
            }
            return 0;
            };

        // Execute the query
        rc = sqlite3_exec(db, query.c_str(), callbackFunction, &tables, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return {};
        }

        return tables;
    }

    std::vector<std::pair<std::string, std::string>> getTableColumns(const std::string& tableName) {
        std::vector<std::pair<std::string, std::string>> columns{};

        std::string query = "PRAGMA table_info(" + tableName + ");";

        auto callbackFunction = [](void* data, int argc, char** argv, char** /*unused*/) -> int {
            std::vector<std::pair<std::string, std::string>>* columns = static_cast<std::vector<std::pair<std::string, std::string>>*>(data);
            if (argc >= 3) { // Ensure there are enough columns
                columns->emplace_back(argv[1], argv[2]); // Column name is argv[1], data type is argv[2]
            }
            return 0;
            };

        rc = sqlite3_exec(db, query.c_str(), callbackFunction, &columns, &zErrMsg);

        if (rc) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return {};
        }

        return columns;
    }

    bool startTransaction() {
        // Begin a transaction
        const char* query = "BEGIN TRANSACTION;";
        return executeQueryD(query, false);
    }

    bool commitTransaction() {
        // Commit the transaction
        const char* query = "COMMIT;";
        return executeQueryD(query, false);
    }

    bool rollbackTransaction() {
        // Rollback the transaction
        const char* query = "ROLLBACK;";
        return executeQueryD(query, false);
    }
};

#endif
