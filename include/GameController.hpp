#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <GameModel.hpp>
#include <NetworkManager.hpp>
#include <JsonHelper.hpp>
#include <EventManager.hpp>

class GameController: public INetworkListener {
public:
	GameController(GameModel& model, NetworkManager& networkManager);
	~GameController();
	virtual void onMessage(std::string msg) override;
private:
	GameModel& model;
	NetworkManager& networkManager;
	JsonHelper helper;
};

#endif //GAME_CONTROLLER_HPP