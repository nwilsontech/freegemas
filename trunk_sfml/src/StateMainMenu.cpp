#include "StateMainMenu.h"
#include "StateHowToPlay.h"
#include "StateGame.h"
#include "ResourceManager.h"

#include "i18n.h"

template <typename T, typename R>
T clamp(T v, R bottom, R top){
    if(v > top) return top;
    if(v < bottom) return bottom;
    return v;
}

StateMainMenu::StateMainMenu(){
    lDEBUG << Log::CON("StateMainMenu");
}

StateMainMenu::~StateMainMenu(){
    lDEBUG << Log::DES("StateMainMenu");
}

void StateMainMenu::loadResources (){
    jewelGroupAnim.loadResources();

    // Load background image
    spBackground.SetImage (ResMgr -> getImage("media/stateMainMenu/mainMenuBackground.png"));

    // Load image for logo
    spLogo.SetImage (ResMgr -> getImage("media/stateMainMenu/mainMenuLogo.png"));
    spLogo.SetPosition(86, 0);

    // Load highlight
    spHighl.SetImage(ResMgr -> getImage("media/stateMainMenu/menuHighlight.png"));

    // Animation values
    animationTotalSteps = 30;
    animationLogoSteps = 30;
    animationCurrentStep = 0;

    // Set menu options 
    MenuOption m;
    sf::Font & menuFont = ResMgr -> getFont("media/fuenteMenu.ttf", 30);

    // Create menu options
    m.targetState = "stateGame";
    m.text = sf::String (_("Timetrial mode"), menuFont);
    m.shadow = m.text;
    m.shadow.SetColor(sf::Color(0,0,0,125));
    menuOptions.push_back(m);

    m.targetState = "stateHowToPlay";
    m.text = sf::String (_("How to play?"), menuFont);
    m.shadow = m.text;
    m.shadow.SetColor(sf::Color(0,0,0,125));
    menuOptions.push_back(m);

    m.targetState = "stateQuit";
    m.text = sf::String (_("Exit"), menuFont);
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

    currentTransitionState = TransitionIn;
}

void StateMainMenu::event (sf::Event theEvent){

    // If a key is pressed
    if (theEvent.Type == sf::Event::KeyPressed){

        // If enter is pressed, go and launch the highlighted option
        if (theEvent.Key.Code == sf::Key::Return){
            optionChosen();
        } else if (theEvent.Key.Code == sf::Key::Up){
            // Ninja technique to easily process wrapping options
            menuSelectedOption = (menuSelectedOption + menuOptions.size() - 1) % menuOptions.size();
        } else if (theEvent.Key.Code == sf::Key::Down){
            menuSelectedOption = (menuSelectedOption + menuOptions.size() + 1) % menuOptions.size();
        }
    }

    else if(theEvent.Type == sf::Event::MouseMoved){
        int mY = (int) theEvent.MouseMove.Y;

        if(mY >= menuYStart && mY < menuYEnd){
            menuSelectedOption = (mY - menuYStart) / menuYGap;
        }
    }

    else if (theEvent.Type == sf::Event::MouseButtonReleased){
        int mY = (int) theEvent.MouseMove.Y;

        if(mY >= menuYStart && mY < menuYEnd){
            optionChosen();
        }
    }
}

void StateMainMenu::optionChosen(){
    std::string nextState = menuOptions[menuSelectedOption].targetState;

    if (nextState == "stateGame"){
        pManager -> pushState(StatePointer(new StateGame()));
    } else if (nextState == "stateHowToPlay"){
        pManager -> pushState(StatePointer(new StateHowToPlay()));
    } else if (nextState == "stateQuit"){
        pManager -> popAndQuit();
    }

}

void StateMainMenu::update(bool isCovered){
    if (isCovered) return;

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

    jewelGroupAnim.draw(queue);

    int logoAlfa = clamp( (int)(255 * (float)animationCurrentStep / animationLogoSteps), 0, 255);
    spLogo.SetColor(sf::Color(255, 255, 255, logoAlfa));
    queue.Draw(1, spLogo);

    for(int i = 0, s = (int) menuOptions.size(); i < s; ++i){
        queue.Draw(3, menuOptions[i].text);
        queue.Draw(2.5, menuOptions[i].shadow);
    }

    spHighl.SetPosition(266, menuYStart + 2 + menuSelectedOption * menuYGap);
    queue.Draw(2, spHighl);

}
