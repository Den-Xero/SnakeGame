#include "Collectables.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

//Sets size of collectable
constexpr float CRadius{ 10.0f };

//Draws collectable when needed
void Collectables::Render(sf::RenderWindow& window)
{

	sf::CircleShape Collectable(CRadius);
	Collectable.setPosition(CPosition);
	int R = rand() % 255;
	int G = rand() % 255;
	int B = rand() % 255;
	Collectable.setFillColor(sf::Color(R, G, B));

	window.draw(Collectable);
}

//Sets where collectable will spawn and how much it will grow the snake
void Collectables::CSpawn(/*sf::Vector2f pos*/)
{
	int x = rand() %40 * 20;
	int y = rand() %30 * 20;
	
	CPosition = sf::Vector2f ((float)x, (float)y) ;

	SGrowValue = rand() %2 + 1;

	CAlive = true;
}
