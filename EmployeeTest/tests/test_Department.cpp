#include "pch.h"
#include "DepartmentFixture.h"

TEST_F(DepartmentFixture, GetDeptNameTest) {
    EXPECT_EQ(department.getDeptName(), "Engineering");
}

TEST_F(DepartmentFixture, GetDeptManagerIdTest) {
    EXPECT_EQ(department.getDeptManagerId(), "1000017");
}

TEST_F(DepartmentFixture, GetDescriptionTest) {
    EXPECT_EQ(department.getDescription(), "This department focuses on software development.");
}

TEST_F(DepartmentFixture, SetIDValidTest) {
    EXPECT_TRUE(department.setid("2000002"));
    EXPECT_EQ(department.getid(), "2000002");
}

TEST_F(DepartmentFixture, SetIDInvalidTest) {
    EXPECT_FALSE(department.setid("invalid_id"));
}

TEST_F(DepartmentFixture, SetDeptNameValidTest) {
    EXPECT_TRUE(department.setDeptName("Software Development"));
    EXPECT_EQ(department.getDeptName(), "Software Development");
}

TEST_F(DepartmentFixture, SetDeptNameInvalidTest) {
    EXPECT_FALSE(department.setDeptName(""));
}

TEST_F(DepartmentFixture, SetDeptManagerIdValidTest) {
    EXPECT_TRUE(department.setDeptManagerId("1000002"));
    EXPECT_EQ(department.getDeptManagerId(), "1000002");
}

TEST_F(DepartmentFixture, SetDeptManagerIdInvalidTest) {
    EXPECT_FALSE(department.setDeptManagerId("invalid_id"));
}

TEST_F(DepartmentFixture, SetDescriptionValidTest) {
    EXPECT_TRUE(department.setDescription("This department focuses on various engineering disciplines."));
    EXPECT_EQ(department.getDescription(), "This department focuses on various engineering disciplines.");
}

TEST_F(DepartmentFixture, SetDescriptionInvalidTest) {
    EXPECT_FALSE(department.setDescription(""));
}
