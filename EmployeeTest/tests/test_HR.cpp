#include "pch.h"
#include "HRFixture.h"

TEST_F(HRFixture, GetProficientLangugaeTest) {
    EXPECT_EQ(hr.getProficientLanguage(), "Spanish Mandarin");
}

TEST_F(HRFixture, GetRecruitingExperienceTest) {
    EXPECT_EQ(hr.getRecruitingExperience(), "3");
}

TEST_F(HRFixture, SetIDValidTest) {
    EXPECT_TRUE(hr.setid("5000002"));
    EXPECT_EQ(hr.getid(), "5000002");
}

TEST_F(HRFixture, SetIDInvalidTest) {
    EXPECT_FALSE(hr.setid("invalid_id"));
}

TEST_F(HRFixture, SetEmpIdValidTest) {
    EXPECT_TRUE(hr.setEmpId("1000004"));
    EXPECT_EQ(hr.getEmpId(), "1000004");
}

TEST_F(HRFixture, SetProficientLangugaeValidTest) {
    EXPECT_TRUE(hr.setProficientLanguage("Spanish German"));
    EXPECT_EQ(hr.getProficientLanguage(), "Spanish German");
}

TEST_F(HRFixture, SetProficientLangugaeInvalidTest) {
    EXPECT_FALSE(hr.setProficientLanguage(""));
}

TEST_F(HRFixture, SetRecruitingExperienceValidTest) {
    EXPECT_TRUE(hr.setRecruitingExperience("4"));
    EXPECT_EQ(hr.getRecruitingExperience(), "4");
}

TEST_F(HRFixture, SetRecruitingExperienceInvalidTest) {
    EXPECT_FALSE(hr.setRecruitingExperience("invalid_data"));
}

TEST_F(HRFixture, CalculateSalaryTest) {
    EXPECT_TRUE(hr.setBaseSalary("80000"));
    EXPECT_TRUE(hr.setPerformanceRating("4.2"));
    EXPECT_TRUE(hr.setYearsOfExperience("8"));
    EXPECT_DOUBLE_EQ(hr.calculateSalary(), 5000 + 80000 + 4 * 4.2 * 80000 / 100 + 8 * 8.0 * 80000 / 100);
}
