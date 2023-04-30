#include "artEntry.h"

artEntry::artEntry() {
}

artEntry::artEntry(sql::SQLString n, sql::SQLString I){
    name = f;
    ID=I;
}

string artEntry::text() {
	string result = ID + ". ";
	result += name + " ";
	return result;

}

string artEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"first\":\"" + first +  "\"}";
	return result;

}