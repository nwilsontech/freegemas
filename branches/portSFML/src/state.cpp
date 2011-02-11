#include <SFML/Graphics.hpp>
#include "state.h"

State::State(Game * p) : parent(p){
    lDEBUG << Log::CON("State");
}

State::~State(){
    lDEBUG << Log::DES("State");
}
