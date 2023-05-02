#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef COLORENTRY_H
#define COLORENTRY_H

class colorEntry {
public:
     colorEntry();
     colorEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString art_piece, sql::SQLString color);
     string text();
     string json();
     
  string id;
  string timestamp;
  string art_piece;
  string color;

private:

};

#endif /* COLORENTRY_H */
