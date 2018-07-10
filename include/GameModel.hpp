#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <vector>
#include <string>

enum Card {
	CARD_BOMB,
	CARD_DEFUSE,
	CARD_PREDICTION,
	CARD_SHUFFLE,
	CARD_STOP,
	CARD_ATTACK,
	CARD_SKIP,
	CARD_MERCY,
	CARD_SHAVERMA,
	CARD_CUCUMBER,
	CARD_WATERMELON,
	CARD_RAINBOW,
	CARD_LUMBERJACK,
};

enum State {
	STATE_INIT = 0,
	STATE_CONNECTING,
	STATE_IN_GAME,
	STATE_TURN,
	STATE_IDDLE,
	STATE_END
};

struct Player {
	unsigned int id;
	std::string name;
	unsigned int numOfCards;
};

enum GameEventType {
	GAMEEVENTTYPE_CONNECT = 0,
	GAMEEVENTTYPE_START,
	GAMEEVENTTYPE_TURN,
	GAMEEVENTTYPE_TAKE,
	GAMEEVENTTYPE_RECEIVE,
	GAMEEVENTTYPE_PLAY,
	GAMEEVENTTYPE_TAKEFROMDECK,
	GAMEEVENTTYPE_AMOUNTCHANGED,
	GAMEEVENTTYPE_SHOWCARDS,
	GAMEEVENTTYPE_PLACEBOMB
};

enum BombPlace {
	BOMBPLACE_TOP = 0,
	BOMBPLACE_BOTTOM,
	BOMBPLACE_MIDDLE,
	BOMBPLACE_RANDOM,	
	BOMBPLACE_SPECIFIC_INDEX
};

struct GameEvent {
	GameEventType type;
	// union {
		struct {
			std::string name;
		} connect;
		struct {
			std::vector<Card> cards;
			std::vector<Player> players;
			unsigned int stackAmount;
		} start;
		struct {
			unsigned int id;
		} turn;
		struct {
			Card card;
		} take;
		struct {
			Card card;
		} receive;
		struct {
			Card card;
			unsigned int id;
		} play;
		struct {
			unsigned int id;
			unsigned int numOfCards;
		} amountChanged;
		struct {
			std::vector<Card> cards;
		} showCards;
		struct {
			BombPlace place;
			bool isClosed;
			unsigned int index;
		} placeBomb;
	// };
};

enum UpdateReason {
	UPDATEREASON_STATE,
	UPDATEREASON_NAME,
	UPDATEREASON_CURRENT_PLAYER,
	UPDATEREASON_STACK_AMOUNT
};

class IGameModelListener {
public:
	virtual void onUpdate(UpdateReason reason) = 0;
};

class GameModel {
public:
	GameModel();
	GameModel(const GameModel& ob);
	~GameModel();
	State getState() const;
	void setState(State st);
	std::string getName() const;
	void setName(std::string nm);
	std::vector<Card>& getHand();
	std::vector<Player>& getPlayers();
	unsigned int getCurrentPlayer() const;
	void setCurrentPlayer(unsigned int playerId);
	unsigned int getStackAmount();
	void setStackAmount(unsigned int amount);
	void addListener(IGameModelListener* listener);
	void removeListener(IGameModelListener* listener);
private:
	State state;
	std::string name;
	std::vector<Card> hand;
	std::vector<Player> players;
	unsigned int currentPlayer;
	unsigned int stackAmount;
	std::vector<IGameModelListener*> listeners;
	void notifyListeners(UpdateReason reason);
};

#endif //GAME_MODEL_HPP