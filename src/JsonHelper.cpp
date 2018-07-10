#include <JsonHelper.hpp>
#include <iostream>
using namespace std;

JsonHelper::JsonHelper() {

}

JsonHelper::JsonHelper(const JsonHelper& ob) {

}

JsonHelper::~JsonHelper() {

}

std::string JsonHelper::eventToString(const GameEvent& event) {
	Json::Value root;
	switch(event.type) {
		case GAMEEVENTTYPE_CONNECT: {
			root["event"] = Json::Value("connect");
			root["name"] = Json::Value(event.connect.name);
		}  break;
		case GAMEEVENTTYPE_PLAY: {
			root["event"] = Json::Value("play");
			root["card"] = Json::Value(convertCardToString(event.play.card));
		} break;
		case GAMEEVENTTYPE_TAKEFROMDECK: {
			root["event"] = Json::Value("takeFromDeck");
		} break;
		case GAMEEVENTTYPE_PLACEBOMB: {
			root["event"] = Json::Value("placeBomb");
			root["place"] = Json::Value(convertBombPlaceToString(event.placeBomb.place));
			root["isClosed"] = Json::Value(event.placeBomb.isClosed);
			root["index"] = Json::Value(event.placeBomb.index);
		} break;
		default: {
			cout << "Invalid event type";
			return "";
		} break;
	}
	std::string result = 	writer.write(root);
	return result;
}

GameEvent JsonHelper::stringToEvent(const std::string& str) {
	GameEvent event;
	Json::Value root;
	bool result = reader.parse(str, root);
	if (false == result) {
		cout << "Parse error: " << reader.getFormattedErrorMessages();
		return event;
		// error handling
	}

	std::string eventType = root["event"].asString();

	if (eventType == "start") {
		event.type = GAMEEVENTTYPE_START;
		for (unsigned i = 0; i < root["hand"].size(); i++) {
			std::string cardName = root["hand"][i].asString();
			Card card = convertStringToCard(cardName);
			event.start.cards.push_back(card);
		}
		for (unsigned i = 0; i < root["table"].size(); i++) {
			Player player = convertValueToPlayer(root["table"][i]);
			event.start.players.push_back(player);
		}
		event.start.stackAmount = root["amountInDeck"].asUInt();
	} else if (eventType == "turn") {
		event.type = GAMEEVENTTYPE_TURN;
		event.turn.id = root["id"].asUInt();
	}	else if (eventType == "take") {
		event.type = GAMEEVENTTYPE_TAKE;
		std::string cardName = root["card"].asString();
		event.take.card = convertStringToCard(cardName);
	}	else if (eventType == "receive") {
		event.type = GAMEEVENTTYPE_RECEIVE;
		std::string cardName = root["card"].asString();
		event.receive.card = convertStringToCard(cardName);
	}	else if (eventType == "play") {
		event.type = GAMEEVENTTYPE_PLAY;
		std::string cardName = root["card"].asString();
		event.play.card = convertStringToCard(cardName);
		event.play.id = root["id"].asUInt();
	// }	else if (eventType == "takeFromDeck") {
	// 	event.type = GAMEEVENTTYPE_TAKEFROMDECK;
	}	else if (eventType == "amountChanged") {
		event.type = GAMEEVENTTYPE_AMOUNTCHANGED;
		event.amountChanged.id = root["id"].asUInt();
		event.amountChanged.numOfCards = root["numOfCards"].asUInt();
	}	else if (eventType == "showCards") {
		event.type = GAMEEVENTTYPE_SHOWCARDS;
		for (unsigned i = 0;i < root["cards"].size(); i++) {
			std::string cardName = root["cards"][i].asString();
			Card card = convertStringToCard(cardName);
			event.showCards.cards.push_back(card);
		}
	}	else if (eventType == "placeBomb") {
		event.type = GAMEEVENTTYPE_PLACEBOMB;
		event.placeBomb.isClosed = false;
		event.placeBomb.index = root["index"].asUInt();
		event.placeBomb.place = convertStringToBombPlace(root["place"].asString());
	} else {
		cout << "Error: unknown event:" << eventType << endl;
	}

	return event;
}

Card JsonHelper::convertStringToCard(const std::string& cardName) {
	if ("bomb" == cardName) {
		return CARD_BOMB;
	} else if ("defuse" == cardName) {
		return CARD_DEFUSE;
	} else if ("predict" == cardName) {
		return CARD_PREDICTION;
	} else if ("shuffle" == cardName) {
		return CARD_SHUFFLE;
	} else if ("stop" == cardName) {
		return CARD_STOP;
	} else if ("attack" == cardName) {
		return CARD_ATTACK;
	} else if ("skip" == cardName) {
		return CARD_SKIP;
	} else if ("please" == cardName) {
		return CARD_MERCY;
	} else if ("shawerma" == cardName) {
		return CARD_SHAVERMA;
	} else if ("cucumber" == cardName) {
		return CARD_CUCUMBER;
	} else if ("watermelon" == cardName) {
		return CARD_WATERMELON;
	} else if ("rainbow" == cardName) {
		return CARD_RAINBOW;
	} else if ("lumberjack" == cardName) {
		return CARD_LUMBERJACK;
	} else {
		cout << "Parsing error: " << cardName << endl;
		return CARD_BOMB;//0
	}
}

std::string JsonHelper::convertCardToString(const Card& card) {
	switch (card) {
		case CARD_BOMB: {
			return "bomb";
		} break;
		case CARD_DEFUSE: {
			return "defuse";
		} break;
		case CARD_PREDICTION: {
			return "predict";
		} break;
		case CARD_SHUFFLE: {
			return "shuffle";
		} break;
		case CARD_STOP: {
			return "stop";
		} break;
		case CARD_ATTACK: {
			return "attack";
		} break;
		case CARD_SKIP: {
			return "skip";
		} break;
		case CARD_MERCY: {
			return "please";
		} break;
		case CARD_SHAVERMA: {
			return "shawerma";
		} break;
		case CARD_CUCUMBER: {
			return "cucumber";
		} break;
		case CARD_WATERMELON: {
			return "watermelon";
		} break;
		case CARD_RAINBOW: {
			return "rainbow";
		} break;
		case CARD_LUMBERJACK: {
			return "lumberjack";
		} break;
		default: {
			return "null";
		}
	}
}

Player JsonHelper::convertValueToPlayer(const Json::Value& value) {
	Player player;
	player.name = value["name"].asString();
	player.id = value["id"].asUInt();
	player.numOfCards = value["numOfCards"].asUInt();
	return player;
}

BombPlace JsonHelper::convertStringToBombPlace(const std::string& place) {
	if ("TOP" == place) {
		return BOMBPLACE_TOP;
	} else if ("BOTTOM" == place) {
		return BOMBPLACE_BOTTOM;
	} else if ("MIDDLE" == place) {
		return BOMBPLACE_MIDDLE;
	} else if ("RANDOM" == place) {
		return BOMBPLACE_RANDOM;
	} else if ("SPECIFIC_INDEX" == place) {
		return BOMBPLACE_SPECIFIC_INDEX;
	} else {
		return BOMBPLACE_BOTTOM;//0
	}
}

std::string JsonHelper::convertBombPlaceToString(const BombPlace& bombPlace) {
	switch (bombPlace) {
		case BOMBPLACE_TOP: {
			return "TOP";
		} break;
		case BOMBPLACE_BOTTOM: {
			return "BOTTOM";
		} break;
		case BOMBPLACE_MIDDLE: {
			return "MIDDLE";
		} break;
		case BOMBPLACE_RANDOM: {
			return "RANDOM";
		} break;
		case BOMBPLACE_SPECIFIC_INDEX: {
			return "SPECIFIC_INDEX";
		} break;
		default: {
			return "null";
		}
	}
}