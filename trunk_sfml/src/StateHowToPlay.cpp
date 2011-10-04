#include "StateHowToPlay.h"
#include "i18n.h"

StateHowToPlay::StateHowToPlay(){
    lDEBUG << Log::CON("StateHowToPlay");
}

StateHowToPlay::~StateHowToPlay(){
    lDEBUG << Log::DES("StateHowToPlay");
}

void StateHowToPlay::loadResources(){
    bodyText = L"";
    bodyText += _("The objective of the game is to swap one gem with an adjacent gem to form a horizontal or vertical chain of three or more gems.");
    bodyText += L"\n\n";
    bodyText += _("Click the first gem and then click the gem you want to swap it with. If the movement is correct, they will swap and the chained gems will disappear.");
    bodyText += L"\n\n";
    bodyText += _("Bonus points are given when more than three identical gems are formed. Sometimes chain reactions, called cascades, are triggered, where chains are formed by the falling gems. Cascades are awarded with bonus points.");

    imgBackground.LoadFromFile("media/howtoScreen.png");
    imgBackground.SetSmooth(false);
    spBackground.SetImage(imgBackground);

    fontTitle.LoadFromFile("media/fuenteMenu.ttf");
    strTitle = sf::String(_("How to play"), fontTitle, 48);
    strExitMessage = sf::String(_("Press escape to come back"), fontTitle, 23);
}

void StateHowToPlay::event(sf::Event theEvent){
    if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Escape){
        pManager -> popState();
    }
}

void StateHowToPlay::update(bool isCovered){

}

void StateHowToPlay::draw(bool isCovered, DrawingQueue& queue){
    queue.Draw(0, spBackground);
}
