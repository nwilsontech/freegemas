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
    
    // Current State
    currentTransitionState = TransitionIn;

    // Load the image for the background
    imgBackground.LoadFromFile("media/stateMainMenu/mainMenuBackground.png");
    sprBackground.SetImage(imgBackground);
    sprBackground.SetPosition(0,0);

    // Load the image for the logo
    imgLogo.LoadFromFile("media/stateMainMenu/mainMenuLogo.png");
    sprLogo.SetImage(imgLogo);
    sprLogo.SetPosition(86,0);

    // Load the image for the highlight
    imgHighl.LoadFromFile("media/stateMainMenu/menuHighlight.png");
    sprHighl.SetImage(imgHighl);
    sprHighl.SetX(266);

    // Load the font for the menu entries
    font.LoadFromFile("media/fuenteMenu.ttf");

    // Properties of the animation of the logo
    animationTotalSteps = 30;
    animationLogoSteps = 30;
    animationCurrentStep = 0;


    // MENÚ

    menuSelectedOption = 0;
    menuYStart = 350;
    menuYGap = 42;

    // Menu options
    menuOptions.push_back("stateGame");    
    menuOptions.push_back("stateHowtoplay");
    menuOptions.push_back("stateQuit");

    // Menu entries images
    menuImages.push_back(sf::String(L"Modo contrarreloj", font, 30.0f));
    menuImages.push_back(sf::String(L"¿Cómo se juega?", font, 30.0f));
    menuImages.push_back(sf::String(L"Salir", font, 30.0f));

    // Menu entries shadows
    menuShadows = menuImages;

    // Compute the widest menu option
    int widestMenuEntry = 0;

    for(size_t i = 0, s = menuImages.size(); i < s; ++i)
    {
	int thisMenuEntryWidth = menuImages[i].GetRect().GetWidth();

	// Set the position for the menu entry
	menuImages[i].SetPosition(
	    floor(800 / 2 - thisMenuEntryWidth / 2),
	    menuYStart + i * menuYGap);

	// Set the position for the shadow
	menuShadows[i].SetPosition(
	    floor(800 / 2 - thisMenuEntryWidth / 2) + 2,
	    menuYStart + i * menuYGap + 2);

	// Set the color for the shadow
	menuShadows[i].SetColor(sf::Color(0,0,0,125));

	if(widestMenuEntry < thisMenuEntryWidth){
	    widestMenuEntry = thisMenuEntryWidth;
	}
    }
    
    // Bottom limit of the menu
    menuYEnd = 350 + (int) menuImages.size() * menuYGap;

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

    sprHighl.SetY(menuYStart + 1 + menuSelectedOption * menuYGap);

    int logoAlfa = clamp( (int)(255 * (float)animationCurrentStep / animationLogoSteps),
    			  0, 255);

    sprLogo.SetColor(sf::Color(255, 255, 255, logoAlfa));

    jewelAnim.update();
}

void StateMainMenu::draw(DrawingManager & dMngr){
    if(!drawingDeclared){
	lDEBUG << "Declaring drawing queue";
	drawingDeclared = true;
	dMngr.Draw(&sprBackground, 1);
	dMngr.Draw(&sprLogo, 2);
	dMngr.Draw(&sprHighl, 1.8);

	jewelAnim.draw(dMngr);

	for(size_t i = 0, s = menuImages.size(); i < s; ++i)
	{
	    dMngr.Draw(&menuImages[i], 2);
	    dMngr.Draw(&menuShadows[i], 1.9);
	}
    }
}

void StateMainMenu::buttonDown(sf::Key::Code B){
    if(B == sf::Key::Escape){
	parent -> drawingManager.clear();
    	parent -> close();
    } 

    else if(B == sf::Key::Space){
    	parent -> changeState("stateGame");
    } 

    else if(B == sf::Key::R){
    	parent -> changeState("stateHowtoplay");
    }

    else if(B == sf::Key::Down){
    	if(++menuSelectedOption == (int)menuOptions.size()){
    	    menuSelectedOption = 0;
    	}
    }

    else if(B == sf::Key::Up){
    	if(--menuSelectedOption == -1){
    	    menuSelectedOption = (int) menuOptions.size() - 1;
    	}
    }

    else if(B == sf::Key::Return){
    	optionChosen();
    }

    // else if(B == Gosu::msLeft){
    // 	int mX = (int) parent -> mouseX();
    // 	int mY = (int) parent -> mouseY();

    // 	if(mX >= menuXStart && mX <= menuXEnd &&
    // 	   mY >= menuYStart && mY <= menuYEnd){
    // 	    optionChosen();
    // 	}
    // }
}

void StateMainMenu::optionChosen(){    
    parent -> changeState(menuOptions[menuSelectedOption]);
}

StateMainMenu::~StateMainMenu(){

    lDEBUG << Log::DES("StateMainMenu");
}
