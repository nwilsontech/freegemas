#include "StateMainMenu.h"
#include "StateHowToPlay.h"

#include "i18n.h"

template <typename T, typename R>
T clamp(T v, R bottom, R top){
    if(v > top) return top;
    if(v < bottom) return bottom;
    return v;
}

void StateMainMenu::loadResources (){
    // Load background image
    imgBackground.LoadFromFile("media/stateMainMenu/mainMenuBackground.png");
    spBackground.SetImage (imgBackground);

    // Load image for logo
    imgLogo.LoadFromFile("media/stateMainMenu/mainMenuLogo.png");
    imgLogo.SetSmooth(false);
    spLogo.SetImage (imgLogo);
    spLogo.SetPosition(86, 0);

    // Load highlight
    imgHighl.LoadFromFile("media/stateMainMenu/menuHighlight.png");
    imgHighl.SetSmooth(false);
    spHighl.SetImage(imgHighl);

    // Load font for menu
    menuFont.LoadFromFile("media/fuenteMenu.ttf");
    
    // Animation values
    animationTotalSteps = 30;
    animationLogoSteps = 30;
    animationCurrentStep = 0;

    // Set menu options 
    MenuOption m;

    // Create menu options
    m.targetState = "stateGame";
    m.text = sf::String (_("Timetrial mode"), menuFont, 30);
    m.shadow = m.text;
    m.shadow.SetColor(sf::Color(0,0,0,125));
    menuOptions.push_back(m);

    m.targetState = "stateHowToPlay";
    m.text = sf::String (_("How to play?"), menuFont, 30);
    m.shadow = m.text;
    m.shadow.SetColor(sf::Color(0,0,0,125));
    menuOptions.push_back(m);

    m.targetState = "stateQuit";
    m.text = sf::String (_("Exit"), menuFont, 30);
    m.shadow = m.text;
    m.shadow.SetColor(sf::Color(0,0,0,125));
    menuOptions.push_back(m);

    // Set menu variables
    menuSelectedOption = 0;
    
    // Menu top
    menuYStart = 350;
    
    // Separation between menu items
    menuYGap = 42;

    // Menu bottom
    menuYEnd = menuYStart + (int) menuOptions.size() * menuYGap;

    // Set menu options positions
    for(int i = 0, s = (int) menuOptions.size(); i < s; ++i){
		int hor = int (800 / 2 - menuOptions[i].text.GetRect().GetWidth() / 2);
        menuOptions[i].text.SetPosition(hor, menuYStart + i * menuYGap);
        menuOptions[i].shadow.SetPosition(hor, menuYStart + i * menuYGap + 2);
    }

    menuXStart = 0;
    menuXEnd = 800;
}

void StateMainMenu::event (sf::Event theEvent){
    if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Space){
        pManager -> pushState(StatePointer(new StateHowToPlay()));
        lDEBUG << "WUT";
    }

    else if(theEvent.Type == sf::Event::MouseMoved){
        int mY = (int) theEvent.MouseMove.Y;

        if(mY >= menuYStart && mY < menuYEnd){
            menuSelectedOption = (mY - menuYStart) / menuYGap;
        }
    }
}

void StateMainMenu::update(bool isCovered){
    if(currentTransitionState == TransitionIn){
        animationCurrentStep ++;

        if(animationCurrentStep == animationTotalSteps){
            currentTransitionState = Active;
        }

    } else if(currentTransitionState == Active){
        // None
    } else if(currentTransitionState == TransitionOut){
        // None
    }
}

void StateMainMenu::draw (bool isCovered, DrawingQueue& queue){
    if (isCovered) return;

    queue.Draw(0, spBackground);

    int logoAlfa = clamp( (int)(255 * (float)animationCurrentStep / animationLogoSteps), 0, 255);
    spLogo.SetColor(sf::Color(255, 255, 255, logoAlfa));
    queue.Draw(1, spLogo);

    for(int i = 0, s = (int) menuOptions.size(); i < s; ++i){
        queue.Draw(3, menuOptions[i].text);
        queue.Draw(2.5, menuOptions[i].shadow);
    }

    //jewelAnim . draw();

    spHighl.SetPosition(266, menuYStart + 2 + menuSelectedOption * menuYGap);
    queue.Draw(2, spHighl);

}
