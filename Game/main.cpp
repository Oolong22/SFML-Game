#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"


static const float WIDTH = 960.0f;
static const float HEIGHT = 540.0f;
static const float VIEW_HEIGHT = 540.0f;

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
	if (!backgroundTexture.loadFromFile("Game/Assets/Sprites/tiles.jpg")) {
		std::cout << "Failed to load backgroundTexture" << std::endl;
	}
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	background.setOrigin(background.getGlobalBounds().height / 2.0f, background.getGlobalBounds().width / 2.0f);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Game/Assets/Sprites/blub.png")) {
		std::cout << "Failed to load playerTexture" << std::endl;
	}

	Player player(&playerTexture, sf::Vector2u(1, 1), 0.3f, 600.0f, 200.0f);
	
	std::vector<Platform> platforms;

	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(2000.0f, 50.0f), sf::Color::Red));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 200.0f), sf::Vector2f(500.0f, 350.0f), sf::Color::Blue));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f), sf::Color::Green));

	float deltaTime;
	sf::Clock clock;

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
				resizeView(window, view);
				break;
			}
		}

		player.update(deltaTime);

		Collider playerCollider = player.getCollider();

		sf::Vector2f direction;

		for (Platform platform : platforms)
			if (platform.getCollider().checkCollision(playerCollider, direction, 1.0f));
				player.onCollision(direction);

		view.setCenter(player.getPositon());

		window.clear(sf::Color(150, 150, 150));
		window.draw(background);
		window.setView(view);
		player.drawTo(window);
		for (Platform platform : platforms)
			platform.drawTo(window);
		window.display();
	}
	

	return 0;
}

//test