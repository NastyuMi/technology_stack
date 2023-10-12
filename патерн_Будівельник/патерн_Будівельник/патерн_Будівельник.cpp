#include <iostream>
#include <string>

using namespace std;

// головний інтерфейс будівельник для всіх типів БД
class SQL_query {
public:
    virtual void reset() = 0;
    virtual void select(const string& fields) = 0;
    virtual void where(const string& condition) = 0;
    virtual void limit(int limit) = 0;
    virtual string getSQL() = 0;
};

// будівельник для PostgreSQL
class Postgre_query : public SQL_query {
private:
    string query;
    string select_fields;
    string where_condition;
    string limit_limit;

public:
    Postgre_query() {
        reset();
    }

    void reset() override {
        query = "\n\t SELECT : ";
    }

    void select(const string& fields) override {
        select_fields = fields;
    }

    void where(const string& condition) override {
        where_condition = condition;
    }

    void limit(int limit) override {
        limit_limit = to_string(limit);
    }

    string getSQL() override {
        query += select_fields + "\n\t WHERE : " + where_condition + "\n\t Limit : " + limit_limit;
        return query;
    }
};

// будівельник для MySQL
class MySQL_query : public SQL_query {
private:
    string query;
    string select_fields;
    string where_condition;
    string limit_limit;

public:
    MySQL_query() {
        reset();
    }

    void reset() override {
        query = "\n\t SELECT : ";
    }

    void select(const string& fields) override {
        select_fields = fields;
    }

    void where(const string& condition) override {
        where_condition = condition;
    }

    void limit(int limit) override {
        limit_limit = to_string(limit);
    }

    string getSQL() override {
        query += select_fields + "\n\t WHERE : " + where_condition + "\n\t Limit : " + limit_limit;
        return query;
    }
};

// Директор 
class SQL_director {
public:
    void buildQuery(SQL_query& type_sql_query) {
        type_sql_query.reset();
        type_sql_query.select("column1, column2");
        type_sql_query.where("condition1 = 'value'");
        type_sql_query.limit(10);
    }

    // запити щоб створювати заміну значить які автоматично заповнює діректор

    void changeSelect(SQL_query& type_sql_query, const string& fields) {
        type_sql_query.select(fields);
    }

    void changeWhere(SQL_query& type_sql_query, const string& condition) {
        type_sql_query.where(condition);
    }

    void changeLimit(SQL_query& type_sql_query, int limit) {
        type_sql_query.limit(limit);
    }
};

int main() {

    Postgre_query postgres;
    MySQL_query mySQL;
    SQL_director director;

    // PostgreSQL
    director.buildQuery(postgres);
    cout << "PostgreSQL Query: " << postgres.getSQL() << endl;

    // MySQL
    director.buildQuery(mySQL);
    director.changeLimit(mySQL,23);
    cout << "MySQL Query: " << mySQL.getSQL() << endl;

    return 0;
}
