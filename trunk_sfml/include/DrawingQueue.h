#ifndef _DRAWINGQUEUE_H_
#define _DRAWINGQUEUE_H_

#include <map>
#include <SFML/Graphics.hpp>

/**
 * Represents a drawing queue, where the Drawable objects will be drawn
 * depending on their depth (which is the key of the map).
 */

class DrawingQueue : private std::multimap<float, const sf::Drawable &>{
    
    // The StateManager should be able to review the base multimap
    friend class StateManager;

public:
    /// Adds a new drawable element to the drawing queue in the selected depth
    void Draw(float z, const sf::Drawable & object){
        insert(std::pair<float, const sf::Drawable &>(z, object));
    }
};

// Iterator for the DrawingQueue
typedef std::multimap<float, const sf::Drawable &>::const_iterator DrawingQueueIterator;


#endif /* _DRAWINGQUEUE_H_ */
