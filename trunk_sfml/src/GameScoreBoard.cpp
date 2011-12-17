#include "GameScoreBoard.h"
#include "ResourceManager.h"

#include "i18n.h"

void GameScoreBoard::loadResources (){
    // Load the font for the scoreboard
    ftScore = ResMgr -> getFont("media/fuentelcd.ttf", 33);

    // Load the background image for the scoreboard
    spScoreBackground.SetImage(ResMgr -> getImage("media/scoreBackground.png"));
    spScoreBackground.SetPosition (17, 124);

    // Create the header of the scoreboard
    stScoreHeader = sf::String (_("score"),
                                 ResMgr -> getFont("media/fNormal.ttf", 33),
                                 33);
    stScoreHeader.SetPosition (113 - stScoreHeader.GetRect().GetWidth() / 2, 80);

};

void GameScoreBoard::redraw (int score){

}

void GameScoreBoard::draw (DrawingQueue& queue){
    queue.Draw (1, stScoreHeader);
    queue.Draw (1, spScoreBackground);
}
