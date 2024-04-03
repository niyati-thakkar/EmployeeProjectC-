#include "pch.h"
#include "Query.h"

TEST(QueryTest, GenerateWhereQueryEmptyInputTest) {
    // Arrange
    std::string colname = "";
    std::string colval = "";

    // Act
    std::string where_query = QueryE::generateWhereQuery(colname, colval);

    // Assert
    ASSERT_EQ(where_query, "");
}

TEST(QueryTest, GenerateWhereQueryValidInputTest) {
    // Arrange
    std::string colname = "name";
    std::string colval = "John Doe";

    // Act
    std::string where_query = QueryE::generateWhereQuery(colname, colval);

    // Assert
    ASSERT_EQ(where_query, " WHERE name = 'John Doe'");
}

TEST(QueryTest, GenerateUpdateQueryEmptyInputTest) {
    // Arrange
    std::string tablename = "";
    std::string toUpdate = "";
    std::string colname = "";
    std::string colval = "";

    // Act
    std::string update_query = QueryE::generateUpdateQuery(tablename, toUpdate, colname, colval);

    // Assert
    ASSERT_TRUE(update_query.empty());
}

TEST(QueryTest, GenerateUpdateQueryValidInputTest) {
    // Arrange
    std::string tablename = "Users";
    std::string toUpdate = "email = 'updated@email.com'";
    std::string colname = "username";
    std::string colval = "johndoe";

    // Act
    std::string update_query = QueryE::generateUpdateQuery(tablename, toUpdate, colname, colval);

    // Assert
    ASSERT_EQ(update_query, "UPDATE Users SET email = 'updated@email.com' WHERE username = 'johndoe';");
}

TEST(QueryTest, GenerateSelectQueryEmptyColumnsTest) {
    // Arrange
    std::string tablename = "Products";
    std::string columns = "";

    // Act
    std::string select_query = QueryE::generateSelectQuery(tablename, columns);

    // Assert
    ASSERT_TRUE(select_query.empty());
}

TEST(QueryTest, GenerateSelectQuerySingleColumnTest) {
    // Arrange
    std::string tablename = "Customers";
    std::string columns = "name";

    // Act
    std::string select_query = QueryE::generateSelectQuery(tablename, columns);

    // Assert
    ASSERT_EQ(select_query, "SELECT name FROM Customers;");
}

TEST(QueryTest, GenerateSelectQueryMultipleColumnsTest) {
    // Arrange
    std::string tablename = "Orders";
    std::string columns = "id, customer_id, product_id, quantity";

    // Act
    std::string select_query = QueryE::generateSelectQuery(tablename, columns);

    // Assert
    ASSERT_EQ(select_query, "SELECT id, customer_id, product_id, quantity FROM Orders;");
}

TEST(QueryTest, GenerateSelectQueryWithWhereClauseTest) {
    // Arrange
    std::string tablename = "Products";
    std::string columns = "name, price";
    std::string colname = "category";
    std::string colval = "Electronics";

    // Act
    std::string select_query = QueryE::generateSelectQuery(tablename, columns, colname, colval);

    // Assert
    ASSERT_EQ(select_query, "SELECT name, price FROM Products WHERE category = 'Electronics';");
}

TEST(QueryTest, GenerateInsertQueryEmptyInputTest) {
    // Arrange
    std::string tablename = "";
    std::string columns = "";
    std::string values = "";

    // Act
    std::string insert_query = QueryE::generateInsertQuery(tablename, columns, values);

    // Assert
    ASSERT_TRUE(insert_query.empty());
}

TEST(QueryTest, GenerateInsertQueryValidInputTest) {
    // Arrange
    std::string tablename = "Users";
    std::string columns = "name, email";
    std::string values = "'John Doe', 'johndoe@email.com'";

    // Act
    std::string insert_query = QueryE::generateInsertQuery(tablename, columns, values);

    // Assert
    ASSERT_EQ(insert_query, "INSERT INTO Users (name, email) VALUES ('John Doe', 'johndoe@email.com'); ");
}

TEST(QueryTest, GenerateDeleteQueryEmptyInputTest) {
    // Arrange
    std::string tablename = "";
    std::string colname = "";
    std::string colval = "";

    // Act
    std::string delete_query = QueryE::generateDeleteQuery(tablename, colname, colval);

    // Assert
    ASSERT_TRUE(delete_query.empty());
}

TEST(QueryTest, GenerateDeleteQueryValidInputTest) {
    // Arrange
    std::string tablename = "Products";
    std::string colname = "id";
    std::string colval = "10";

    // Act
    std::string delete_query = QueryE::generateDeleteQuery(tablename, colname, colval);

    // Assert
    ASSERT_EQ(delete_query, "DELETE FROM Products WHERE id = '10';");
}
