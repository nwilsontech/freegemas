/**
 * @file JewelGroupAnim.h
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

#ifndef _JEWELGROUPANIM_H_
#define _JEWELGROUPANIM_H_

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "StateManager.h"

/**
 * @class JewelGroupAnim
 *
 * @brief Encapsulates the animation of the jewels in the Main Menu
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class JewelGroupAnim{
public:

    /// Loads all the resources
    void loadResources(){
        imgGems[0].LoadFromFile("media/gemWhite.png");
        imgGems[1].LoadFromFile("media/gemRed.png");
        imgGems[2].LoadFromFile("media/gemPurple.png");
        imgGems[3].LoadFromFile("media/gemOrange.png");
        imgGems[4].LoadFromFile("media/gemGreen.png");
        imgGems[5].LoadFromFile("media/gemYellow.png");
        imgGems[6].LoadFromFile("media/gemBlue.png");

        for (int i = 0; i < 7; ++i)
        {
            imgGems[i].SetSmooth(false);
            spGems[i].SetImage(imgGems[i]);
            spGems[i].SetX(800 / 2 - (65 * 7) / 2 + i * 65);
        }

        animationCurrentStep = 0;
        animationTotalSteps = 30;
        posFinalY = 265;
    }

    /// Updates the animation and then draws the jewels
    void draw(DrawingQueue& queue){
        if(animationCurrentStep < 7 * 5 + animationTotalSteps)
            ++animationCurrentStep;

        for(int i = 0; i < 7; ++i)
        {
            int composedStep = animationCurrentStep - i * 5;
            if(composedStep < 0) continue;

            if(composedStep < animationTotalSteps){
                spGems[i].SetY(Animation::easeOutCubic(
                                   (float) composedStep, 
                                   600.f, 
                                   (float) posFinalY - 600.f, 
                                   (float) animationTotalSteps));
            }else{
                spGems[i].SetY(posFinalY);;
            }

            queue.Draw(5, spGems[i]);
        }
    }

private:
    sf::Image imgGems[7];
    sf::Sprite spGems[7];

    int posFinalY;
    int animationCurrentStep;
    int animationTotalSteps;

};


#endif /* _JEWELGROUPANIM_H_ */
