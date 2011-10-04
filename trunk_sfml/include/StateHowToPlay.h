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
    void loadResources();
    void event(sf::Event theEvent);
    void update(bool isCovered);
    void draw(bool isCovered, DrawingQueue& queue);

private:

    /*
    /// Possible states of the transition
    enum transitionState{ TransitionIn,
			  Active,
			  TransitionOut };

    /// Current transition state
    transitionState currentTransitionState;

    /// Current step of the animation
    int animationCurrentStep;

    /// Logo animation's total steps
    int animationLogoSteps;

    /// General animation's total steps
    int animationTotalSteps;
			  
    //*/

    /// Image for the background
    sf::Image imgBackground;
    sf::Sprite spBackground;

    // Font for the title
    sf::Font fontTitle;

    // Font for the subtitle
    sf::Font fontSubtitle;

    sf::String strTitle;
    sf::String strExitMessage;

    std::wstring bodyText;
};

#endif /* _STATE1_H_ */
