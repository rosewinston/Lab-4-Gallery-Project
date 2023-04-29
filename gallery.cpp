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
  
  	
  /* "/" just returnsAPI name */
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("Chat API", "text/plain"); 
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
  
  svr.Get(R"(/response/word/(.*))", [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");
    string word = req.matches[1];
    string result;
    
    gldb.addEntryWord(word);
    result = "{\"status\":\"success\",\"word\":\"" + word + "\"}";
    
    res.set_content(result, "text/json");
    res.status = 200;
  });
  
  
  
  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);
  
}
