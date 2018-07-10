#ifndef JSON_HELPER_HPP
#define JSON_HELPER_HPP

#include <GameModel.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>

class JsonHelper {
public:
	JsonHelper();
	JsonHelper(const JsonHelper& ob);
	~JsonHelper();
	std::string eventToString(const GameEvent& event);
	GameEvent stringToEvent(const std::string& str);

	Card convertStringToCard(const std::string& cardName);
	std::string convertCardToString(const Card& card);
	Player convertValueToPlayer(const Json::Value& value);
	BombPlace convertStringToBombPlace(const std::string& place);
	std::string convertBombPlaceToString(const BombPlace& bombPlace);
private:
	Json::Reader reader;
	Json::FastWriter writer;

};

#endif //JSON_HELPER_HPP