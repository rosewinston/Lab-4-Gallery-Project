#include <vector>
#include <iostream>
#include <mariadb/conncpp.hpp>
#include "galleryDB.h"


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
    	art = res->getString("Name");
	    list.push_back(art);
    }
    
    return list;
}


vector<artEntry> galleryDB::find(string search) {

	vector<artEntry> list;
    
    // Make sure the connection is still valid
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}	
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    
    // Execute query
    sql::ResultSet *res = stmnt->executeQuery(
			"SELECT * FROM art_pieces WHERE Name like '%"+search+"%");
    
    // Loop through and print results
    while (res->next()) {
    	artEntry entry(res->getString("ID"),res->getString("Name"),res->getString("Link"));
	    list.push_back(entry);

    }
    return list;

}


void galleryDB::addEntry(string name, string link){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
  	stmnt->executeQuery("INSERT INTO art_pieces(Name) VALUES ('"+name+"','"+link+"')");
}

artEntry galleryDB::fetchArt(string id){

	artEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM art_pieces WHERE ID = '"+id+"'");
    
    // Get first entry
    if (res->next()) {
    	entry = artEntry(res->getString("ID"),res->getString("Name"), res->getString("Link"));
    }
    return entry;
}

void galleryDB::editEntry(string idnum,string name,string link){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
  	
  	stmnt->executeQuery("UPDATE art_pieces SET Name = '"+name+"'Link = '"+link+"', WHERE ID='"+idnum+"'");
  	
}


void galleryDB::deleteEntry(string idnum){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }

  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  stmt->execute("DELETE FROM art_pieces WHERE ID='"+idnum+"'");
}



// function to summarize results of emotion responses for each art piece
void galleryDB::summaryEmotion(vector<string> &artVec, vector<string> &emotionVec, vector<string> &countVec) {	
	if (!conn) {
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
  	sql::ResultSet *res = stmnt->executeQuery(
			"SELECT art_piece, color, COUNT(color) as count_emotion FROM color_response GROUP BY art_piece, color"
	);
    
    // Loop through and print results
    while (res->next()) {
    	string art;
    	art = res->getString("art_piece");
    	artVec.push_back(art);
    	string color;
    	color = res->getString("color");
    	emotionVec.push_back(color);
    	string countStr;
    	countStr = res->getString("count_emotion");
    	countVec.push_back(countStr);
    	//cout << art << " " << color << " " << countInt << endl;
    }
}