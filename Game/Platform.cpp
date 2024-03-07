#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setFillColor(color);
	body.setTexture(texture);
	body.setPosition(position);

}

Platform::~Platform()
{
}

void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(body);
}
