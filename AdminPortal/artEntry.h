#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef ARTENTRY_H
#define ARTENTRY

class artEntry {
public:
     artEntry();
     artEntry(sql::SQLString n, sql::SQLString I);
     string text();
     string json();
     
     string name;
     string ID;

private:

};

#endif /* ARTENTRY_H */
