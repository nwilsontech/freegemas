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
    actualWindow.Create(sf::VideoMode(width, height), title); 
    actualWindow.SetFramerateLimit(fps);

    while (actualWindow.IsOpened())
    {

        performOperations();

        // Process events
        sf::Event Event;
        while (actualWindow.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed){
                actualWindow.Close();
            }else if(!states.empty()){
                states.back() -> event(Event);
            }
        }

        actualWindow.Clear();

        update();

        draw();

        actualWindow.Display();        
    }
}


void StateManager::update(){
    if(!states.empty()){
        StateRevIt it, itEnd = states.rend();
        bool covered = false;
        for(it = states.rbegin(); it != itEnd; ++it){
            (*it) -> update(covered);
            covered = true;
        }
    }
}


void StateManager::draw(){
    DrawingQueue queue;
    DrawingQueueIterator qIt;

    if(!states.empty()){
        StateIt it, itEnd = states.end();
        bool covered = false;

        for(it = states.begin(); it != itEnd; ++it){
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
