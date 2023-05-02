#include "DatabaseFiles/artEntry.h"

artEntry::artEntry() {
}

artEntry::artEntry(sql::SQLString id, sql::SQLString name){
    this->ID = id;
    this->Name = name;
}

string artEntry::text() {
	string result = ID + ". ";
	result += Name + " ";
	return result;
}

string artEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"Name\":\"" + Name +  "\"}";
	return result;
}
