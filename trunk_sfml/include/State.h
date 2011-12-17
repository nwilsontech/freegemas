/**
 * @file State.h
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

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <SFML/Window/Event.hpp>
#include "StateManager.h"
#include "DrawingQueue.h"


class State{
public:
    State() : pManager(0) { }

    void assignStateManager(StateManager * stMg){
        pManager = stMg;
    }

    virtual void event(sf::Event theEvent){ };
    virtual void update(bool isCovered){ };
    virtual void draw(bool isCovered, DrawingQueue& queue){ };

    virtual void focusSet(){ }
    virtual void focusLost(){ }
    
    virtual void loadResources() { };
    virtual void launch() { };
    virtual void cleanup(){ };

protected:
    StateManager * pManager;

};

#endif /* _GAMESTATE_H_ */
