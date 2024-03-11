#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Coin.h"
#include <memory>


static const float WIDTH = 1600.0f;
static const float HEIGHT = 900.0f;
static const float VIEW_HEIGHT = 1000.0f;
static const bool playerView = true;
static const float LEVEL_VIEW_HEIGHT = 5000.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "blub", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Vector2f middleOfScreen(WIDTH / 2, HEIGHT / 2);
	//window.setFramerateLimit(60);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Game/Assets/Sprites/tileBackground.jpg")) {
		std::cout << "Failed to load backgroundTexture" << std::endl;
	}
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	sf::FloatRect localBounds = background.getLocalBounds();
	background.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
	background.setPosition(0, 0);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Game/Assets/Sprites/mushroomSpriteSheet.png")) {
		std::cout << "Failed to load playerTexture" << std::endl;
	}

	Player player(&playerTexture, sf::Vector2u(6, 4), 0.3f, 600.0f, 200.0f);

	sf::Texture coinTexture;
	if (!coinTexture.loadFromFile("Game/Assets/Sprites/coinAnimation.png")) {
		std::cout << "Failed to load coinTexture" << std::endl;
	}

	std::vector<std::unique_ptr<Coin>> coins;
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1200.0f, 350.0f)));
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1250.0f, 350.0f)));
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1300.0f, 350.0f)));
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1350.0f, 350.0f)));
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1400.0f, 350.0f)));
	coins.push_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(6, 1), 0.75f, sf::Vector2f(1450.0f, 350.0f)));

	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(300.0f, 20.0f), sf::Vector2f(1200.0f, 150.0f), sf::Color::Red));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 200.0f), sf::Vector2f(500.0f, 350.0f), sf::Color::Blue));
	platforms.push_back(Platform(nullptr, sf::Vector2f(3000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f), sf::Color::Green));

	float deltaTime;
	sf::Clock clock;
	sf::Text nCoinsText;
	sf::Font font;
	if (!font.loadFromFile("Game/Assets/Fonts/Catboo.ttf")) {
		std::cout << "Failed to load font" << std::endl;
	}

	//Text Coins
	nCoinsText.setCharacterSize(24);
	nCoinsText.setFont(font);
	nCoinsText.setPosition(500.0f, 0.0f);
	int coinsCollected = 0;

	if (playerView)
		resizeView(window, view);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		//Events:
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				if (playerView)
					resizeView(window, view);
				break;
			case sf::Event::KeyReleased: {
				if (evnt.key.code == sf::Keyboard::LShift)
					player.allowDash();
				break;
			case sf::Event::KeyPressed:
				if (!player.getisDashing()) {
					if (evnt.key.code == sf::Keyboard::Escape)
						window.close();
					if (evnt.key.code == sf::Keyboard::A)
						player.faceRight = false;
					if (evnt.key.code == sf::Keyboard::D)
						player.faceRight = true;
				}
			}

			}
		}

		player.update(deltaTime);
		for (std::unique_ptr<Coin>& coin : coins)
			coin->update(deltaTime);

		Collider playerCollider = player.getCollider();

		sf::Vector2f direction;

		for (Platform platform : platforms)
			if (platform.getCollider().checkCollision(playerCollider, direction, 1.0f));
				player.onCollision(direction);

		for (auto it = coins.begin(); it != coins.end(); ) {
			if ((*it)->getCollider().checkCollision(playerCollider, direction, 0.0f)) {
				if (it == coins.begin()) {
					it = coins.erase(it);
				}
				else {
					it = coins.erase(it);
					--it;
				}
				coinsCollected++;
			}
			else {
				++it;
			}
		}

		nCoinsText.setString("Coins: " + std::to_string(coinsCollected));

		if (playerView)
			view.setCenter(player.getPositon());
		else {
			view.setCenter(player.getPositon());
			view.setSize(LEVEL_VIEW_HEIGHT, (LEVEL_VIEW_HEIGHT / 16) * 9);
		}

		window.setView(view);
		window.clear(sf::Color(150, 150, 150));
		//window.draw(background);
		player.drawTo(window);
		for (std::unique_ptr<Coin>& coin : coins)
			coin->drawTo(window);
		for (Platform platform : platforms)
			platform.drawTo(window);
		window.draw(nCoinsText);
		window.display();
	}


	return 0;
}

//test