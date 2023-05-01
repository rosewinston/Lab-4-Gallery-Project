#include <vector>
#include <iostream>
#include <mariadb/conncpp.hpp>
#include "artDB.h"
#include "artEntry.h"



artDB::artDB() {
  	// Instantiate Driver
  	driver = sql::mariadb::get_driver_instance();
  	
 	// Configure Connection
  	// The URL or TCP connection string format is
  	// ``jdbc:mariadb://host:port/database``.
  	sql::SQLString url(db_url);

    // Use a properties map for the other connection options
  	sql::Properties my_properties({{"user", user}, {"password",pass}});
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

vector<artEntry> artDB::find(string search) {

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
    	artEntry entry(res->getString("Name"));
	    	
	    list.push_back(entry);

    }
    return list;

}


void artDB::addEntry(string name){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
  	stmnt->executeQuery("INSERT INTO art_pieces(Name) VALUES ('"+name+"')");
}

artEntry artDB::fetchEntry(string id){

	artEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM contacts WHERE ID = '"+id+"'");
    
    // Get first entry
    if (res->next()) {
    	entry = artEntry(res->getString("name"));
    }
    return entry;
}

void artDB::editEntry(string idnum,string name){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
  	
  	stmnt->executeQuery("UPDATE art_pieces SET Name = '"+name+"' WHERE ID='"+idnum+"'");
  	
}


void artDB::deleteEntry(string idnum){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }

  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  stmt->execute("DELETE FROM contacts WHERE ID='"+idnum+"'");
}

