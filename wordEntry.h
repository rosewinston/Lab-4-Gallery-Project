#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef WORDENTRY_H
#define WORDENTRY_H

class wordEntry {
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

#endif /* WORDENTRY_H */
