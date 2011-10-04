#include "Game.h"
#include "StateMainMenu.h"

Game::Game(){
    // Create the window
    actualWindow.Create(sf::VideoMode(800, 600), "Freegemas"); 

    // Set the frame rate
    actualWindow.SetFramerateLimit(60);

    // Load and set the icon for the window
    appIcon.LoadFromFile("media/appIcon.png"); 
    actualWindow.SetIcon(64, 64, appIcon.GetPixelsPtr());

    // Assign the stateManager its window
    stateManager.setWindow(&actualWindow);

    // Push the first state
    stateManager.pushState(StatePointer(new StateMainMenu()));
}

void Game::go(){
    // Run the game loop
    stateManager.run();
}
