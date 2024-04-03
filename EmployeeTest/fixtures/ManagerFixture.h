#include "pch.h"
#include "Manager.h"
#include "Query.h"
#ifndef _ManagerFixture_H_
#define _ManagerFixture_H_

class ManagerFixture : public ::testing::Test {
protected:
    void SetUp() override {
        manager.setFname("Mark");
        manager.setMname("Lee");
        manager.setLname("Brown");
        manager.setContact("555-123-4567");
        manager.setEmail("mark.brown@company.com");
        manager.setDOB("1985-03-21");
        manager.setJoiningDate("2022-09-01");
        manager.setDeptId("4000004");
        manager.setReportingManagerId("1000456");
        manager.setBaseSalary("90000");
        manager.setPerformanceRating("4.5");
        manager.setYearsOfExperience("12");

        manager.setid("3000002");
        manager.setEmpId("1000114");
        manager.setManagerSpecialization("Marketing Management");
        manager.setYearsOfManagementExperience("5");
    }

    void TearDown() override {
        Database& db = DatabaseWrapper::getDemoDatabaseInstance();
        db.executeQueryD(QueryE::generateDeleteQuery("Employee", "contact", "555-123-4567"), false);
    }

    Manager manager;
};

#endif
