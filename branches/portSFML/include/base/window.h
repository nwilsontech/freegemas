#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>

using namespace std;

class DrawingManager{
    multimap<float, sf::Drawable*> elementsToDraw;
    multimap<float, sf::Drawable*>::iterator it1, it2;

public:
    DrawingManager();
    void assignTarget(sf::RenderWindow * targetWindow_);
    void Draw(sf::Drawable * obj, float z);
    void commit();
    void clear();

private:
    sf::RenderWindow * targetWindow;
};


class BaseWindow{
public:
    BaseWindow(int w, int h, string c, float f = 60);

    virtual void update() = 0;
    virtual void draw(DrawingManager & dMngr) = 0;
    virtual void buttonDown(sf::Key::Code button) { }
    virtual void buttonUp(sf::Key::Code button) { }

    int mouseX() const;
    int mouseY() const;

    void show();
    void close();    

    DrawingManager drawingManager;
private:
    int width, height;
    string caption;
    float fps;

    sf::RenderWindow targetWindow;

};


#endif /* _WINDOW_H_ */

