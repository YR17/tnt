#include <GameModel.hpp>

GameModel::GameModel():
	state(STATE_INIT),
	currentPlayer(0),
	stackAmount(0) {

}

GameModel::GameModel(const GameModel& ob) {

}

GameModel::~GameModel() {

}

State GameModel::getState() const {
	return state;
}

void GameModel::setState(State st) {
	state = st;
	notifyListeners(UPDATEREASON_STATE);
}

std::string GameModel::getName() const {
	return name;
}

void GameModel::setName(std::string nm) {
	name = nm;
	notifyListeners(UPDATEREASON_NAME);
}

std::vector<Card>& GameModel::getHand() {
	return hand;
}

std::vector<Player>& GameModel::getPlayers() {
	return players;
}

unsigned int GameModel::getCurrentPlayer() const {
	return currentPlayer;
}

void GameModel::setCurrentPlayer(unsigned int playerId) {
	currentPlayer = playerId;
	notifyListeners(UPDATEREASON_CURRENT_PLAYER);
}

unsigned int GameModel::getStackAmount() {
	return stackAmount;
}

void GameModel::setStackAmount(unsigned int amount) {
	stackAmount = amount;
	notifyListeners(UPDATEREASON_STACK_AMOUNT);
}

void GameModel::addListener(IGameModelListener* listener) {
	for (auto i: listeners) {
		if (listener == i) {
			return;
		}
	}
	listeners.push_back(listener);
}

void GameModel::removeListener(IGameModelListener* listener) {
	for (auto i = listeners.begin(); i != listeners.end(); i++) {
		if (listener == *i) {
			listeners.erase(i);
			return;
		}
	}
}

void GameModel::notifyListeners(UpdateReason reason) {
	for (auto i: listeners) {
		i->onUpdate(reason);
	}
}