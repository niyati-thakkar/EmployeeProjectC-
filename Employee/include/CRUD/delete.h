
#ifndef _DELETE_H_
#define _DELETE_H_

#include <string>
#include <vector>
#include <iostream>
#include "crud.h"
#include "select.h"

namespace CRUD {

    namespace DeleteHelper {

        template<typename ParentEntityType, typename ChildEntityType = ParentEntityType>
        bool executeDeleteQuery(Database& db, ChildEntityType& entity, std::string id) {
            auto& propertyMap = ParentEntityType::getMap();
            std::string query = QueryE::generateDeleteQuery(ParentEntityType::getTableName(), propertyMap[1].name, id);
            return db.executeQueryD(query, false);
        }

        inline std::optional<std::string> getDeptManagerWarning(std::string employeeId) {
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            if (auto deptManagerCount = db.valueExistsInTable("Department", "DeptManager", employeeId); deptManagerCount) {
                return "Employee " + employeeId + " is Head of the Department. Respective Department will also be deleted!";
            }
            return std::nullopt;
        }

        inline std::optional<std::string> getReportingManagerWarning(std::string employeeId) {
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            if (auto reportingManagerCount = db.valueExistsInTable("Employee", "ReportingManagerID", employeeId); reportingManagerCount) {
                return "Employee " + employeeId + " is Reporting Manager of " + std::to_string(reportingManagerCount) + " employees. Their Reporting Manager will be changed to NULL!";
            }
            return std::nullopt;
        }

        template<typename ParentEntityType, typename ChildEntityType = ParentEntityType>
        bool deleteGivenEntities(ChildEntityType& entity, const std::vector<std::string>& ids) {
            auto warningDept = [&](std::string id) {
                if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); promptUserForAction("Note that Employees, Engineers, HR, and Managers belonging to this department will also be deleted!")) {
                    return executeDeleteQuery<ParentEntityType, ChildEntityType>(db, entity, id);
                }
                };

            auto warningEmp = [&](std::string id) {
                std::string warning;
                if (auto warningDeptManager = DeleteHelper::getDeptManagerWarning(id); warningDeptManager) {
                    warning += *warningDeptManager + "\n";
                }
                if (auto warningReportingManager = DeleteHelper::getReportingManagerWarning(id); warningReportingManager) {
                    warning += *warningReportingManager + "\n";
                }
                if (Database& db = DatabaseWrapper::getEmployeeDatabaseInstance(); promptUserForAction(warning)) {
                    return executeDeleteQuery<ParentEntityType, ChildEntityType>(db, entity, id);
                }
                };

            if (ParentEntityType::getTableName() == Employee::getTableName()) {
                return applyToAllProperties(entity, ids, size_t{ 0 }, ids.size(), warningEmp);
            }
            if (ParentEntityType::getTableName() == Department::getTableName()) {
                return applyToAllProperties(entity, ids, size_t{ 0 }, ids.size(), warningDept);
            }
            return false;
        }

    }

    namespace Delete {

        template<typename EntityType>
        bool deleteEntity(EntityType& entity) {
            std::optional<std::pair<std::string, int>> entityTableAndIndex;
            int option = Utility::takeOption(true, "Delete by ID", "Delete by column value");
            if (!promptDeleteCriteria(option, entity, entityTableAndIndex) || !entityTableAndIndex.has_value()) {
                Database::logger.Error("Failed to delete!");
                return false;
            }

            std::vector<std::string> IdsList;
            collectEntityIdsFromSingleTable(entity, entityTableAndIndex.value(), IdsList);

            if (DeleteHelper::deleteGivenEntities<EntityType, EntityType>(entity, IdsList)) {
                Database::logger.Info("Successfully Deleted!");
                return true;
            }
            else {
                Database::logger.Error("Failed to delete!");
                return false;
            }
        }

        template<typename ParentEntityType, typename ChildEntityType>
        bool deleteEntitiesWithCascade(ChildEntityType& entity) {
            int option = Utility::takeOption(true, "Delete by EmpID", (std::string{ "Delete by " } + ChildEntityType::getTableName() + " ID"), "Delete by column value");
                std::optional<std::pair<std::string, int>> tableAndIndex;

            if (!promptDeleteCriteriaC<ParentEntityType, ChildEntityType>(option, entity, tableAndIndex) || !tableAndIndex.has_value()) {
                Database::logger.Error("Failed to delete!");
                return false;
            }
            std::vector<std::string> IdsList;
            collectEntityIdsFromJoinTables<ParentEntityType, ChildEntityType>(entity, tableAndIndex.value(), IdsList);
            if (DeleteHelper::deleteGivenEntities<ParentEntityType, ChildEntityType>(entity, IdsList)) {
                Database::logger.Info("Successfully Deleted!");
                return true;
            }
            else {
                Database::logger.Error("Failed to delete!");
                return false;
            }
        }
    }
}
#endif
