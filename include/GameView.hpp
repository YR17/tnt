#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <GameModel.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <thread>

class GameView {
public:
	GameView(GameModel& model);
	~GameView();
	void start();
	sf::Window& getWindow();
private:
	void render();
	GameModel& model;
	sf::RenderWindow window;
	std::thread* rendering;
	sf::Font font;
	sf::Text text;
};

#endif // GAME_VIEW_HPP