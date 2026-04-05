#include "game.h"

void Game::initVariables()
{
	window = nullptr;

    points = 0;
    cellSize = 20;
    delay = 10;
    time = 0;
    highScore = 0;
    canChangeDirection = true;
    gameOver = false;

    // Snake segment shape
    segment.setSize(sf::Vector2f(cellSize, cellSize));
    segment.setFillColor(sf::Color::Green);
    segment.setOutlineColor(sf::Color::Red);
    segment.setOutlineThickness(3);

    // Spawn snake
    snake.push_back({ 400,260 });
    snake.push_back({ 400,280 });
    snake.push_back({ 400,300 });

    dx = 0;
    dy = cellSize;
}

void Game::initFonts()
{
    if (!font.loadFromFile("Fonts/Pixellettersfull-BnJ5.ttf"))
    {
        std::cout << "ERROR:GAME::INTETION::Failed to load font!" << '\n';
    }
}

void Game::initText()
{
    uiText.setFont(font);
    uiText.setCharacterSize(22);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("NONE");


    gameOverText.setFont(font);
    gameOverText.setCharacterSize(45);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");

    restartGameText.setFont(font);
    restartGameText.setCharacterSize(35);
    restartGameText.setFillColor(sf::Color::White);
    restartGameText.setString("Press R to restart");

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(25);
    highScoreText.setFillColor(sf::Color::White);
}

void Game::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;

	window = new sf::RenderWindow(videoMode, "Snake", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    // Spawn food
    food.y = (rand() % (videoMode.height / cellSize)) * cellSize;
    food.x = (rand() % (videoMode.width / cellSize)) * cellSize;

    // Game over overlay
    overlay.setSize(sf::Vector2f(videoMode.width, videoMode.height));
    overlay.setFillColor(sf::Color::Black);

    // Centered text
    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    gameOverText.setPosition(videoMode.width / 2.f, videoMode.height / 2.f - 40.f);

    sf::FloatRect b2 = restartGameText.getLocalBounds();
    restartGameText.setOrigin(b2.left + b2.width / 2.f, b2.top + b2.height / 2.f);
    restartGameText.setPosition(videoMode.width / 2.f, videoMode.height / 2.f + 30.f);
}

Game::Game()
{
	initVariables();
    initFonts();
    initText();
	initWindow();
}

Game::~Game()
{
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) window->close();
            break;
        }
    }
}

void Game::resetGame()
{
    snake.clear();

    // Reset to start position
    snake.push_back({ 400,260 });
    snake.push_back({ 400,280 });
    snake.push_back({ 400,300 });

    dx = 0;
    dy = cellSize;
    points = 0;
    canChangeDirection = true;
    delay = 10;

    //respawn food
    food.y = (rand() % (videoMode.height / cellSize)) * cellSize;
    food.x = (rand() % (videoMode.width / cellSize)) * cellSize;

}

//updating
void Game::updateSnakeBody()
{
    // Calculate new head position based on current direction
    sf::Vector2i newHead = {
        snake.back().x + dx,
        snake.back().y + dy
    };

    // Wrap around window edges
    if (newHead.x < 0) newHead.x = videoMode.width - cellSize;
    if (newHead.x >= videoMode.width) newHead.x = 0;
    if (newHead.y < 0) newHead.y = videoMode.height - cellSize;
    if (newHead.y >= videoMode.height) newHead.y = 0;

    snake.push_back(newHead);

    if (newHead == food)
    {
        //respawn food
        food.y = (rand() % (videoMode.height / cellSize)) * cellSize;
        food.x = (rand() % (videoMode.width / cellSize)) * cellSize;
        points++;

        // Speed up every 5 points, minimum delay of 5 frames
        if (points % 5 == 0 && delay >= 5)
        {
            delay--;
        }
    }
    else
    {
        // Remove tail
        snake.erase(snake.begin());
    }

    for (size_t i = 0; i < snake.size() - 1; i++)
    {
        if (newHead == snake[i])
        {
            gameOver = true;
            return;
        }
    }
   
    time = 0;
    canChangeDirection = true;
}

void Game::updateText()
{
    std::stringstream ss1;
    ss1 << "Score: " << points;
    uiText.setString(ss1.str());

    std::stringstream ss2;
    ss2 << "High score: " << highScore;
    highScoreText.setString(ss2.str());

    // Re-center after string changes
    sf::FloatRect b = highScoreText.getLocalBounds();
    highScoreText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
    highScoreText.setPosition(videoMode.width / 2.f, videoMode.height / 2.f);
}

void Game::update()
{
    pollEvents();

    // input
    switch (canChangeDirection)
    {
    case true:
    {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && dy == 0)
            {
                dx = 0;
                dy = -cellSize;
                canChangeDirection = false;
            }

            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && dy == 0)
            {
                dx = 0;
                dy = cellSize;
                canChangeDirection = false;
            }

            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && dx == 0)
            {
                dx = -cellSize;
                dy = 0;
                canChangeDirection = false;
            }

            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && dx == 0)
            {
                dx = cellSize;
                dy = 0;
                canChangeDirection = false;
            }
            break;
    }
    case false: break;
    }

    time++;
    if (time >= delay)
    {
        updateSnakeBody();
    }

    if (highScore < points)
    {
        highScore = points;
    }
    updateText();

    if (gameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            resetGame();
            gameOver = false;
        }
        return;
    }
}

//rendering
void Game::renderSnakeBody()
{
    for (auto& p : snake)
    {
        segment.setPosition(p.x, p.y);
        window->draw(segment);
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(uiText);

}

void Game::render()
{
    window->clear();

    renderSnakeBody();

    //Drawing food
    sf::RectangleShape foodBlock;
    foodBlock.setSize(sf::Vector2f(cellSize, cellSize));
    foodBlock.setFillColor(sf::Color::Red);
    foodBlock.setPosition(food.x, food.y);
    window->draw(foodBlock);

    renderText(*window);

    //Game over
    if (gameOver)
    {
        window->draw(overlay);
        window->draw(highScoreText);
        window->draw(gameOverText);
        window->draw(restartGameText);
    }

    window->display();

}
