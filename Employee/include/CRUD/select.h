#ifndef _SELECT_H_
#define _SELECT_H_

#include <string>
#include <optional>
#include <vector>
#include "crud.h"

namespace CRUD {

    namespace SelectHelper {
        template<typename EntityType>
        bool promptSelectCriteria(EntityType& entity, std::optional<std::pair<std::string, int>>& entityTableAndIndex) {
            int option = Utility::takeOption(true, "View Entire Table", "View by ID", "View by column value");
            std::string tableName = EntityType::getTableName();
            auto& propertyMap = EntityType::getMap();
            switch (option) {
            case 0:
                return false;
            case 1: {
                return true;
            }
            case 2: {
                entityTableAndIndex = std::make_pair(tableName, 1);
                break;
            }
            case 3: {
                entityTableAndIndex = selectPropertyIndex(entity, propertyMap, {});
                break;
            }
            }
            if (entityTableAndIndex.has_value())
                return Utility::getUserInput(entity, propertyMap[entityTableAndIndex.value().second]);
            return true;
        }

        template<typename ParentEntityType, typename ChildEntityType>
        bool promptSelectCriteriaC(ChildEntityType& e, std::optional<std::pair<std::string, int>>& entityTableAndIndex) {
            int option = Utility::takeOption(true, "View Entire Table", "View by EmpID", (std::string{ "view by " } + ChildEntityType::getTableName() + " ID"), "View by column value");
            auto& mapParent = ParentEntityType::getMap();
            auto& mapChild = ChildEntityType::getMap();
            std::string childTableName = ChildEntityType::getTableName();
            std::string parentTableName = ParentEntityType::getTableName();
            switch (option) {
            case 0:
                return false;
            case 1: {
                break;
            }
            case 2: {
                entityTableAndIndex = std::make_pair(childTableName, 0);
                break;
            }
            case 3: {
                entityTableAndIndex = std::make_pair(childTableName, 1);
                break;
            }
            case 4: {
                entityTableAndIndex = selectPropertyIndex<ParentEntityType, ChildEntityType>(e, mapParent, std::optional{ mapChild });
                break;
            }
            }

            if (entityTableAndIndex.has_value()) {
                if (entityTableAndIndex.value().first == parentTableName)
                    return Utility::getUserInput(e, mapParent[entityTableAndIndex.value().second]);

                if (entityTableAndIndex.value().first == childTableName)
                    return Utility::getUserInput(e, mapChild[entityTableAndIndex.value().second]);
            }
            return true;
        }

        inline bool promptUserForAction(std::string option1, std::string option2) {
            int userInput = Utility::takeOption(false, option1, option2);
            return userInput == 1;
        }

        inline bool performSelect(Database& db, std::string query) {
            return db.selectQueryD(query);
        }

        template<typename T1>
        void viewHelper(T1& e, bool selectAllColumns, std::string table, std::map<int, PropertyMap<T1>>& map, size_t lastkey, std::string& cols) {
            auto addColumn = [&](PropertyMap<T1>& mapp) {
                cols = cols + table + "." + mapp.name + ", ";
                return true;
                };
            auto selectColumn = [&](PropertyMap<T1>& mapp) {
                int opt = promptUserForAction("Select " + mapp.name, "Discard " + mapp.name);
                if (opt == 1) {
                    cols = cols + table + "." + mapp.name + ", ";
                }
                return true;
                };
            if (selectAllColumns) {
                applyToAllProperties<T1>(e, map, 1, T1::getLastKey() + 1, addColumn);
            }
            else {
                applyToAllProperties<T1>(e, map, 1, T1::getLastKey() + 1, selectColumn);
            }
            if (cols.length() > 2) {
                cols.pop_back();
                cols.pop_back();
            }
        }
    }

    namespace Select {
        template<typename T1>
        bool view(T1& e) {
            std::string tableName = T1::getTableName();
            auto& map = T1::getMap();

            std::optional<std::pair<std::string, int>> entityTableAndIndex;
            if (!SelectHelper::promptSelectCriteria(e, entityTableAndIndex)) {
                Database::logger.Error("Unable to Fetch Data!");
                return false;
            }

            bool allColumns = promptUserForAction("View All Columns", "View Selected Columns");
            std::string cols = "";
            SelectHelper::viewHelper<T1>(e, allColumns, tableName, map, T1::getLastKey(), cols);

            std::string query;
            if (entityTableAndIndex.has_value()) {
                auto index = entityTableAndIndex.value().second;
                query = QueryE::generateSelectQuery(tableName, cols, map[index].name, (e.*map[index].getter)());
            }
            else {
                query = QueryE::generateSelectQuery(tableName, cols, "", "");
            }

            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            if (SelectHelper::performSelect(db, query)) {
                Database::logger.Info("Successfully Fetched!");
                return true;
            }

            Database::logger.Error("Failed to Fetch Data!");
            return false;
        }

        template<typename T1, typename T2>
        bool viewC(T2& e) {
            std::string tableName1 = T1::getTableName();
            auto& map1 = T1::getMap();
            std::string tableName2 = T2::getTableName();
            auto& map2 = T2::getMap();

            std::optional<std::pair<std::string, int>> entityTableAndIndex;
            if (!SelectHelper::promptSelectCriteriaC<T1, T2>(e, entityTableAndIndex)) {
                Database::logger.Error("Unable to Fetch Data!");
                return false;
            }

            bool allColumns = promptUserForAction("View All Columns", "View Selected Columns");
            std::string cols = "";
            SelectHelper::viewHelper<T1>(e, allColumns, tableName1, map1, T1::getLastKey(), cols);
            cols += ", ";
            SelectHelper::viewHelper<T2>(e, allColumns, tableName2, map2, T2::getLastKey(), cols);

            if (cols.length() == 0) {
                Database::logger.Error("No columns Selected!");
                return false;
            }

            std::string query;
            if (entityTableAndIndex.has_value()) {
                std::string colname, value, tname;
                if (entityTableAndIndex.value().first == tableName1) {
                    tname = tableName1;
                    colname = map1[entityTableAndIndex.value().second].name;
                    value = (e.*map1[entityTableAndIndex.value().second].getter)();
                }
                else {
                    tname = tableName2;
                    colname = map2[entityTableAndIndex.value().second].name;
                    value = (e.*map2[entityTableAndIndex.value().second].getter)();
                }
                query = QueryE::generateSelectQuery(tableName1, tableName2, map1[1].name, map2[0].name, cols, tname, colname, value);
            }
            else {
                query = QueryE::generateSelectQuery(tableName1, tableName2, map1[1].name, map2[0].name, cols, "", "", "");
            }
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            if (SelectHelper::performSelect(db, query)) {
                Database::logger.Info("Successfully Fetched!");
                return true;
            }
            Database::logger.Error("Failed to Fetch Data!");
            return false;
        }
    }
}

#endif
