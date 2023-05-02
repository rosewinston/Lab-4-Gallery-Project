#include "emojiEntry.h"

emojiEntry::emojiEntry() {
}

emojiEntry::emojiEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString emoji_code) {
    this->id = id;
    this->timestamp = timestamp;
    this->emoji_code = emoji_code;

}

string emojiEntry::text() {
	string result = id + ". ";
	result += timestamp + " ";
	result += emoji_code;
	
	return result;

}

string emojiEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"timestamp\":\"" + timestamp + "\",";
	result += "\"emoji_code\":\"" + emoji_code + "\"}";
	
	return result;
}
