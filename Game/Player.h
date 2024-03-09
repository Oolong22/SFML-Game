#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void update(float deltaTime);
	void drawTo(sf::RenderWindow& window);
	void onCollision(sf::Vector2f direction);
	void allowDash();
	bool getisDashing();

	sf::Vector2f getPositon();
	Collider getCollider() { return Collider(body); };

public:
	bool faceRight;
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;

	sf::Vector2f velocity;

	//Jumping
	bool canJump = true;
	float jumpHeight;
	bool isJumping = false;

	//Dashing
	bool canDash = true;
	bool isDashingAllowed = true;
	bool isDashing = false;
	float dashTimer = 0.0f;
	float dashCooldown = 0.6f;
	float dashSpeed = 1500.0f;
	float dashDuration = 0.3f;
	bool inDashingAnimation = false;
};

//test