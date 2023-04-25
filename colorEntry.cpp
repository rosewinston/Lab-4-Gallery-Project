#include "colorEntry.h"

colorEntry::colorEntry() {
}

colorEntry::colorEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString art_piece, sql::SQLString color) {
    this->id = id;
    this->timestamp = timestamp;
    this->art_piece = art_piece;
    this->color = color;
}

string colorEntry::text() {
	string result = id + ". ";
	result += timestamp + " ";
	result += art_piece + " ";
	result += color;
	return result;

}

string colorEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"timestamp\":\"" + timestamp + "\",";
	result += "\"art_piece\":\"" + art_piece + "\",";
	result += "\"color\":\"" + color + "\"}";
	return result;
}
