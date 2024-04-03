#include "pch.h"
#include "DepartmentFixture.h" 
#include "EngineerFixture.h"
#include "insert.h"

TEST_F(DepartmentFixture, TestProcessPropertyInsertionDepartment) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();

    std::string columns, values;
    CRUD::InsertHelper::processInsertedProperties(department, Department::getMap(), columns, values);
    ASSERT_EQ(columns, "DeptName, DeptManager, Description");
    ASSERT_EQ(values, "'Engineering', '1000017', 'This department focuses on software development.'");
    std::string query = QueryE::generateInsertQuery(Department::getTableName(), columns, values);
    EXPECT_TRUE(db.executeQueryD(query, true));
}

TEST_F(EngineerFixture, TestProcessPropertyInsertionEngineer) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string columns, values;
    CRUD::InsertHelper::processInsertedProperties<Employee>(engineer, Employee::getMap(), columns, values);
    ASSERT_EQ(columns, "FirstName, MiddleName, LastName, Contact, Email, DOB, JoiningDate, DepartmentID, ReportingManagerID, BaseSalary, PerformanceRating, YearsOfExperience");
    ASSERT_EQ(values, "'Jane', 'Doe', 'Wilson', '987-654-3210', 'jane.wilson@company.com', '01-01-2000', '01-06-2023', '2000003', '1000014', '60000.000000', '4.200000', '5'");

    std::string query = QueryE::generateInsertQuery(Employee::getTableName(), columns, values);
    EXPECT_TRUE(db.executeQueryD(query, true));

    engineer.setEmpId(db.lastInsertedValue());
    columns = "";
    values = "";
    CRUD::InsertHelper::processInsertedProperties<Engineer>(engineer, Engineer::getMap(), columns, values);
    ASSERT_EQ(columns, "EmpId, EngineerSpecialization, CurrentProject");
    std::string check = ("'" + engineer.getEmpId() + "', 'Software Engineer', 'Project X'");
    ASSERT_EQ(values, check);
    query = QueryE::generateInsertQuery(Engineer::getTableName(), columns, values);
    EXPECT_TRUE(db.executeQueryD(query, true));
}
