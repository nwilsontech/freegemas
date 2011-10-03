/**
 * @file State2.h
 * 
 * @author José Tomás Tocino García
 * @date 2011
 *
 * Copyright (C) 2011 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _STATE2_H_
#define _STATE2_H_

#include "log.h"
#include "State.h"
#include <SFML/Graphics.hpp>


class State2 : public State{
    sf::String texto;

    void loadResources(){
        texto = sf::String("Pulsa espacio para que yo me pire");        
        texto.SetPosition(0, 200);
    }

    void event(sf::Event theEvent){
        if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Space){
            pManager -> popState();
        }//
    }

    void draw(bool isCovered, DrawingQueue& queue){
        queue.Draw(0, texto);
    }
};

#endif /* _STATE2_H_ */
