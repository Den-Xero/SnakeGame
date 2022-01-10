#pragma once
#include <SFML/Graphics.hpp>
#include <list>
//Declaring Snake directions
enum class EDirection
{
	DNorth,
	DEast,
	DWest,
	DSouth
};


class Collectables;

//Declaring the snake class with private variables and public variables and functions
class Snake
{
private:
	bool SAlive{ true };
	EDirection SDirection{EDirection::DNorth};
	//sf::Vector2f SPosition;
	std::list<sf::Vector2f> SBodyParts;
	int SGrowAmount{ 0 };
public:
	bool IsSAlive() const { return SAlive; }
	Snake(sf::Vector2f pos);
	void ChangeDirection(EDirection NewDirection);
	void Update();
	void Render(sf::RenderWindow& window);
	void CollisionCheckWithCollectables(std::vector<Collectables*>& Collectables, int& Score);
	//void CollisionWithSnake(Snake& other);
	void CollisionWithSelf(sf::RenderWindow& window);
	void OutOfBounds(sf::RenderWindow& window);
	int Collision(sf::RenderWindow& window);
};

