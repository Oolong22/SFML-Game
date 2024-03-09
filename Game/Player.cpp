#include "Player.h"
#include "Constants.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float animationTime, float speed, float jumpHeight) :
	animation(texture, imageCount, animationTime / imageCount.x) //Divide by imageCount.x to get the time for each frame
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

void Player::allowDash()
{
	isDashingAllowed = true;
}

bool Player::getisDashing()
{
	return isDashing;
}

sf::Vector2f Player::getPositon() { return body.getPosition(); }

void Player::update(float deltaTime)
{
	velocity.x = 0.0f;
	if (!isDashing) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocity.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocity.x += speed;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && canJump) {
			canJump = false;
			isJumping = true;
			velocity.y = -sqrt(2.0f * GRAVITY * jumpHeight);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && canDash && isDashingAllowed && !isDashing) {
			isDashing = true;
			canDash = false;
			isDashingAllowed = false;
			dashTimer = 0.0f;
			velocity.y = 0.0f;
		}
	}

	if (isDashing) {
		if (faceRight) {
			velocity.x = dashSpeed;
		}
		else {
			velocity.x = -dashSpeed;
		}

		dashTimer += deltaTime;
		if (dashTimer >= dashDuration) {
			isDashing = false;
			inDashingAnimation = false;
		}
	}
	else {
		dashTimer += deltaTime;
		if (dashTimer >= dashCooldown) {
			canDash = true;
		}
	}

	//Gravity
	if (!isDashing)
		velocity.y += GRAVITY * deltaTime;
	
	if (velocity.x == 0.0f) {
		row = 0;
	}
	else if (isDashing) {
		row = 3;
	}
	else if (isJumping) {
		row = 2;
	}
	else {
		row = 1;
	}

	if (row != previousRow) {
		animation.reset();
		std::cout << "reset" << std::endl;
	}

	animation.update(row, deltaTime, faceRight);
	previousRow = row;
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}