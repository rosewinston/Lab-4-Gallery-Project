#include <vector>
#include <iostream>
#include <mariadb/conncpp.hpp>
#include "galleryDB.h"
#include "colorEntry.h"


galleryDB::galleryDB() {
  	// Instantiate Driver
  	driver = sql::mariadb::get_driver_instance();
  	
 	// Configure Connection
  	// The URL or TCP connection string format is
  	// ``jdbc:mariadb://host:port/database``.
  	sql::SQLString url(db_url);

    // Use a properties map for the other connection options
  	sql::Properties my_properties({{"user", user}, {"password", pass}});
  	// Save properties in object
  	properties = my_properties;

    // Establish Connection
  	std::unique_ptr<sql::Connection> my_conn(driver->connect(db_url, properties));
    
    // Check success
    if (!my_conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}	
   	
   	// Save connection in object
   	conn = std::move(my_conn);
   	
}

void galleryDB::addEntryWord(string word){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	stmnt->executeQuery("INSERT INTO word_response(word) VALUES ('"+word+"')");
}


void galleryDB::addColor(string art_piece, string color){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	stmnt->executeQuery("INSERT INTO color_response(art_piece, color) VALUES ('"+art_piece+"','"+color+"')");
}


vector<string> galleryDB::sumWord(string timestamp){
	string timestamp;
	timestamp.append("%");
	string word;
	vector<string> wordList; 
	if (!conn)
	{
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
	sql::ResultSet *res = stmnt->executeQuery("SELECT word FROM word_response WHERE timestamp like '" + timestamp + "'");
	while (res->next())
	{
		word = res->getString("word");
		wordList.push_back(word); 
		
	}
	return wordList;
}
	
// Get all arts function
vector<string> galleryDB::getAllArts() {
	vector<string> list;
	if (!conn) {
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
  	sql::ResultSet *res = stmnt->executeQuery(
			"SELECT DISTINCT Name FROM art_pieces"
	);
    
    // Loop through and print results
    while (res->next()) {
    	string art;
	    list.push_back(art);
    }
    
    return list;
}







// vector<userEntry> restChatDB::find(string user, string mail) {
// 
// 	vector<userEntry> list;
//     
//     // Make sure the connection is still valid
//     if (!conn) {
//    		cerr << "Invalid database connection" << endl;
//    		exit (EXIT_FAILURE);
//    	}	
//     // Create a new Statement
// 	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//     
//     // Execute query
//     sql::ResultSet *res = stmnt->executeQuery(
// 			"SELECT * FROM users WHERE username like '%"+user+"%' OR " + "email like '%"+mail+"%'");
//     
//     // Loop through and print results
//     while (res->next()) {
//     	userEntry entry(res->getString("ID"),res->getString("username"),
// 			res->getString("email"),res->getString("password"));
// 	    list.push_back(entry);
//     }
//     return list;
// }
// 
// // Function to find if username and password matches with DB
// bool restChatDB::verifyLogin(string user, string password) {
// 
// 	bool found = false;
//     
//     // Make sure the connection is still valid
//     if (!conn) {
//    		cerr << "Invalid database connection" << endl;
//    		exit (EXIT_FAILURE);
//    	}	
//     // Create a new Statement
// 	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//     
//     // Execute query
// 
//     sql::ResultSet *res = stmnt->executeQuery(
// 			"SELECT COUNT(*) AS count FROM users WHERE username = '"+user+"' AND password = '" + password+ "'");
//     
//     // Loop through and print results
//     while (res->next()) {
//     	if (res->getString("count") == "1"){
//     		found = true;
//     	}
//     }
//     
//     return found;
// }
