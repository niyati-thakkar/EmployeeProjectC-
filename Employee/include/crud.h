#ifndef _CRUD_H_
#define _CRUD_H_

#include "Query.h"
#include "Utility.h"
#include <string>
#include <optional>
#include <map>
#include <vector>
#include <type_traits>
#include <utility>

namespace CRUD {

    inline static std::string isOpt = " (Note - This field is optional. Enter '#' to keep it blank!)";
    inline static std::string INVALID_INPUT_MSG = "Invalid Input!";
    inline static std::string valuenotexits = "Value doesn't exist!";
    inline static std::string someerror = "Sorry! Some error occurred!";

    template<typename T1>
    void clear(T1& e) {
        e = T1{};
    }

    template<typename T1, typename I, typename Function>
    bool applyToAllProperties(T1& entity, I& iterable, size_t startIdx, size_t endIdx, Function f) {
        for (auto i = startIdx; i < endIdx; ++i) {
            if (!f(iterable[i])) {
                return false;
            }
        }
        return true;
    }

    template<typename T1, typename T2 = T1>
    std::optional<std::pair<std::string, int>> selectPropertyIndex(T2& e, std::map<int, PropertyMap<T1>>& map1, std::optional<std::map<int, PropertyMap<T2>>> map2) {
        int i = 1;
        auto printMap1 = [&](const PropertyMap<T1>& property) { std::cout << i++ << ". " << property.name << "\n"; return true; };
        applyToAllProperties(e, map1, 2, T1::getLastKey() + 1, printMap1);
        if (map2.has_value()) {
            auto printMap2 = [&](const PropertyMap<T2>& property) { std::cout << i++ << ". " << property.name << "\n"; return true; };
            applyToAllProperties(e, map2.value(), 2, T2::getLastKey() + 1, printMap2);
        }

        int selection;
        if (Utility::setInput(selection) && (0 < selection < i)) {
            if (selection < T1::getLastKey()) {
                return std::make_pair(T1::getTableName(), selection + 1);
            }
            else if (map2.has_value()) {
                selection = selection - T1::getLastKey() + 2;
                return std::make_pair(T2::getTableName(), selection);
            }
        }
        return std::nullopt;
    }

    template<typename EntityType>
    bool promptDeleteCriteria(int option, EntityType& entity, std::optional<std::pair<std::string, int>>& entityTableAndIndex) {
        std::string tableName = EntityType::getTableName();
        auto& propertyMap = EntityType::getMap();
        switch (option) {
        case 0:
            return false;
        case 1: {
            entityTableAndIndex = std::make_pair(tableName, 1);
            break;
        }
        case 2: {
            entityTableAndIndex = selectPropertyIndex(entity, propertyMap, {});
            break;
        }
        }
        if (entityTableAndIndex.has_value())
            return Utility::getUserInput(entity, propertyMap[entityTableAndIndex.value().second]);
        return false;
    }

    template<typename ParentEntityType, typename ChildEntityType>
    bool promptDeleteCriteriaC(int option, ChildEntityType& e, std::optional<std::pair<std::string, int>>& entityTableAndIndex) {

        auto& mapParent = ParentEntityType::getMap();
        auto& mapChild = ChildEntityType::getMap();
        std::string childTableName = ChildEntityType::getTableName();
        std::string parentTableName = ParentEntityType::getTableName();
        switch (option) {
        case 0: {
            return false;
        }
        case 1: {
            entityTableAndIndex = std::make_pair(childTableName, 0);
            break;
        }
        case 2: {
            entityTableAndIndex = std::make_pair(childTableName, 1);
            break;
        }
        case 3: {
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
        return false;
    }

    inline bool promptUserForAction(std::string warningMessage) {
        if (warningMessage.empty())
            return true;
        Database::logger.Warn(warningMessage);
        int userInput = Utility::takeOption(false, "Yes, Proceed!", "No, Go back to Previous Menu!");
        return userInput == 1;
    }

    inline bool promptUserForAction(std::string option1, std::string option2) {
        int userInput = Utility::takeOption(false, option1, option2);
        return userInput == 1;
    }

    template<typename T1, typename T2 = T1>
    void storeToObject(T2& e) {
        std::string id = e.getid();
        auto& tmap = T2::getMap();
        if constexpr (!std::is_same_v<std::decay_t<T1>, T2>) {
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            id = (db.getColValue(e.getTableName(), tmap[1].name, id, tmap[0].name));
        }
        auto& map = T1::getMap();

        for (int i = 2; i <= T1::getLastKey(); i++) {
            Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
            (e.*map[i].setter)(db.getColValue(T1::getTableName(), map[1].name, id, map[i].name));
        }
    }

    template<typename EntityType>
    void collectEntityIdsFromSingleTable(EntityType& entity, std::pair<std::string, int>& tableAndIndex, std::vector<std::string>& IdsList) {
        auto& propertyMap = EntityType::getMap();
        std::string id = (entity.*propertyMap[tableAndIndex.second].getter)();
        std::string query = QueryE::generateSelectQuery(EntityType::getTableName(), propertyMap[1].name, propertyMap[tableAndIndex.second].name, id);
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        db.getPrimaryKeys(query, IdsList);
    }

    template<typename ParentEntityType, typename ChildEntityType>
    void collectEntityIdsFromJoinTables(ChildEntityType& e, std::pair<std::string, int> tableAndIndex, std::vector<std::string>& IdsList) {
        std::string parentTableName = ParentEntityType::getTableName();
        std::string childTableName = ChildEntityType::getTableName();
        auto& parentMap = ParentEntityType::getMap();
        auto& childMap = ChildEntityType::getMap();

        std::string tablename = parentTableName + " JOIN " + childTableName + " ON " + parentTableName + "." + parentMap[1].name + " = " + childTableName + "." + childMap[0].name;
        std::string columns = childTableName + "." + childMap[0].name;
        std::string colname, value;
        if (tableAndIndex.first == parentTableName) {
            colname = parentTableName + "." + parentMap[tableAndIndex.second].name;
            value = (e.*parentMap[tableAndIndex.second].getter)();
        }
        else {
            colname = childTableName + "." + childMap[tableAndIndex.second].name;
            value = (e.*childMap[tableAndIndex.second].getter)();
        }
        std::string query = QueryE::generateSelectQuery(tablename, columns, colname, value);
        Database& db = DatabaseWrapper::getEmployeeDatabaseInstance();
        db.getPrimaryKeys(query, IdsList);
    }

} // namespace CRUD

#endif // _CRUD_H_
