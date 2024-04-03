#include "pch.h"
#include "Query.h"
#include "update.h"
#include "HRfixture.h"

TEST_F(HRFixture, UpdateSuccess) {
    std::string updateQuery = "UPDATE HR SET ProficientLanguage='Spanish' WHERE HRID='5000001';";
    bool updateSuccess = CRUD::UpdateHelper::performUpdate(updateQuery);
    ASSERT_TRUE(updateSuccess);

    updateQuery = "UPDATE HR SET ProficientLanguage='English' WHERE HRID='5000001';";
    CRUD::UpdateHelper::performUpdate(updateQuery);
}

TEST_F(HRFixture, UpdateFailure) {
    std::string invalidQuery = "Invalid SQL Statement";
    bool updateSuccess = CRUD::UpdateHelper::performUpdate(invalidQuery);
    ASSERT_FALSE(updateSuccess);
}

TEST_F(HRFixture, UpdateSingleHRByID) {
    std::string updateCol = "ProficientLanguage = 'French'";
    std::vector<std::string> IDs = { "1000004" };
    bool updateSuccess = CRUD::UpdateHelper::updateByID(DatabaseWrapper::getEmployeeDatabaseInstance(), HR::getTableName(), updateCol, "EmpId", IDs);
    ASSERT_TRUE(updateSuccess);
}

TEST_F(HRFixture, UpdateMultipleHRsByID) {
    std::string updateCol = "RecruitingExperience = '4'";
    std::vector<std::string> IDs = { "1000001", "1000002" };
    bool updateSuccess = CRUD::UpdateHelper::updateByID(DatabaseWrapper::getEmployeeDatabaseInstance(), HR::getTableName(), updateCol, "EmpId", IDs);
    ASSERT_TRUE(updateSuccess);
}

TEST_F(HRFixture, UpdateByIDEmptyList) {
    std::string updateCol = "BaseSalary";
    std::string newValue = "80000";
    std::vector<std::string> emptyList;
}
