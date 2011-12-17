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

    /// Font for the current-score text
    sf::Font ftScore;

    /// Background for the current-score board
    sf::Sprite spScoreBackground;

    /// Image for the current-score header
    sf::String stScoreHeader;

    /// Image for the score text
    sf::Sprite spPuntos;
};

#endif /* _GAMESCOREBOARD_H_ */
