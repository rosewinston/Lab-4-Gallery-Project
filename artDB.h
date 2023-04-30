#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

//#include "mysql_connection.h"
//#include "mysql_driver.h"
#include <mariadb/conncpp.hpp>

//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
#include "artEntry.h"

#ifndef CONTACTDB_H
#define CONTACTDB_H

#define DB_URL "jdbc:mariadb://localhost:3306/SoftDevContacts"
#define USER "root"
#define PASS "0606"

using namespace std;

class artDB {
public:
    artDB();
    vector<contactEntry> find(string search);
    contactEntry fetchEntry(string id);
    void addEntry(string name;
    void editEntry(string idnum,string name);
    void deleteEntry(string idnum);
private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* contactDB_H */