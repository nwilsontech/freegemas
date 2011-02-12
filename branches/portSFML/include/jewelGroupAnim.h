#ifndef _JEWELGROUPANIM_H_
#define _JEWELGROUPANIM_H_

#include <SFML/Graphics.hpp>


#include <boost/shared_ptr.hpp>
#include "game.h"

#include <cmath>


class JewelGroupAnim{
public:
    JewelGroupAnim(){
	imgGems[0].LoadFromFile("media/gemWhite.png");
	imgGems[1].LoadFromFile("media/gemRed.png");
	imgGems[2].LoadFromFile("media/gemPurple.png");
	imgGems[3].LoadFromFile("media/gemOrange.png");
	imgGems[4].LoadFromFile("media/gemGreen.png");
	imgGems[5].LoadFromFile("media/gemYellow.png");
	imgGems[6].LoadFromFile("media/gemBlue.png");

	sprGems[0].SetImage(imgGems[0]);
	sprGems[1].SetImage(imgGems[1]);
	sprGems[2].SetImage(imgGems[2]);
	sprGems[3].SetImage(imgGems[3]);
	sprGems[4].SetImage(imgGems[4]);
	sprGems[5].SetImage(imgGems[5]);
	sprGems[6].SetImage(imgGems[6]);

	for (int i = 0; i < 7; ++i)
	{
	    sprGems[i].SetPosition(std::floor(800 / 2 - (65 * 7) / 2 + i * 65), 600);
	}

	animationCurrentStep = 0;
	animationTotalSteps = 30;
	posFinalY = 265;
    }

    void update(){
	if(animationCurrentStep < 7 * 5 + animationTotalSteps)
	    ++animationCurrentStep;

	for(int i = 0; i < 7; ++i)
	{
	    int composedStep = animationCurrentStep - i * 5;
	    if(composedStep < 0) continue;

	    if(composedStep < animationTotalSteps){
		sprGems[i].SetY(eqMovOut((float) composedStep, 
					 600.0, 
					 (float) posFinalY - 600., 
					 (float) animationTotalSteps));
	    }else{
		sprGems[i].SetY(posFinalY);
	    }
	}
    }

    void draw(DrawingManager & dMngr){
	for(int i = 0; i < 7; ++i){
	    dMngr.Draw(&sprGems[i], 2);
	}
    }

    // past time, begining pos, change, duration
    float eqMovOut(float t, float b, float c, float d) {
	/* //quad
	   t/=d;
	   h	return -c *(t)*(t-2) + b;
	//*/

	// cubic
	t=t/d-1;
	return c*(t*t*t + 1) + b;
    };
    
private:
    sf::Image imgGems[7];
    sf::Sprite sprGems[7];

    int posX[7], posFinalY;
    
    int animationCurrentStep;
    int animationTotalSteps;

};


#endif /* _JEWELGROUPANIM_H_ */
