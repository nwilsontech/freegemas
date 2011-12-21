#include "GameScoreBoard.h"
#include "ResourceManager.h"

#include "i18n.h"

void GameScoreBoard::loadResources (){
    // Load the font for the scoreboard
    ftScore = ResMgr -> getFont("media/fuentelcd.ttf", 32);

    // Load the background image for the scoreboard
    spBackground.SetImage(ResMgr -> getImage("media/scoreBackground.png"));
    spBackground.SetPosition (17, 124);

    // Create the header of the scoreboard
    stHeader = sf::String (_("score"),
                                 ResMgr -> getFont("media/fNormal.ttf", 33),
                                 33);
    stHeader.SetPosition (113 - stHeader.GetRect().GetWidth() / 2, 80);

    // Redraw the text with the score
    redraw (0);
};

void GameScoreBoard::redraw (int score){
    stScore = sf::String("88", ftScore, 32);
    stScore.SetPosition(197 - stScore.GetRect().GetWidth(), 123);
}

void GameScoreBoard::draw (DrawingQueue& queue){
    queue.Draw (1, stHeader);
    queue.Draw (1, spBackground);
    queue.Draw (2, stScore);
}
