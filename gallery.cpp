#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "httplib.h"
#include "galleryDB.h"
#include "colorEntry.h"
// #include "CTokenGenerator.h"
#include <string>

using namespace httplib;
using namespace std;

const int port = 5005;

string getWordJSON(vector<string> &wordList){
	string result; 
	
	if (wordList.size()==0){
		result = "{\"status\": \"failed\"}";
		return;
	}
	else{
		result = "{\"status\": \"success\", ";
		bool first = true;
		string words = "\"words\":[";
		
		for (string word : wordList){
			if (not first) result += ",";
			result += "\"" + word + "\"";
			first = false;
 		}
		result += "]}";
		return result;
   }
}

int main(void) {
  Server svr;
  // int nextUser=0;
  // map<string,vector<string>> messageMap;
  // vector<string> currentUser;
  // map<string, vector<string>> userMap; //store the register information
  // vector<string> typingUser;
  // map<string, vector<string>> userToTokenMap;
  // map<string, string> tokenToUserMap;
  
  // Object of RestchatDB
  galleryDB gldb;
  gldb.addEntryWord("omgitsawordwow");
  
  	
  /* "/" just returnsAPI name */
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("Chat API", "text/plain"); 
  });
  
  // Get all art pieces names
  svr.Get(R"(/response/getAllArts)", [&](const Request& req, Response& res){
  	res.set_header("Access-Control-Allow-Origin","*");
  	vector<string> allArts = gldb.getAllArts();
  	string result;
  	if (allArts.size() == 0){
  		result = "{\"status\": \"failed\"}";
  	}
  	else {
  		result = "{\"status\": \"success\", ";
  		string arts = "\"all_arts\":[";
  		bool first = true;
  		for (auto &art : allArts) {
  			if (not first) result += ",";
			result += art;
			first = false;
  		}
  		arts += "]}";
  		result += arts;
  	}
  	
  	res.set_content(result, "text/json");
    res.status = 200;
  });
  
  svr.Get(R"(/response/addColor/(.*)/(.*))", [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");
    string art_piece = req.matches[1];
    string color = req.matches[2];
    string result;
    
    gldb.addColor(art_piece, color);
    result = "{\"status\":\"success\",\"art_piece\":\"" + art_piece + "\",\"color\":\"" + color + "\"}";
    
    res.set_content(result, "text/json");
    res.status = 200;
  });

  svr.Get(R"(/retrieve/art_pieces/))", [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");
    //gldb.retrieveArt();

    //res.set_content(result, "text/json")
    res.status =  200;
  });

  
  svr.Get(R"(/response/word/(.*))", [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");
    string word = req.matches[1];
    string result;
    
    gldb.addEntryWord(word);
    result = "{\"status\":\"success\",\"word\":\"" + word + "\"}";
    
    res.set_content(result, "text/json");
    res.status = 200;
  });
	
  svr.Get(R"(/retrieve/words/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");

    string timestamp = req.matches[1];
    vector<string> wordResult = gldb.sumWord(timestamp); 
    string json = getWordJSON(wordResult); 
	  
    res.set_content(json, "text/json");
    res.status = 200;
  });
	
	
  
   svr.Get("R(/admin/join/(.*)/(.*))",  [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");
    string username = req.matches[1];
    string password = req.matches[2];
    string result;
    
    if (username == "GalleryAdmin" && password == "WYjX5aKujKh67m") {
        result = "{\"status\":\"success\"}";
    }
    else {
      result = "{\"status\":\"failure\"}";
    }
    res.set_content(result, "text/json");
    res.status = 200;
  });
  
  
  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);
  
   
}
