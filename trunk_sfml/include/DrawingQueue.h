// Copyright (C) 2012 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

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
