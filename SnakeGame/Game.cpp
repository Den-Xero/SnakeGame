#include "Game.h"
#include "Snake.h"
#include "Collectables.h"
#include <iostream>


/*
  Games Development with C++ GAV1031-N
  Snake ICA start project

  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

/* sf::Vector2f Game::GetProbPosition()
{
     Can't get to work, needed to return value NewPos but couldn't find out how to get it to collectables.cpp
    bool found{ false };
    do
    {
        float x = rand() % 80 * 10;
        float y = rand() % 60 * 10;
        sf::Vector2f NewPos{ x, y };
        found = { true };

        for (Collectables* Collectables : SCollectablesVector)
        {

            if (Collectables->GetProbPosition() == NewPos)
                found = { false };
            break;

        }

    } while (!found);
  
}*/

void Game::Run()
{
	

    // All SFML types and functions are contained in the sf namespace

   // Create an instance of the SFML RenderWindow type which represents the display
   // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : A0048295", sf::Style::Close);
    
    //Makes a snake for player to play and places it on screen
    SSnakesVector.push_back(new Snake(sf::Vector2f(400, 300)));

    //Makes the 5 collectable to be called when game is running
    for (int i = 0;i < 5;i++)
    {
        SCollectablesVector.push_back(new Collectables());
    }

    
    sf::Clock clock;

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }


       

        //checks for keypresses and change snake direction accordingly
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            SSnakesVector[0]->ChangeDirection(EDirection::DNorth);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            SSnakesVector[0]->ChangeDirection(EDirection::DWest);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            SSnakesVector[0]->ChangeDirection(EDirection::DEast);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            SSnakesVector[0]->ChangeDirection(EDirection::DSouth);
        
        for (Snake* snake : SSnakesVector)
            snake->Update();


        // We must clear the window each time around the loop
        window.clear();

        // draw our circle shape to the window
        for (Snake* snake : SSnakesVector)
        {
            if (snake->IsSAlive())
                snake->Render(window);
        }

        //Checks for collision between snake and collectables 
        for (Snake* snake : SSnakesVector)
            snake->CollisionCheckWithCollectables(SCollectablesVector, Score);

        /*for (SizeS Snake1I = 0; Snake1I<SSnakeVector.size(); Snake1I++)
        {
            for(SizeS Snake2I = Snake1I + 1; Snake2I<SSnakeVector.size();Snake2I++)
            {
                SSnakeVector[Snake1I]->CollisionWithSnake(*SSnakeVector[Snake2I]);
            }
        }*/

        //Checks for the snake colliding with itself
        for (Snake* snake : SSnakesVector)
            snake->CollisionWithSelf(window);

        //Checks for the snake colliding with wall
        for (Snake* snake : SSnakesVector)
            snake->OutOfBounds(window);

        //Spawns collectables from the vector that is set as dead at the time at random times
        if (Count == 0)
        {
            for (Collectables* Collectables : SCollectablesVector)
            {
                if ((!Collectables->IsAlive()))
                {

                    //sf::Vector2f pos = GetProbPosition();
                    Count++;

                    Collectables->CSpawn(/*pos*/);
                    break;
                }
            }
        }
        else if (Count == 20)
        {
            Count = 0;
        }
        else
        {
            Count++;
        }

        //Draws the collectables on the screen when it is set to alive 
        for (Collectables* Collectables : SCollectablesVector)
        {
            if (Collectables->IsAlive())
                Collectables->Render(window);
        }

        // Get the window to display its contents
        window.display();

        // Loop until time passed
        while (clock.getElapsedTime().asMilliseconds() < 250);
        clock.restart();

    }

    std::cout << "Your score is: " << Score;
    //Removes all the snake when the game ends
    for (Snake* snake : SSnakesVector)
        delete snake;

    
    

}
