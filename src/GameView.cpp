#include <GameView.hpp>

#include <iostream>
using namespace std;

GameView::GameView(GameModel& _model):
model(_model) {
	if (false == font.loadFromFile("data/font.ttf")) {
		cout << "Can not load font" << endl;
	}
	text.setFont(font);
	text.setString("Test");//model.getName());
	text.setColor(sf::Color::Black);
}

GameView::~GameView() {
	delete rendering;
}

void GameView::start() {
	cout << "Start create new thread" << endl;
	rendering = new std::thread(&GameView::render, this);
}

sf::Window& GameView::getWindow() {
	return window;
}

void GameView::render() {
	cout << "\\\\Render thread//" << endl;
	window.create(sf::VideoMode(640, 480), "GameView", sf::Style::Close);
	while (window.isOpen()) {
		window.clear(sf::Color(60, 10, 10));
		
		switch (model.getState()) {
			case STATE_INIT: {
				window.draw(text);
			} break;
		
		}

		window.display();
	}
}