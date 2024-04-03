#include "Employee.h"
#include "Query.h"
#ifndef _EmployeeFixture_H_
#define _EmployeeFixture_H_

class EmployeeFixture : public testing::Test {
public:
    EmployeeFixture() {
        emp.setFname("John");
        emp.setMname("Doe");
        emp.setLname("Smith");
        emp.setContact("123-456-7890");
        emp.setEmail("john@example.com");
        emp.setDOB("12-02-2024");
        emp.setJoiningDate("12-02-2024");
        emp.setDeptId("2000002");
        emp.setReportingManagerId("#");
        emp.setBaseSalary("60000");
        emp.setPerformanceRating("3.8");
        emp.setYearsOfExperience("8");
    }

    ~EmployeeFixture() {
        Database& db = DatabaseWrapper::getDemoDatabaseInstance();
        db.executeQueryD(QueryE::generateDeleteQuery("Employee", "contact", "123-456-7890"), false);
    }

    Employee emp;
};
#endif
