#include "pch.h"

#include "ManagerFixture.h"

TEST_F(ManagerFixture, GetManagerSpecializationTest) {
    EXPECT_EQ(manager.getManagerSpecialization(), "Marketing Management");
}

TEST_F(ManagerFixture, GetYearsOfManagementExperienceTest) {
    EXPECT_EQ(manager.getYearsOfManagementExperience(), "5");
}

TEST_F(ManagerFixture, SetIDValidTest) {
    EXPECT_TRUE(manager.setid("3000001")); // Replace with a valid, different ID
    EXPECT_EQ(manager.getid(), "3000001");
}

TEST_F(ManagerFixture, SetIDInvalidTest) {
    EXPECT_FALSE(manager.setid("invalid_id"));
}

TEST_F(ManagerFixture, SetEmpIdValidTest) {
    EXPECT_TRUE(manager.setEmpId("1000015")); // Replace with a valid, different employee ID
    EXPECT_EQ(manager.getEmpId(), "1000015");
}

TEST_F(ManagerFixture, SetManagerSpecializationValidTest) {
    EXPECT_TRUE(manager.setManagerSpecialization("Software Development Management"));
    EXPECT_EQ(manager.getManagerSpecialization(), "Software Development Management");
}

TEST_F(ManagerFixture, SetManagerSpecializationInvalidTest) {
    EXPECT_FALSE(manager.setManagerSpecialization(""));
}

TEST_F(ManagerFixture, SetYearsOfManagementExperienceValidTest) {
    EXPECT_TRUE(manager.setYearsOfManagementExperience("5"));
    EXPECT_EQ(manager.getYearsOfManagementExperience(), "5");
}

TEST_F(ManagerFixture, SetYearsOfManagementExperienceInvalidTest) {
    EXPECT_FALSE(manager.setYearsOfManagementExperience("invalid_data"));
}

TEST_F(ManagerFixture, CalculateSalaryTest) {
    EXPECT_TRUE(manager.setBaseSalary("75000"));
    EXPECT_TRUE(manager.setPerformanceRating("4.6"));
    EXPECT_TRUE(manager.setYearsOfExperience("3"));
    EXPECT_DOUBLE_EQ(manager.calculateSalary(), 5000 + 75000 + 4.6 * 4 * 75000 / 100 + 3 * 10.0 * 75000 / 100);
}
