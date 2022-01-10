#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class Snake;
class Collectables;

//Declaring the game class with private variables and public variables and functions
class Game
{
private:
	std::vector<Snake*> SSnakesVector;
	std::vector<Collectables*> SCollectablesVector;
	int Count{ 0 };
	int Score{ 0 };
	//sf::Vector2f GetProbPosition();
public:
	void Run();
};

