#include "game.h"
#include "log.h"

#include "stateMainMenu.h"

#include "inter.h"


#include <algorithm>
#include <string>
#include <functional>
#include <cmath>




template <typename T, typename R>

T clamp(T v, R bottom, R top){
    if(v > top) return top;
    if(v < bottom) return bottom;
    return v;
}

StateMainMenu::StateMainMenu(Game * p) : State(p){
    lDEBUG << Log::CON("StateMainMenu");
    
    currentTransitionState = TransitionIn;

    imgBackground.LoadFromFile("media/stateMainMenu/mainMenuBackground.png");
    sprBackground.SetImage(imgBackground);
    sprBackground.SetPosition(0,0);

    imgLogo.LoadFromFile("media/stateMainMenu/mainMenuLogo.png");
    sprLogo.SetImage(imgLogo);
    sprLogo.SetPosition(86,0);

    imgHighl.LoadFromFile("media/stateMainMenu/menuHighlight.png");
    sprHighl.SetImage(imgHighl);

    font.LoadFromFile("media/fuenteMenu.ttf");

    animationTotalSteps = 30;
    animationLogoSteps = 30;
    animationCurrentStep = 0;


    // MENÚ

    menuSelectedOption = 0;
    menuYStart = 350;
    menuYGap = 42;

    menuOptions.push_back(make_pair(sf::String(L"Modo contrarreloj", font, 30.0f), "stateGame"));    
    menuOptions.push_back(make_pair(sf::String(L"¿Cómo se juega?", font, 30.0f), "stateHowtoplay"));
    menuOptions.push_back(make_pair(sf::String(L"Salir", font, 30.0f), "stateQuit"));

    int widestMenuEntry = 0;

    for(size_t i = 0, s = menuOptions.size(); i < s; ++i)
    {
	int thisMenuEntryWidth = menuOptions[i].first.GetRect().GetWidth();

	menuOptions[i].first.SetPosition(
	    floor(800 / 2 - thisMenuEntryWidth / 2),
	    menuYStart + i * menuYGap);

	if(widestMenuEntry < thisMenuEntryWidth){
	    widestMenuEntry = thisMenuEntryWidth;
	}
    }

    menuYEnd = 350 + (int) menuOptions.size() * menuYGap;

    menuXStart = 800 / 2 - widestMenuEntry / 2;
    menuXEnd = menuXStart + widestMenuEntry;

}

void StateMainMenu::update(){
    if(currentTransitionState == TransitionIn){
    	animationCurrentStep ++;

    	if(animationCurrentStep == animationTotalSteps){
    	    currentTransitionState = Active;
    	}

    } else if(currentTransitionState == Active){

    } else if(currentTransitionState == TransitionOut){

    }

    int mY = (int) parent -> mouseY();

    if(mY >= menuYStart && mY < menuYEnd){
    	menuSelectedOption = (mY - menuYStart) / menuYGap;
    }
}

void StateMainMenu::draw(DrawingManager & dMngr){
    dMngr.Draw(&sprBackground, 1);

    int logoAlfa = clamp( (int)(255 * (float)animationCurrentStep / animationLogoSteps),
    			  0, 255);

    sprLogo.SetColor(sf::Color(255, 255, 255, logoAlfa));
    dMngr.Draw(&sprLogo, 2);

    for(size_t i = 0, s = menuOptions.size(); i < s; ++i)
    {
	dMngr.Draw(&menuOptions[i].first, 2);
    }
    
    
    jewelAnim . draw(dMngr);

    // imgHighl -> draw(266, menuYStart + 5 + menuSelectedOption * menuYGap, 2);
}

void StateMainMenu::buttonDown(sf::Key::Code B){
    if(B == sf::Key::Escape){
    	parent -> close();
    } 

    // else if(B == Gosu::kbSpace){
    // 	parent -> changeState("stateGame");
    // } 

    // else if(B == Gosu::kbR){
    // 	parent -> changeState("stateHowtoplay");
    // }

    // else if(B == Gosu::kbDown){
    // 	if(++menuSelectedOption == (int)menuOptions.size()){
    // 	    menuSelectedOption = 0;
    // 	}
    // }

    // else if(B == Gosu::kbUp){
    // 	if(--menuSelectedOption == -1){
    // 	    menuSelectedOption = (int) menuOptions.size() - 1;
    // 	}
    // }

    // else if(B == Gosu::kbReturn || B == Gosu::kbEnter){
    // 	optionChosen();
    // }

    // else if(B == Gosu::msLeft){
    // 	int mX = (int) parent -> input().mouseX();
    // 	int mY = (int) parent -> input().mouseY();

    // 	if(mX >= menuXStart && mX <= menuXEnd &&
    // 	   mY >= menuYStart && mY <= menuYEnd){
    // 	    optionChosen();
    // 	}
    // }
}

void StateMainMenu::optionChosen(){    
    //parent -> changeState(menuOptions[menuSelectedOption].second);
}

StateMainMenu::~StateMainMenu(){
    lDEBUG << Log::DES("StateMainMenu");
}
