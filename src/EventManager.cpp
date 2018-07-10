#include <EventManager.hpp>

EventManager::EventManager(GameModel& _model, GameView& _view):
	model(_model),
	view(_view),
	window(_view.getWindow()),
	polling(nullptr),
	exit(false) {
	polling = new std::thread(&EventManager::waitEvent, this);
}

EventManager::~EventManager() {
	polling->join();
	delete polling;
}

void EventManager::waitEvent() {
	// while (true) {
	// 	sf::Event event;
	// 	if(true == window.waitEvent(event)){
	// 		if (sf::Event::Closed == event.type){
	// 			window.close();
	// 			exit = true;
	// 			return;
	// 		}
	// 		//transfor sf:event to windowevent and send to listener
	// 	} else {
	// 		//error
	// 	}
	// }
}

bool EventManager::isExit() {
	return exit;
}