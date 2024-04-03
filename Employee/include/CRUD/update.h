#ifndef _UPDATE_H_
#define _UPDATE_H_

#pragma once
#include <string>
#include "crud.h"

namespace CRUD {
    inline namespace UpdateHelper {
        template<typename T1, typename T2 = T1>
        bool updateHelper(T2& e, std::map<int, PropertyMap<T1>>& map, std::string& toUpdate) {

            auto update = [&](PropertyMap<T1> map) {
                if (promptUserForAction(("Update " + map.name), ("Discard " + map.name))) {
                    if (Utility::getUserInput(e, map)) {
                        toUpdate = toUpdate + map.name + " = '" + (e.*map.getter)() + "', ";
                        return true;
                    }
                }
                else {
                    return true;
                }
                return false;
                };
            bool applied = applyToAllProperties(e, map, 2, T1::getLastKey() + 1, update);
            if (toUpdate.length() > 2) {
                toUpdate.pop_back();
                toUpdate.pop_back();
            }
            return applied;
        }
        bool performUpdate(std::string query) {
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            return db.executeQueryD(query, false);
        }
        bool updateByID(Database& db, std::string tablename, std::string& toUpdate, std::string colname, std::vector<std::string>& IdsList) {

            auto update = [&](std::string id) {
                std::string query = QueryE::generateUpdateQuery(tablename, toUpdate, colname, id);
                return performUpdate(query);
                };
            int i = 0;
            return CRUD::applyToAllProperties(i, IdsList, 0, IdsList.size(), update);
        }
    }
    inline namespace Update {
        template<typename EntityType>
        bool updateEntity(EntityType& entity) {
            std::optional<std::pair<std::string, int>> entityTableAndIndex = std::nullopt;
            int option = Utility::takeOption(true, "Update by ID", "Update by column value");
            auto& map = EntityType::getMap();

            std::string toUpdate = "";
            std::string colname, value;
            if (promptDeleteCriteria(option, entity, entityTableAndIndex) && entityTableAndIndex.has_value()) {
                int index = entityTableAndIndex.value().second;
                colname = map[index].name;
                value = (entity.*map[index].getter)();
            }
            else {
                Database::logger.Error("Failed to Update!");
                return false;
            }
            if (!updateHelper<EntityType, EntityType>(entity, EntityType::getMap(), toUpdate) || toUpdate.length() == 0) {
                Database::logger.Error("Failed to Update!");
                return false;
            }

            std::string query = QueryE::generateUpdateQuery(EntityType::getTableName(), toUpdate, colname, value);

            if (performUpdate(query)) {
                Database::logger.Info("Successfully Update!");
                return true;
            }
            else {
                Database::logger.Error("Failed to Update!");
                return false;
            }
        }

        template<typename ParentEntityType, typename ChildEntityType>
        bool updateEntitiesWithCascade(ChildEntityType& entity) {
            int option = Utility::takeOption(true, "Update by EmpID", (std::string{ "Update by " } + ChildEntityType::getTableName() + " ID"), "Update by column value");
            std::optional<std::pair<std::string, int>> tableAndIndex;

            if (!promptDeleteCriteriaC<ParentEntityType, ChildEntityType>(option, entity, tableAndIndex) || !tableAndIndex.has_value()) {
                Database::logger.Error("Failed to delete!");
                return false;
            }
            std::vector<std::string> IdsList;
            collectEntityIdsFromJoinTables<ParentEntityType, ChildEntityType>(entity, tableAndIndex.value(), IdsList);
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            db.startTransaction();
            bool updated = true;
            std::string toUpdate = "";
            if (updateHelper(entity, ParentEntityType::getMap(), toUpdate)) {
                updated = updateByID(db, ParentEntityType::getTableName(), toUpdate, ParentEntityType::getMap()[1].name, IdsList);
            }
            toUpdate = "";
            if (updateHelper(entity, ChildEntityType::getMap(), toUpdate)) {
                updated = updated && UpdateHelper::updateByID(db, ChildEntityType::getTableName(), toUpdate, ChildEntityType::getMap()[0].name, IdsList);
            }
            if (updated) {
                db.commitTransaction();
                Database::logger.Info("Successfully Update!");
                return true;
            }
            db.rollbackTransaction();
            Database::logger.Error("Failed to delete!");
            return false;
        }
    }
}
#endif
