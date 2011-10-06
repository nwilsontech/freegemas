/**
 * @file Game.h
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

#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>

#include "StateManager.h"

/**
 * Main control class. It launches the window, the state manager and the initial state
 */

class Game {

public:
    /// Creates the basic window and initialises the first state
    Game();

    /// Game destructor
    ~Game();

    /// Starts the game loop
    void go();

private:

    // Window where everything happens
    sf::RenderWindow actualWindow;

    /// State Manager
    StateManager stateManager;

    /// Image for the icon of the app
    sf::Image appIcon;
};

#endif /* _GAME_H_ */
