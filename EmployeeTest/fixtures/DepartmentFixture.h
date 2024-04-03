#include "pch.h"
#ifndef _DepartmentFixture_H_
#define _DepartmentFixture_H_

#include "gtest/gtest.h"
#include "Department.h"
#include "Query.h"

class DepartmentFixture : public ::testing::Test {
protected:
    void SetUp() override {
        department.setDeptName("Engineering");
        department.setDeptManagerId("1000017");
        department.setDescription("This department focuses on software development.");
    }
    void TearDown() override {
        Database& db = DatabaseWrapper::getDemoDatabaseInstance();
        db.executeQueryD(QueryE::generateDeleteQuery("DEPARTMENT", "DeptManager", department.getDeptManagerId()), false);
    }
    Department department;
};

#endif
