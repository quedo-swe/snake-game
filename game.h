#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstddef>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::RectangleShape overlay;

	//Font
	sf::Font font;

	//UI text elements
	sf::Text uiText;
	sf::Text restartGameText;
	sf::Text gameOverText;
	sf::Text highScoreText;

	bool gameOver;

	//Game logic
	int points;
	int cellSize;
	int delay;
	int time;
	int dx;
	int dy;
	int highScore;
	bool canChangeDirection;

	// Game objects
	sf::Vector2i food;
	std::vector<sf::Vector2i> snake;
	sf::RectangleShape segment;
	 
	// Init helpers called in constructor
	void initVariables();
	void initFonts();
	void initText();
	void initWindow();

public:
	Game();
	virtual ~Game();

	const bool running() const;

	void pollEvents();
	void resetGame();

	void updateSnakeBody();
	void updateText();
	void update();

	void renderSnakeBody();
	void renderText(sf::RenderTarget& target);
	void render();
};
