#include "pch.h"
#include "EngineerFixture.h"

TEST_F(EngineerFixture, GetEngineerSpecializationTest) {
    EXPECT_EQ(engineer.getEngineerSpecialization(), "Software Engineer");
}

TEST_F(EngineerFixture, GetCurrentProjectTest) {
    EXPECT_EQ(engineer.getCurrentProject(), "Project X");
}

TEST_F(EngineerFixture, SetIDValidTest) {
    EXPECT_TRUE(engineer.setid("4000002"));
    EXPECT_EQ(engineer.getid(), "4000002");
}

TEST_F(EngineerFixture, SetIDInvalidTest) {
    EXPECT_FALSE(engineer.setid("invalid_id"));
}

TEST_F(EngineerFixture, SetEmpIdValidTest) {
    EXPECT_TRUE(engineer.setEmpId("1000008"));
    EXPECT_EQ(engineer.getEmpId(), "1000008");
}

TEST_F(EngineerFixture, SetInvalidDataTest) {
    EXPECT_FALSE(engineer.setEngineerSpecialization(""));
    EXPECT_FALSE(engineer.setCurrentProject(""));
}

TEST_F(EngineerFixture, CalculateSalaryTest) {
    EXPECT_TRUE(engineer.setBaseSalary("60000"));
    EXPECT_TRUE(engineer.setPerformanceRating("4"));
    EXPECT_TRUE(engineer.setYearsOfExperience("5"));
    EXPECT_DOUBLE_EQ(engineer.calculateSalary(), 5000 + 60000 + 4 * 4 * 60000 / 100 + 5 * 9.0 * 60000 / 100);
}
