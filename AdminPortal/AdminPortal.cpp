/* art database web microservice using mariaDB */


#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "httplib.h"
#include "artDB.h"
const int port = 5004;

using namespace std;

ofstream logfile; 

string jsonResults(vector<artEntry> pbList) {
	string res = "{\"results\":[";
	for (int i = 0; i<pbList.size(); i++) {
		res += pbList[i].json();
		if (i < pbList.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}

int main() {
	httplib::Server svr;

  	artDatabasae artDB; // Art Database SQL Interface Object
  
  	vector<artEntry> results;

  	svr.Get("/", [](const httplib::Request & /*req*/, httplib::Response &res) {
    	res.set_header("Access-Control-Allow-Origin","*");
    	res.set_content("Contact API", "text/plain");
  	});

  	svr.Get(R"(/contact/find)", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	results = artDB.find("");
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});
  	  	
  	svr.Get(R"(/contact/find/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string last = req.matches[1];
    	results = artDB.find(last);
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});
  	

  	svr.Get(R"(/contact/type/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string type = req.matches[1];
    	results = artDB.findByType(type);
    	string json = jsonResults(results);
    	cout << "type: " << json << endl;
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});  
  	
  	svr.Get(R"(/contact/add/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string name = req.matches[1];
    	artDB.addEntry(name);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 	
 
   	svr.Get(R"(/contact/update/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string ID = req.matches[1];
    	string name = req.matches[2];
    	artDB.editEntry(ID,name);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 

  	svr.Get(R"(/contact/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string ID = req.matches[1];
		artDB.deleteEntry(ID);
    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});  
  	 
  	cout << "Server listening on port " << port << endl;
  	svr.listen("0.0.0.0", port);

}
