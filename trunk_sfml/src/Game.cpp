#include "Game.h"
#include "StateMainMenu.h"

Game::Game() : StateManager (800, 600, "Freegemas"){
    pushState(StatePointer(new StateMainMenu()));
}

void Game::go(){
    lDEBUG << "GO!";
    StateManager::run();
}
