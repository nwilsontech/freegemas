#include "StateHowToPlay.h"
#include "i18n.h"
#include "ResourceManager.h"
#include "Util.h"

#include <cmath>

StateHowToPlay::StateHowToPlay(){
    lDEBUG << Log::CON("StateHowToPlay");
}

StateHowToPlay::~StateHowToPlay(){
    lDEBUG << Log::DES("StateHowToPlay");
}

void StateHowToPlay::loadResources(){

    // Main text
    bodyText = L"";
    bodyText += _("The objective of the game is to swap one gem with an adjacent gem to form a horizontal or vertical chain of three or more gems.");
    bodyText += L" \n \n ";
    bodyText += _("Click the first gem and then click the gem you want to swap it with. If the movement is correct, they will swap and the chained gems will disappear.");
    bodyText += L" \n \n ";
    bodyText += _("Bonus points are given when more than three identical gems are formed. Sometimes chain reactions, called cascades, are triggered, where chains are formed by the falling gems. Cascades are awarded with bonus points.");

    // Set the sprite for the background
    spBackground.SetImage(ResMgr -> getImage("media/howtoScreen.png"));

    // Main title
    strTitle = sf::String(_("How to play"), 
                          ResMgr -> getFont("media/fuenteMenu.ttf", 48), 48);
    strTitle.SetX(300 + 470 / 2 - strTitle.GetRect().GetWidth() / 2);
    strTitle.SetY(20);

    // Main title's shadow
    strTitleShadow = strTitle;
    strTitleShadow.SetColor (sf::Color(0,0,0,125));
    strTitleShadow.Move(0, 2);

    // Exit message
    strExitMessage = sf::String(_("Press escape to come back"), 
                                ResMgr -> getFont("media/fuenteMenu.ttf", 23), 23);
    strExitMessage.SetPosition(40, 550);

    // Exit message's shadow
    strExitMessageShadow = strExitMessage;
    strExitMessageShadow.SetColor (sf::Color(0,0,0,125));
    strExitMessageShadow.Move(0, 2);

    // Format text to fit 450px of width
    strBodyLines = formatText(bodyText, ResMgr -> getFont("media/23medium.ttf", 23), 450);
    
    // Initial vertical position
    int acumHeight = 90;

    // Position every line of text, centered
    for (size_t i = 0; i < strBodyLines.size(); i++){
        strBodyLines[i].SetPosition(535 - std::floor(strBodyLines[i].GetRect().GetWidth() / 2), 
                                    acumHeight);

        // Increment vertical acumulator
        acumHeight += strBodyLines[i].GetSize() + 7;
    }
}

void StateHowToPlay::event(sf::Event theEvent){
    if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Escape){
        pManager -> popState();
    }
}

void StateHowToPlay::update(bool isCovered){

}

void StateHowToPlay::draw(bool isCovered, DrawingQueue& queue){

    // Draw every line of text
    for (size_t i = 0; i < strBodyLines.size(); i++){
        queue.Draw(2, strBodyLines[i]);
    }

    queue.Draw(0, spBackground);

    queue.Draw(1, strTitle);
    queue.Draw(1, strExitMessage);

    queue.Draw(0.9, strTitleShadow);
    queue.Draw(0.9, strExitMessageShadow);
}
