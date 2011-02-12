#ifndef _STATEMAINMENU_H_
#define _STATEMAINMENU_H_

#include "state.h"
//#include "resManager.h"
#include "jewelGroupAnim.h"

#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <utility>
using namespace std;

class Game;

class StateMainMenu : public State{
public:

    StateMainMenu(Game * p);

    void update();

    void draw(DrawingManager & dMngr);

    void buttonDown(sf::Key::Code B);

    ~StateMainMenu();

private:

    enum transitionState{ TransitionIn,
			  Active,
			  TransitionOut };

    transitionState currentTransitionState;

    int animationCurrentStep;
    int animationLogoSteps;
    int animationTotalSteps;
			  
    sf::Image imgBackground;
    sf::Sprite sprBackground;

    sf::Image imgLogo;
    sf::Sprite sprLogo;

    sf::Image imgHighl;
    sf::Sprite sprHighl;

    sf::Font font;
    JewelGroupAnim jewelAnim;

    // Menu configuration

    int menuSelectedOption;
    vector<string> menuOptions;
    vector<sf::String> menuImages, menuShadows;

    void optionChosen();
    
    int menuYStart, menuYEnd, menuYGap;
    int menuXStart, menuXEnd;

};

#endif /* _STATEMAINMENU_H_ */
