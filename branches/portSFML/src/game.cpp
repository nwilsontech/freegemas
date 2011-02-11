#include "game.h"
#include "state.h"

#include "log.h"


// #include "stateGame.h"
#include "stateMainMenu.h"
// #include "stateHowtoplay.h"

// #include "resManager.h"

Game::Game () : BaseWindow(800, 600, "FreeGemas v0.4") {
    lDEBUG << Log::CON("Game");
    
    imCursor.LoadFromFile("media/handCursor.png");
    spCursor.SetImage(imCursor);

    //ResourceManager::instance() -> init(graphics());    

    changeState("stateMainMenu");
}

void Game::update(){
    currentState -> update();
    spCursor.SetPosition(mouseX(), mouseY());
}

void Game::draw(DrawingManager & dMngr){
    dMngr.Draw(&spCursor, 100);
    currentState -> draw(dMngr);
}

void Game::buttonDown(sf::Key::Code button){
    currentState -> buttonDown(button);
}

void Game::buttonUp(sf::Key::Code button){
    currentState -> buttonUp(button);
}

void Game::changeState(string S){
    if(S == currentStateString)
    	return;

    if(S == "stateMainMenu"){
    	currentState . reset(new StateMainMenu(this));
    	currentStateString = "stateMainMenu";
    }
    else if(S == "stateGame"){
//    	currentState . reset(new StateGame(this));
    	currentStateString = "estadoGame";
    }
    else if(S == "stateHowtoplay"){
//    	currentState . reset(new StateHowtoplay(this));
    	currentStateString = "stateHowtoplay";
    }
    else if(S == "stateQuit"){
    	close();
    }
}

Game::~Game(){
    lDEBUG << Log::DES("Game");
}
