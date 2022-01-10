#pragma once
#include <SFML/Graphics.hpp>

//Declaring the collectable class with private variables and public variables and functions
class Collectables
{
private:
	bool CAlive{ false };
	sf::Vector2f CPosition;
	int SGrowValue{ 0 };
public:
	bool IsAlive() const { return CAlive;}
	void Render(sf::RenderWindow& window);
	void CSpawn(/*sf::Vector2f pos*/);
	void Collected() { CAlive = false; };
	int GetGrowValue() const { return SGrowValue; };
	sf::Vector2f GetProbPosition() const { return CPosition; }
};

