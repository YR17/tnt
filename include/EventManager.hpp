#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <thread>
#include <SFML/Window.hpp>

#include <GameModel.hpp>
#include <GameView.hpp>

enum WindowEventType {
	WINDOWEVENTTYPE_KEYBOARD_KEY_UP,
	WINDOWEVENTTYPE_KEYBOARD_KEY_DOWN,
	WINDOWEVENTTYPE_MOUSE_CLICK_UP,
	WINDOWEVENTTYPE_MOUSE_CLICK_DOWN,
	WINDOWEVENTTYPE_WINDOW_CLOSE
};

struct WindowEvent {
	WindowEventType type;
	union {
		struct {
			char key;
		} keyboard;
		struct {
			int x;
			int y;
		} mouse;
	};
};

class EventManager {
public:
	EventManager(GameModel& model, GameView& view);
	~EventManager();
	void waitEvent();
	bool isExit();
private:
	std::thread *polling;
	GameModel& model;
	GameView& view;
	sf::Window& window;
	bool exit;
};

#endif //EVENT_MANAGER_HPP