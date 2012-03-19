#include "BaseButton.h"
#include "ResourceManager.h"

void BaseButton::loadResources(std::string text, 
                               std::string imgIconPath, 
                               int lx, int ly, int lz){

    x = lx;
    y = ly;
    z = lz;

    sfBackground.SetImage(ResMgr -> getImage ("media/buttonBackground.png"));
    sfBackground.SetPosition (x, y);

    sfIcon.SetImage(ResMgr -> getImage (imgIconPath));
    sfIcon.SetPosition (x + 7, y);

    changeText (text);    
}

void BaseButton::changeText(std::string text){
    stLabel = sf::String(text, ResMgr -> getFont ("media/fNormal.ttf", 27));
    // int stLabelWidth = stLabel.GetRect().GetWidth();
    stLabel.SetPosition(x + 35, y + 5);
}

void BaseButton::draw(DrawingQueue& queue){
    queue.Draw (z, sfIcon);
    queue.Draw (z, stLabel);
    queue.Draw (z - 0.1, sfBackground);
}

bool BaseButton::clicked(unsigned int mX, unsigned int mY){
    return false;
}


