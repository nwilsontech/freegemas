#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"


State::State(Game * p) : parent(p), drawingDeclared(false){
    lDEBUG << Log::CON("State");
}

State::~State(){
    lDEBUG << Log::DES("State");
}
