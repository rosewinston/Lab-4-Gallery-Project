#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "httplib.h"
#include "DatabaseFiles/galleryDB.h"
#include "DatabaseFiles/colorEntry.h"
#include <string>

using namespace httplib;
using namespace std;

const int port = 5005;

string getWordJSON(vector<string> &wordList){
	string result; 
	
	if (wordList.size()==0){
		result = "{\"status\": \"failed\"}";
		return result;
	}
	else{
		result = "{\"status\": \"success\", \"words\":[";
		bool first = true;
		//string words = "\"words\":[";
		
		for (string word : wordList){
			cout<<word<<endl; 
			if (not first) result += ",";
			result += "\"" + word + "\"";
			first = false;
 		}
		result += "]}";
		return result;
   }
}

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

// string jsonSummaryEmotion(map<string, map<string, int> myMap){
// 	string result = "\"results\":[";
// 	for (auto art : myMap) {
// 		bool first = true;
// 		
// 		// Iterate over outer map
//         string artName = art.first;
// 		
// 		string emotion;
//         int count;
// 		for (auto emo : myMap[art]){
// 			emotion = emo.first;
// 			count = emo.second;
// 		}
// 		
//         if (not first) result += ",";
//         result += "{\""+artName+"\":{\""+emotion+"\":"+count+"}}";
//         first = false;
//     }
//     result += "]";
//     return result;
// }


int main(void) {
  Server svr;
  // Object of RestchatDB
  galleryDB gldb;
  gldb.addEntryWord("omgitsawordwow");
  vector<artEntry> results;
  /* "/" just returnsAPI name */
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("Gallery API", "text/plain"); 
  });
  
  // Get all art pieces names
  svr.Get(R"(/response/getAllArts)", [&](const Request& req, Response& res){
  	res.set_header("Access-Control-Allow-Origin","*");
  	vector<string> allArts = gldb.getAllArts();
  	
  	cout << "ALL arts size: " << allArts.size();
  	
  	string result;
  	if (allArts.size() == 0){
  		result = "{\"status\": \"failed\"}";
  	}
  	
  	else {
  		result = "{\"status\": \"success\", \"arts\":[";
  		bool first = true;
  		for (auto art : allArts) {
  			if (not first) result += ",";
			result += "\"" + art + "\"";
			first = false;
  		}
  		result += "]}";
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
	
  
   svr.Get(R"(/admin/join/(.*)/(.*))",  [&](const Request& req, Response& res) {
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
	

   svr.Get(R"(/art/find)", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	results = gldb.find("");
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});

svr.Get(R"(/art/find/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string name = req.matches[1];
    	results = gldb.find(name);
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});


svr.Get(R"(/art/add/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
	res.set_header("Access-Control-Allow-Origin","*");

	string name = req.matches[1];
	string link = req.matches[2];
	gldb.addEntry(name,link);

	res.set_content("{\"status\":\"success\"}", "text/json");
	res.status = 200;
}); 	

svr.Get(R"(/art/update/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
	res.set_header("Access-Control-Allow-Origin","*");

	string ID = req.matches[1];
	string name = req.matches[2];
	string link = req.matches[3];
	gldb.editEntry(ID,name,link);

	res.set_content("{\"status\":\"success\"}", "text/json");
	res.status = 200;
}); 

svr.Get(R"(/art/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
	res.set_header("Access-Control-Allow-Origin","*");

	string ID = req.matches[1];
		gldb.deleteEntry(ID);
	res.set_content("{\"status\":\"success\"}", "text/json");
	res.status = 200;
});  
 
// Summary Page for Emotions
svr.Get(R"(/response/summaryEmotion)", [&](const Request& req, Response& res){
  	res.set_header("Access-Control-Allow-Origin","*");
  	vector<string> artVec;
  	vector<string> emoVec;
  	vector<string> countVec;
  	
  	gldb.summaryEmotion(emoVec, artVec, countVec);
  	string result;
  	
  	if (artVec.size() > 0 && emoVec.size() > 0 && countVec.size() > 0){
  		result = "{\"status\":\"success\", ";
  		string emoStr = "\"emotions\":[";
  		string artStr = "\"arts\":[";
  		string countStr = "\"counts\":[";
  		bool first = true;
  		for (int i=0; i<artVec.size(); i++){
  			if (not first) {
  				artStr += ",";
  				emoStr += ",";     
  				countStr += ",";
  			}
  			artStr += "\"" + artVec[i] + "\"";
  			emoStr += "\"" + emoVec[i] + "\"";
  			countStr += countVec[i];
  			first = false;
  		}
  		artStr += "]";
  		emoStr += "]";
  		countStr += "]";
  		result += emoStr + "," + artStr + "," + countStr + "}";
  	}
  	else
  		result = "{\"status\":\"failed\"}";
  		
  	res.set_content(result, "text/json");
  	res.status = 200;
  });


  
  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);
  
   
}
