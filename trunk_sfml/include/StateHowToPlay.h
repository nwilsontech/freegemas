/**
 * @file StateHowToPlay.h
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

#ifndef _STATEHOWTOPLAY_H_
#define _STATEHOWTOPLAY_H_

#include "log.h"
#include "State.h"
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

using namespace std;

class StateHowToPlay : public State{

public:
    StateHowToPlay();
    ~StateHowToPlay();

    void loadResources();
    void event(sf::Event theEvent);
    void update(bool isCovered);
    void draw(bool isCovered, DrawingQueue& queue);

private:

    /// Sprite for the background image
    sf::Sprite spBackground;

    /// String for the title
    sf::String strTitle, strTitleShadow;

    /// String for the exit message
    sf::String strExitMessage, strExitMessageShadow;

    /// Help message
    std::wstring bodyText;

    /// Strings for the help message
    std::vector<sf::String> strBodyLines;

    /// Shadows for the help message
    std::vector<sf::String> strBodyLinesShadow;
};

#endif /* _STATE1_H_ */
