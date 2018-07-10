#include <Application.hpp>

#include <GameModel.hpp>
#include <GameView.hpp>
#include <NetworkManager.hpp>
#include <EventManager.hpp>
#include <GameController.hpp>

Application::Application() {

}

Application::Application(const Application& ob) {

}

Application::~Application(){

}

void Application::start() {
	GameModel gameModel;
	GameView gameView(gameModel);
	EventManager eventManager(gameModel, gameView);
	// NetworkManager networkManager;
	// GameController gameController(gameModel, networkManager, eventManager);
	gameView.start();
	while (/*false == networkManager.isError()&&*/false == eventManager.isExit());
}