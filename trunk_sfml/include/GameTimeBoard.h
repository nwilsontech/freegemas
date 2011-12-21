#ifndef _GAMETIMEBOARD_H_
#define _GAMETIMEBOARD_H_

#include <SFML/Graphics.hpp>
#include "DrawingQueue.h"

class GameTimeBoard {    
public:
    void loadResources();

    void redraw(std::string time);

    void draw (DrawingQueue& queue);
private:

    /// Background image
    sf::Sprite spBackground;

    /// String for the header
    sf::String stHeader;

    /// Font for the time
    sf::Font ftTime;

    /// String for the score
    sf::String stTime;
};


#endif /* _GAMETIMEBOARD_H_ */
