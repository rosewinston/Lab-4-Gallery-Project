#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>
#include <map>

#include <mariadb/conncpp.hpp>

#include "colorEntry.h"
#include "emojiEntry.h"
#include "wordEntry.h"
#include "AdminPortal/artEntry.h"

#ifndef GALLERYDB_H
#define GALLERYDB_H

#define DB_URL "jdbc:mariadb://18.222.189.198:3306/gallery"
#define USER "lab4team"
#define PASS "iloveskon"

using namespace std;

class galleryDB {
public:
    galleryDB();
    //void addEntryEmoji(string id, string timestamp, string emoji_code);
    //void addEntryColor(string id, string timestamp, string art_piece, string color);
    void addEntryWord(string word); 
    //map<string, string> sumEmoji(string timestamp); //GO BACK AND NAME THIS STRING PARAMETER + EDIT MAP DATA TYPES
    //map<string, int> sumColor(string timestamp, string art_piece); //GO BACK AND NAME THIS STRING PARAMETER + EDIT MAP DATA TYPES
    vector<string> sumWord(string timestamp); //GO BACK AND NAME THIS STRING PARAMETER + EDIT MAP DATA TYPES
    // vector<userEntry> find(string user, string mail);
    // userEntry fetchEntry(string idnum);
    void addColor(string art_piece, string color);
    // void editColor(string idnum, string username, string email, string password);
    void deleteColor(string idnum);
    // function to get all art names
    vector<string> getAllArts();
    
    
    
    // verify if username matches database
    // bool verifyLogin(string user, string password);
    
private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* GALLERYDB_H */
