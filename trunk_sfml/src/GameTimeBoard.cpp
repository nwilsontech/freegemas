#include "GameTimeBoard.h"
#include "ResourceManager.h"

#include "i18n.h"
#include "log.h"

#include <cmath>

void GameTimeBoard::loadResources (){

    // Load the font for the timeboard
    ftTime = ResMgr -> getFont("media/fuentelcd.ttf", 61);

    // Load the background image for the timeboard
    spBackground.SetImage(ResMgr -> getImage("media/timeBackground.png"));
    spBackground.SetPosition (17, 230);

    // Create the header of the time board
    stHeader = sf::String (_("time left"),
                                 ResMgr -> getFont("media/fNormal.ttf", 33),
                                 33);
    stHeader.SetPosition (113 - floor(stHeader.GetRect().GetWidth() / 2), 186);

    // Redraw the text with the time
    redraw ("00:11");
};

void GameTimeBoard::redraw (std::string time){
    stTime = sf::String(time, ftTime, 60);
    stTime.SetPosition(190 - stTime.GetRect().GetWidth(), 226);
}

void GameTimeBoard::draw (DrawingQueue& queue){
    queue.Draw (1, stHeader);
    queue.Draw (1, spBackground);
    queue.Draw (2, stTime);
}
