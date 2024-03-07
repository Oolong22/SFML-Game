#include "Player.h"
#include "Constants.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(200.0f, 0.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && canJump) {
		canJump = false;
		isJumping = true;
		velocity.y = -sqrt(2.0f * GRAVITY * jumpHeight);
	}

	velocity.y += GRAVITY * deltaTime;
	
	if (velocity.x == 0.0f) {
		row = 0;
	}
	else {
		row = 0;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

sf::Vector2f Player::getPositon() { return body.getPosition(); }

void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		//Collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		//Collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		//Collision on the bottom
		if (!isJumping)
			velocity.y = 0.0f;
		canJump = true;
		isJumping = false; //To prevent snapping to surface
	}
	else if (direction.y > 0.0f) {
		//Collision on the top
		velocity.y = 0.0f;
	}
}

//te