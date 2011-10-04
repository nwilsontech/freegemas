/**
 * @file StateManager.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2011
 *
 * Copyright (C) 2011 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#include "StateManager.h"
#include "State.h"
#include "log.h"

StateManager::StateManager (int width, int height, std::string title,
                            bool fullscreen, double fps)
    : width (width), height (height), title(title),
      fullscreen (fullscreen), fps(fps), isRunning(false)
{

    lDEBUG << Log::CON("StateManager");
    numStates = 0;
}

void StateManager::run(){

    // Creates the window
    actualWindow.Create(sf::VideoMode(width, height), title); 

    // Sets the frame rate
    actualWindow.SetFramerateLimit(fps);

    // Starts the game loop
    while (actualWindow.IsOpened())
    {

        // Perform push and pop operations over the stack of states
        performOperations();

        // Process events
        sf::Event Event;

        // Iterate all of the events
        while (actualWindow.GetEvent(Event))
        {
            // If window gets closed
            if (Event.Type == sf::Event::Closed){
                
                // close the app
                actualWindow.Close();

            }
            // Else, redirect all of the events to the current (topmost) state
            else if(!states.empty()){
                states.back() -> event(Event);
            }
        }

        // Perform logical stage
        update();

        // Clear the window
        actualWindow.Clear();

        // Perform graphical stage
        draw();

        // Display everything on screen
        actualWindow.Display();        
    }
}


void StateManager::update(){

    // If there are states
    if(!states.empty()){

        // Initialise iterators
        StateRevIt it = states.rbegin();
        StateRevIt itEnd = states.rend();

        (*it++) -> update(false);
        
        for( ; it != itEnd; ++it){
            (*it) -> update(true);
        }
    }
}


void StateManager::draw(){
    if(!states.empty()){
        DrawingQueue queue;
        DrawingQueueIterator qIt;

        StateRevIt it;
        StateRevIt itEnd = states.rend();

        bool covered = false;

        for(it = states.rbegin(); it != itEnd; ++it){
            queue.clear();
            (*it) -> draw(covered, queue);
            
            for (qIt = queue.begin(); qIt != queue.end(); ++qIt){
                actualWindow.Draw(qIt -> second);
            }
            covered = true;
        }
    }
}

void StateManager::changeState(StatePointer state){
    lDEBUG << "ChangeState requested";

    if(!states.empty()){
        popState();
    }
    pushState(state);
}

void StateManager::pushState(StatePointer state){
    lDEBUG << "Push requested";

    pendingOperations.push (StateOp(opPUSH, state));
    ++numStates;
}

void StateManager::popState(){
    lDEBUG << "Pop requested";

    pendingOperations.push (StateOp(opPOP));
    --numStates;
}

void StateManager::popAllStates(){
    lDEBUG << "Pop all states requested";

    while(numStates > 0){
        popState();
    }    
}

void StateManager::performOperations(){
    if(!pendingOperations.empty()){
        lDEBUG << "Performing " << pendingOperations.size() << " operations...";
    }

    while(!pendingOperations.empty()){
        StateOp currentOperation = pendingOperations.front();

        if(currentOperation.opType == opPUSH){
            currentOperation.involvedState -> assignStateManager(this);
            currentOperation.involvedState -> loadResources();
            states.push_back(currentOperation.involvedState);
            lDEBUG << "Performed push";
        }

        else if(currentOperation.opType == opPOP){
            states.back() -> cleanup();
            states.pop_back();
            lDEBUG << "Performed pop";
        }

        pendingOperations.pop();
    }
}

StateManager::~StateManager(){
    lDEBUG << Log::DES("StateManager");

    popAllStates();
    performOperations();
}
