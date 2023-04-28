#include "emojiEntry.h"

colorEntry::emojiEntry() {
}

emojiEntry::emojiEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString art_piece, sql::SQLString color) {
    this->id = id;
    this->timestamp = timestamp;
    this->art_piece = art_piece;
    this->color = color;
}

string emojiEntry::text() {
	string result = id + ". ";
	result += timestamp + " ";
	result += art_piece + " ";
	result += color;
	return result;

}

string emojiEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"timestamp\":\"" + timestamp + "\",";
	result += "\"art_piece\":\"" + art_piece + "\",";
	result += "\"color\":\"" + color + "\"}";
	return result;
}
