#include "pch.h"
#include "delete.h"

TEST(WarningMessageTest, DeptManagerExists) {
	std::string employeeId = "1000011";

	auto warning = CRUD::DeleteHelper::getDeptManagerWarning(employeeId);
	ASSERT_TRUE(warning.has_value());
	EXPECT_EQ(warning.value(), "Employee " + employeeId + " is Head of the Department. Respective Department will also be deleted!");
}

TEST(WarningMessageTest, DeptManagerNonexistent) {
	std::string employeeId = "23423412";

	auto warning = CRUD::DeleteHelper::getReportingManagerWarning(employeeId);
	ASSERT_FALSE(warning.has_value());
}

