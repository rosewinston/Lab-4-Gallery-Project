#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef EMOJIENTRY_H
#define EMOJIENTRY_H

class emojiEntry {
public:
     emojiEntry();
     emojiEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString emoji_code);
     string text();
     string json();
     
  string id;
  string timestamp;
  string emoji_code; 

private:

};

#endif /* EMOJIENTRY_H */
