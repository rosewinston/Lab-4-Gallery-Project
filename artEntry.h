#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef ARTENTRY_H
#define ARTENTRY

class artEntry {
public:
     artEntry();
     artEntry(sql::SQLString ID, sql::SQLString Name);
     string text();
     string json();
     
     string ID;
     string Name;

private:

};

#endif /* ARTENTRY_H */
