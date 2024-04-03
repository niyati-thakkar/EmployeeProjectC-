#ifndef _SALARY_H_
#define _SALARY_H_

#include <map>
#include <string>
#include "select.h"

namespace CRUD {
    namespace Salary {
        template<typename T1, typename T2 = T1>
        void emplSalary(T2& e) {
            if (Utility::getUserInput(e, e.getMap()[1])) {
                std::string empId = e.getid();

                std::string columnsToSelect;
                SelectHelper::viewHelper(e, true, T2::getTableName(), T2::getMap(), T2::getLastKey(), columnsToSelect);
                std::string query = QueryE::generateSelectQuery(T2::getTableName(), columnsToSelect);

                // Call a function to fetch data from the database
                storeToObject<T1, T2>(e);
                std::cout << "Salary of " << (e.*T1::getMap()[2].getter)() << " is " << e.calculateSalary() << "\n";
            }
        }
    }
}

#endif