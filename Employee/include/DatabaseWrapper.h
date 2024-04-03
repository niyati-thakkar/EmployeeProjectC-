#ifndef _DB_WRAPPER_H_
#define _DB_WRAPPER_H_

#include "Database.h"

class DatabaseWrapper {
public:
    static Database& getEmployeeDatabaseInstance() {
        static Database EmplDatabase{ "..\\..\\Employee\\Database\\Employee.db" };
        return EmplDatabase;
    }

    static Database& getDemoDatabaseInstance() {
        static Database DemoDatabase{ "..\\..\\Employee\\Database\\Employee.db" };
        return DemoDatabase;
    }

    static void resetEmployeeDatabase() {
        // Implement database reset logic here if needed
    }
};

#endif
