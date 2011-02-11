#include "base/window.h"

DrawingManager::DrawingManager() : targetWindow(NULL){ }

void DrawingManager::assignTarget(sf::RenderWindow * targetWindow_){
    targetWindow = targetWindow_;
}

void DrawingManager::Draw(sf::Drawable * obj, float z){
    elementsToDraw.insert(pair<float, sf::Drawable* >(z, obj));
}

void DrawingManager::commit(){
    if(targetWindow != NULL){
	it1 = elementsToDraw.begin();
	it2 = elementsToDraw.end();

	while(it1 != it2){
	    targetWindow -> Draw(*(it1 -> second));
	    ++it1;
	}
    }
    
    elementsToDraw.clear();
}


BaseWindow::BaseWindow(int w, int h, string c, float f) : width(w), height(h), caption(c), fps(f)
{
    targetWindow.Create(sf::VideoMode(width, height), c);
    targetWindow.SetFramerateLimit(fps);

    drawingManager.assignTarget(&targetWindow);
    targetWindow.ShowMouseCursor(false);

};

int BaseWindow::mouseX() const{ return targetWindow.GetInput().GetMouseX(); }
int BaseWindow::mouseY() const{ return targetWindow.GetInput().GetMouseY(); }

void BaseWindow::close(){
    targetWindow.Close();
}
    
void BaseWindow::show(){
    while(targetWindow.IsOpened()){
	
	sf::Event Event;
	while (targetWindow.GetEvent(Event))
	{
	    
	    // Close window : exit
	    if (Event.Type == sf::Event::Closed){
		targetWindow.Close();
	    }
	    else if(Event.Type == sf::Event::KeyPressed){
		buttonDown(Event.Key.Code);
	    }
	    else if(Event.Type == sf::Event::KeyReleased){
		buttonUp(Event.Key.Code);
	    }
	    
	    
	}
	update();
	targetWindow.Clear();
	draw(drawingManager);
	drawingManager.commit();
	targetWindow.Display();
    }
}
