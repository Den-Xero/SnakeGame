#include "Snake.h"
#include "Collectables.h"
#include <stdlib.h>
#include <iostream>

//sets the snake size
constexpr float SRadius{ 10.0f };

//How the snake grows
Snake::Snake(sf::Vector2f pos)
{
	SBodyParts.push_back(pos);
}

//How the snake changes direction
void Snake::ChangeDirection(EDirection NewDirection)
{
	SDirection = NewDirection;
}

void Snake::Update()
{
	sf::Vector2f Position = SBodyParts.front();
	switch (SDirection)
	{
	case EDirection::DNorth:
		Position.y -= SRadius * 2.0f;
		break;
	case EDirection::DEast:
		Position.x += SRadius * 2.0f;
		break;
	case EDirection::DWest:
		Position.x -= SRadius * 2.0f;
		break;
	case EDirection::DSouth:
		Position.y += SRadius * 2.0f;
		break;
	default:
		break;
	}

	//Adding new part then removing from the back
	SBodyParts.push_front(Position);
	
	if (SGrowAmount > 0)
	{
		SGrowAmount--;
	}
	else
	{
		SBodyParts.pop_back();
	}



}
//Draw snake
void Snake::Render(sf::RenderWindow& window)
{
	sf::CircleShape Head(SRadius);
	Head.setFillColor(sf::Color::Cyan);
	
	for (sf::Vector2f pos : SBodyParts)
	{
		Head.setPosition(pos);
		window.draw(Head);
	}
}

//What happens when collision with collectables occurs 
void Snake::CollisionCheckWithCollectables(std::vector<Collectables*>& Collectable, int& Score)
{
	for (Collectables* Collect : Collectable)
	{
		if (Collect->IsAlive())
		{
			if (SBodyParts.front() == Collect->GetProbPosition())
			{
				SGrowAmount = Collect->GetGrowValue();
				Score += Collect->GetGrowValue();
				Collect->Collected();
			}
		}
	}
}

/*void Snake::CollisionWithSnake(Snake& other)
{
	for (sf::Vector2f OtherBodyPos : other.SBodyParts)
	{
		for (sf::Vector2f AllSegPos : SBodyParts)
		{
			if (AllSegPos == OtherBodyPos)
			{
				Snake->Collision();
			}
		}
	}
}*/

//What happens when collision with self occurs 
void Snake::CollisionWithSelf(sf::RenderWindow& window)
{
	bool First{true};
	for (sf::Vector2f AllSegPos : SBodyParts)
	{
		if (First)
		{
			First = false;
			continue;
		}
			if (SBodyParts.front() == AllSegPos)
			{
				Collision(window);
			}
	}
}


void Snake::OutOfBounds(sf::RenderWindow& window)
{
	sf::Vector2f Position = SBodyParts.front();
	if (Position.x < 0)
	{
		Collision(window);
	}
	else if (Position.x > 800)
	{
		Collision(window);
	}
	else if (Position.y < 0)
	{
		Collision(window);
	}
	else if (Position.y > 600)
	{
		Collision(window);
	}
}

//How snake is killed and removed form game when colliding with self, other snakes are out of bounds
int Snake::Collision(sf::RenderWindow& window)
{
	SAlive = false;
	window.close();
	std::cout << "SnakeGame: Finished" << std::endl;
	return 0;
}
