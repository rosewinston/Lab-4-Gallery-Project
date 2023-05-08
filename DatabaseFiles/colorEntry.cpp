#include "colorEntry.h"

colorEntry::colorEntry() {
}

colorEntry::colorEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString art_piece, sql::SQLString emotion) {
    this->id = id;
    this->timestamp = timestamp;
    this->art_piece = art_piece;
    this->emotion = emotion;
}

string colorEntry::text() {
	string result = id + ". ";
	result += timestamp + " ";
	result += art_piece + " ";
	result += emotion;
	return result;

}

string colorEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"timestamp\":\"" + timestamp + "\",";
	result += "\"art_piece\":\"" + art_piece + "\",";
	result += "\"emotion\":\"" + emotion + "\"}";
	return result;
}
