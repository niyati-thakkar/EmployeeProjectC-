#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <iostream>

namespace QueryE {
    inline std::string generateWhereQuery(std::string colname, std::string colval) {
        if (colname == "" || colval == "") {
            return "";
        }
        return " WHERE " + colname + " = '" + colval + "'";
    }

    inline std::string generateUpdateQuery(std::string tablename, std::string toUpdate,
        std::string colname, std::string colval) {
        if (colname == "" || colval == "") {
            return "";
        }
        std::string wherequery = generateWhereQuery(colname, colval);
        return "UPDATE " + tablename + " SET " + toUpdate + wherequery + ";";
    }

    inline std::string generateSelectQuery(std::string tablename, std::string columns,
        std::string colname = "", std::string colval = "") {
        std::string wherequery = generateWhereQuery(colname, colval);
        if (columns == "") {
            std::cout << "No Columns Selected!";
            return "";
        }
        return "SELECT " + columns + " FROM " + tablename + wherequery + ";";
    }

    inline std::string generateSelectQuery(std::string tablename1, std::string tablename2,
        std::string colname1, std::string colname2,
        std::string columns, std::string tname,
        std::string colname = "", std::string colval = "") {
        colname = tname + "." + colname;
        std::string wherequery = generateWhereQuery(colname, colval);
        if (columns == "") {
            std::cout << "No Columns Selected!";
            return "";
        }
        return "SELECT " + columns + " FROM " + tablename1 + " JOIN " + tablename2 +
            " ON " + tablename1 + "." + colname1 + " = " + tablename2 + "." + colname2 +
            wherequery + ";";
    }

    inline std::string generateInsertQuery(std::string tablename, std::string columns,
        std::string values) {
        if (tablename == "" || columns == "" || values == "") return "";
        return "INSERT INTO " + tablename + " (" + columns + ") VALUES (" + values + "); ";
    }

    inline std::string generateDeleteQuery(std::string tablename, std::string colname,
        std::string colval) {
        if (colname == "" || colval == "") {
            return "";
        }
        std::string wherequery = generateWhereQuery(colname, colval);
        return "DELETE FROM " + tablename + wherequery + ";";
    }
}

#endif
