#include "pch.h"
#include "Engineer.h"
#include "Query.h"
#ifndef _EngineerFixture_H_
#define _EngineerFixture_H_
class EngineerFixture : public ::testing::Test {
protected:
    void SetUp() override {
        engineer.setFname("Jane");
        engineer.setMname("Doe");
        engineer.setLname("Wilson");
        engineer.setContact("987-654-3210");
        engineer.setEmail("jane.wilson@company.com");
        engineer.setDOB("01-01-2000");
        engineer.setJoiningDate("01-06-2023");
        engineer.setDeptId("2000003");
        engineer.setReportingManagerId("1000014");
        engineer.setBaseSalary("75000");
        engineer.setPerformanceRating("4.2");
        engineer.setYearsOfExperience("5");
        engineer.setEngineerSpecialization("Software Engineer");
        engineer.setCurrentProject("Project X");
        engineer.setBaseSalary("60000");
        engineer.setYearsOfExperience("5");
    }
    void TearDown() override {
        Database& db = DatabaseWrapper::getDemoDatabaseInstance();
        db.executeQueryD(QueryE::generateDeleteQuery("Employee", "contact", "987-654-3210"), false);
    }

    Engineer engineer;
};
#endif
