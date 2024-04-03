#include "pch.h"
#include "DatabaseWrapper.h"

TEST(DatabaseWrapperTest, selectQueryDWithDemoDBTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string query = "SELECT * FROM Employee";

    bool result = db.selectQueryD(query);

    ASSERT_TRUE(result);
}

TEST(DatabaseWrapperTest, CreateTableTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();

    std::string create_table = "CREATE TABLE IF NOT EXISTS TestTable (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)";

    ASSERT_TRUE(db.executeQueryD(create_table, false));
}

TEST(DatabaseWrapperTest, InsertDataTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string name = "Test Name";

    std::string insert_query = "INSERT INTO TestTable (name) VALUES ('" + name + "')";

    ASSERT_TRUE(db.executeQueryD(insert_query, false));
}

TEST(DatabaseWrapperTest, ValueExistsTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string table_name = "TestTable";
    std::string col_name = "name";
    std::string name = "Test Name";

    int count = db.valueExistsInTable(table_name, col_name, name);

    ASSERT_GT(count, 0);

    std::string last_id = db.lastInsertedValue();
    ASSERT_FALSE(last_id.empty());

    std::string col_value = db.getColValue("TestTable", "id", last_id, "name");

    ASSERT_EQ(col_value, name);
}

TEST(DatabaseWrapperTest, startRollbackTransactionTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();

    ASSERT_TRUE(db.startTransaction());
    ASSERT_TRUE(db.rollbackTransaction());
}

TEST(DatabaseWrapperTest, TransactionWithCommitTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string update_query = "UPDATE TestTable SET name = 'Name2' WHERE id = 1";

    ASSERT_TRUE(db.startTransaction());

    bool update_result = db.executeQueryD(update_query, false);
    ASSERT_TRUE(update_result);

    ASSERT_TRUE(db.commitTransaction());
}

TEST(DatabaseTest, getPrimaryKeysTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string query = "SELECT id FROM TestTable";
    std::vector<std::string> empids;

    bool success = db.getPrimaryKeys(query, empids);

    ASSERT_TRUE(success);
    ASSERT_FALSE(empids.empty());
}

TEST(DatabaseTest, getUserTablesTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::vector<std::string> expected_tables = { "UT_Niyati", "UT_bottle" };

    std::vector<std::string> tables = db.getUserTables();

    ASSERT_EQ(tables.size(), expected_tables.size());
    for (int i = 0; i < tables.size(); ++i) {
        ASSERT_EQ(tables[i], expected_tables[i]);
    }
}

TEST(DatabaseTest, getTableColumnsTest) {
    Database& db = DatabaseWrapper::getDemoDatabaseInstance();
    std::string table_name = "TestTable";
    std::vector<std::pair<std::string, std::string>> expected_columns = {
        {"id", "INTEGER"}, {"name", "TEXT"}
    };

    std::vector<std::pair<std::string, std::string>> columns = db.getTableColumns(table_name);

    ASSERT_EQ(columns.size(), expected_columns.size());
    for (int i = 0; i < columns.size(); ++i) {
        ASSERT_EQ(columns[i].first, expected_columns[i].first);
        ASSERT_EQ(columns[i].second, expected_columns[i].second);
    }
}
