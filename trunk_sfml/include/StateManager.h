/**
 * @file StateManager.h
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

#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <vector>
#include <queue>
#include <string>
#include <tr1/memory>
#include <map>

#include <SFML/Graphics.hpp>

class State;

class DrawingQueue : private std::multimap<float, const sf::Drawable &>{
    friend class StateManager;

public:
    void Draw(float z, const sf::Drawable & object){
        insert(std::pair<float, const sf::Drawable &>(z, object));
    }
};

// Iterator for the DrawingQueue
typedef std::multimap<float, const sf::Drawable &>::const_iterator DrawingQueueIterator;

/// Typedef for shared pointer to State
typedef std::tr1::shared_ptr<State> StatePointer;
 
class StateManager{

public:
    StateManager(int width, int height, std::string title, 
                 bool fullscreen = false, double fps = 60);

    void run();
    void changeState(StatePointer state);
    void pushState(StatePointer state);
    void popState();
    void popAllStates();

    ~StateManager();

private:

    void update();

    void draw();

    /// Actual window where everything happens
    sf::RenderWindow actualWindow;

    /// Window's width
    int width;
    
    /// Window's height
    int height;

    /// Window's title
    std::string title;

    // Window should be fullscreen or not
    bool fullscreen;

    // Update interval
    double fps;

    bool isRunning;

    /// Typedef for const iterator for vector of StatePointers
    typedef std::vector<StatePointer>::const_iterator StateIt;

    /// Typedef for const reverse iterator for vector of StatePointers
    typedef std::vector<StatePointer>::const_reverse_iterator StateRevIt;

    /// Set of states
    std::vector<StatePointer> states;

    /// Temporary state counter
    size_t numStates;

    /// Operation types
    enum tOpType { opPUSH, opPOP };

    /// Single operation
    struct StateOp{

        /// Type of the operation
        tOpType opType;

        /// State involved (if it's an opPUSH operation)
        StatePointer involvedState;

        /// Constructor
        StateOp(tOpType t_, StatePointer s_ = std::tr1::shared_ptr<State>()) 
            : opType(t_), involvedState(s_){ }
    };

    /// Queue of pending operations
    std::queue<StateOp> pendingOperations;
    
    /// Performs all pending operations
    void performOperations();
    
};


#endif /* _STATEMANAGER_H_ */
