#include <GameController.hpp>

#include <iostream>
using namespace std;

GameController::GameController(GameModel& _model, NetworkManager& _networkManager):
model(_model),
networkManager(_networkManager),
helper() {
	networkManager.setListener(this);
	
	if (networkManager.connect()){
		GameEvent event;
		event.type = GAMEEVENTTYPE_CONNECT;
		event.connect.name = "YR17";
		std::string msg = helper.eventToString(event);
		networkManager.send(msg);
	}
}

GameController::~GameController() {

}

void GameController::onMessage(std::string msg) {
	cout << "Receive message: " << msg << endl;
	GameEvent event = helper.stringToEvent(msg);
	cout << "EventType: " << event.type << endl;
	switch (event.type) {
		case GAMEEVENTTYPE_START: {
			cout << "We starting..." << endl;
			model.getHand() = event.start.cards;
			model.getPlayers() = event.start.players;
			model.setStackAmount(event.start.stackAmount);
			////
			for (auto &i: event.start.players) {
				cout << "Player:" << i.name << " have " << i.numOfCards << "cards" << endl;
			}
			cout << "Yours hand:" << endl;
			for (auto &i: event.start.cards) {
				cout << helper.convertCardToString(i) << endl;
			}
			cout << "Stack contain " << event.start.stackAmount << endl;
			////
		} break;
		case GAMEEVENTTYPE_TURN: {
			std::vector<Player>& players = model.getPlayers();
			for (auto &i: players) {
				if (i.id == event.turn.id) {
					cout << "Now " << i.name << "'s turn" << endl;
					break;
				}
			}
			model.setCurrentPlayer(event.turn.id);
		} break;
		case GAMEEVENTTYPE_TAKE: {
			cout << helper.convertCardToString(event.take.card) << "card was takken from you" << endl;
			std::vector<Card>& cards = model.getHand();
			for (auto i = cards.begin(); i != cards.end(); i++) {
				if (event.take.card == *i) {
					cards.erase(i);
					break;
				}
			}
		} break;
		case GAMEEVENTTYPE_RECEIVE: {
			cout << helper.convertCardToString(event.receive.card) << "card was received" << endl;
			std::vector<Card>& cards = model.getHand();
			cards.push_back(event.receive.card);
		} break;
		case GAMEEVENTTYPE_PLAY: {
			cout << "Player #" << event.play.id << " played " << helper.convertCardToString(event.play.card) << " card" << endl;
		} break;
		case GAMEEVENTTYPE_AMOUNTCHANGED: {
			cout << "Player #" << event.amountChanged.id << " have " << event.amountChanged.numOfCards << " cards" << endl;
		} break;
		case GAMEEVENTTYPE_SHOWCARDS: {
			cout << "Server showed you a cards: " << endl;
			for (auto &i: event.showCards.cards) {
				cout << helper.convertCardToString(i) << endl;
			}
		} break;
		case GAMEEVENTTYPE_PLACEBOMB: {
			cout << "Bomb has been placed at " << event.placeBomb.place << "(index: " << event.placeBomb.index << ")" << endl;
		} break;
		default: {
			cout << "Wrong event type" << endl;
		}
	}
}