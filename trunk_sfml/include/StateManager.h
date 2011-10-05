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

// Forward declaration of the sprite
class State;

/**
 * Represents a drawing queue, where the Drawable objects will be drawn
 * depending on their depth (which is the key of the map).
 */

class DrawingQueue : private std::multimap<float, const sf::Drawable &>{
    friend class StateManager;

public:
    /// Adds a new drawable element to the drawing queue
    void Draw(float z, const sf::Drawable & object){
        insert(std::pair<float, const sf::Drawable &>(z, object));
    }
};

// Iterator for the DrawingQueue
typedef std::multimap<float, const sf::Drawable &>::const_iterator DrawingQueueIterator;

/// Typedef for shared pointer to State
typedef std::tr1::shared_ptr<State> StatePointer;
 
/**
 * Manages the different states, loading and unloading them using a stack.
 *
 * It uses a queue of operations, so multiple states can be loaded and unloaded
 * at the same time. It also handles the rendering window.
 */

class StateManager{

public:
    /// Creates a new StateManager.
    StateManager();

    /// Sets the window to be working on
    void setWindow(sf::RenderWindow * w);
    
    /// Runs the manager, showing the window and starting the game loop
    void run();

    /// Unloads the active state and loads the new one
    void changeState(StatePointer state);

    /// Loads and places a new state at the top of the states stack
    void pushState(StatePointer state);

    /// Unloads and pops the state at the top of the stack
    void popState();

    /// Unloads all of the states
    void popAllStates();

    /// Unloads all of the states and then quits
    void popAndQuit();

    /// Frees resources and quits 
    ~StateManager();

private:

    /// Launches the logical stage of the loaded states
    void update();

    /// Launches the drawing stage of the loaded states
    void draw();

    /// Actual window where everything happens
    sf::RenderWindow * actualWindow;

    bool shouldQuit;

    /// Iterator of states (points thereof)
    typedef std::vector<StatePointer>::const_iterator StateIt;

    /// Reverse iterator of states
    typedef std::vector<StatePointer>::const_reverse_iterator StateRevIt;

    /// Stack of states
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
