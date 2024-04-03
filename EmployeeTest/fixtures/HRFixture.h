#include "pch.h"
#include "HR.h"
#include "Employee.h"
#include "Query.h"
#ifndef _HRFixture_H_
#define _HRFixture_H_

class HRFixture : public ::testing::Test {
protected:
    void SetUp() override {
        hr.setFname("Sarah");
        hr.setMname("Kim");
        hr.setLname("Wong");
        hr.setContact("444-888-9999");
        hr.setEmail("sarah.wong@company.com");
        hr.setDOB("1990-10-15");
        hr.setJoiningDate("2021-06-15");
        hr.setDeptId("2000002");
        hr.setReportingManagerId("1000019");
        hr.setBaseSalary("70000");
        hr.setPerformanceRating("4.0");
        hr.setYearsOfExperience("8");

        hr.setid("5000002");
        hr.setEmpId("1000002");
        hr.setProficientLanguage("Spanish Mandarin");
        hr.setRecruitingExperience("3");
    }

    void TearDown() override {
        Database& db = DatabaseWrapper::getDemoDatabaseInstance();
        db.executeQueryD(QueryE::generateDeleteQuery("Employee", "contact", "444-888-9999"), false);
    }

    HR hr;
};

#endif
