#include "pch.h"
#include "crud.h"
#include "Manager.h"
#include "Employee.h"

TEST(DataCollectionTest, SingleTableDepartmentFilter) {
    Employee emp;
    emp.setDeptId("2000001");

    std::pair<std::string, int> tableAndIndex = { "Employee", 9 };
    std::vector<std::string> employeeIds;

    CRUD::collectEntityIdsFromSingleTable<Employee>(emp, tableAndIndex, employeeIds);

    EXPECT_FALSE(employeeIds.empty());
}
