#ifndef _GAMESCOREBOARD_H_
#define _GAMESCOREBOARD_H_

#include <SFML/Graphics.hpp>
#include "DrawingQueue.h"

class GameScoreBoard {    
public:
    void loadResources();

    void redraw(int score);

    void draw (DrawingQueue& queue);
private:

    /// Background image
    sf::Sprite spBackground;

    /// String for the header
    sf::String stHeader;

    /// Font for the score 
    sf::Font ftScore;

    /// String for the score
    sf::String stScore;
};

#endif /* _GAMESCOREBOARD_H_ */
