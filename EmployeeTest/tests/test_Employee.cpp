#include "pch.h"
#include "EmployeeFixture.h"

TEST_F(EmployeeFixture, GetNameTest) {
    EXPECT_EQ(emp.getFname(), "John");
    EXPECT_EQ(emp.getMname(), "Doe");
    EXPECT_EQ(emp.getLname(), "Smith");
}

TEST_F(EmployeeFixture, GetContactTest) {
    EXPECT_EQ(emp.getContact(), "123-456-7890");
}

TEST_F(EmployeeFixture, GetEmailTest) {
    EXPECT_EQ(emp.getEmail(), "john@example.com");
}

TEST_F(EmployeeFixture, GetDateTest) {
    EXPECT_EQ(emp.getDOB(), "12-02-2024");
    EXPECT_EQ(emp.getJoiningDate(), "12-02-2024");
}

TEST_F(EmployeeFixture, GetIDFieldsTest) {
    EXPECT_EQ(emp.getDeptId(), "2000002");
    EXPECT_EQ(emp.getReportingManagerId(), "");
}

TEST_F(EmployeeFixture, GetSalaryComponentsTest) {
    EXPECT_EQ(emp.getBaseSalary(), "60000.000000");
    EXPECT_EQ(emp.getPerformanceRating(), "3.800000");
    EXPECT_EQ(emp.getYearsOfExperience(), "8");
}

TEST_F(EmployeeFixture, SetIDValidTest) {
    EXPECT_TRUE(emp.setid("1000011"));
    EXPECT_EQ(emp.getid(), "1000011");
}

TEST_F(EmployeeFixture, SetIDInvalidTest) {
    EXPECT_FALSE(emp.setid("invalid_id"));
}

TEST_F(EmployeeFixture, SetNameTest) {
    EXPECT_TRUE(emp.setFname("Jane"));
    EXPECT_TRUE(emp.setMname("#"));
    EXPECT_TRUE(emp.setLname("Doe"));
}

TEST_F(EmployeeFixture, SetContactValidTest) {
    EXPECT_TRUE(emp.setContact("555-123-4567"));
}

TEST_F(EmployeeFixture, SetContactInvalidTest) {
    EXPECT_FALSE(emp.setContact("invalid_contact"));
}

TEST_F(EmployeeFixture, SetEmailValidTest) {
    EXPECT_TRUE(emp.setEmail("jane.doe@company.com"));
}

TEST_F(EmployeeFixture, SetEmailInvalidTest) {
    EXPECT_FALSE(emp.setEmail("invalid_email"));
}

TEST_F(EmployeeFixture, SetDateTest) {
    EXPECT_TRUE(emp.setDOB("31-12-2020"));
    EXPECT_TRUE(emp.setJoiningDate("31-12-2020"));
}

TEST_F(EmployeeFixture, SetIDFieldsValidTest) {
    EXPECT_TRUE(emp.setDeptId("2000003"));
    EXPECT_TRUE(emp.setReportingManagerId("#"));
}

TEST_F(EmployeeFixture, SetSalaryComponentsTest) {
    EXPECT_TRUE(emp.setBaseSalary("50000"));
    EXPECT_TRUE(emp.setPerformanceRating("4.6"));
    EXPECT_TRUE(emp.setYearsOfExperience("3"));
}
