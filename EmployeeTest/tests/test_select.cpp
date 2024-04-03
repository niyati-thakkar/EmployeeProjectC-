#include "pch.h"
#include "HR.h"
#include "select.h"

TEST(PerformSelectTest, SimpleQueryExecution) {
    std::string query = "SELECT * FROM Employee";

    // Assuming you have a way to connect to the database
    Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
    bool result = db.selectQueryD(query); // Assuming selectQueryD returns true/false based on success

    // You can assert on the result (optional) based on your expected behavior
    // EXPECT_TRUE(result); // If successful execution is expected
}

TEST(ViewHelperTestEmplyee, SelectAllColumns) {
    Employee emp; // Replace with your Employee object
    std::string table = "Employee";
    std::map<int, PropertyMap<Employee>> map = emp.getMap(); // Assuming getMap() exists
    std::string cols;

    CRUD::SelectHelper::viewHelper(emp, true, table, map, emp.getLastKey(), cols);

    // Assuming PropertyMap<Employee> has a member named `name` for column names
    std::string expected_cols = "Employee.EmpId, Employee.FirstName, Employee.MiddleName, Employee.LastName, Employee.Contact, Employee.Email, Employee.DOB, Employee.JoiningDate, Employee.DepartmentID, Employee.ReportingManagerID, Employee.BaseSalary, Employee.PerformanceRating, Employee.YearsOfExperience"; // Add more columns based on map

    // Check if expected columns are present in the generated list
    EXPECT_EQ(cols.substr(0, expected_cols.length()), expected_cols);
}

TEST(ViewHelperTestHR, SelectAllColumns) {
    HR emp; // Replace with your Employee object
    std::string table = "Employee";
    std::string cols;

    CRUD::SelectHelper::viewHelper<HR>(emp, true, table, HR::getMap(), HR::getLastKey(), cols);

    // Assuming PropertyMap<Employee> has a member named `name` for column names
    std::string expected_cols = "Employee.HRID, Employee.ProficientLanguage, Employee.RecruitingExperience"; // Add more columns based on map

    // Check if expected columns are present in the generated list
    EXPECT_EQ(cols.substr(0, expected_cols.length()), expected_cols);
}
