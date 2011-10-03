/**
 * @file State1.h
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


#ifndef _STATE1_H_
#define _STATE1_H_

#include "log.h"
#include "State.h"
#include "State2.h"

#include <SFML/Graphics.hpp>


class State1 : public State{
    sf::String texto;
    sf::Image img1, img2;
    sf::Sprite sp1, sp2;

    void loadResources(){
        texto = sf::String("Pulsa espacio para que aparezca otro estado encima");        

        img1.LoadFromFile("cat.jpg");
        sp1.SetImage(img1);

        img2.LoadFromFile("dog.jpg");
        sp2.SetImage(img2);
        sp2.SetPosition(300, 300);
    }

    void event(sf::Event theEvent){
        if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Space){
            pManager -> pushState(StatePointer(new State2()));
         }
    }

    void draw(bool isCovered, DrawingQueue& queue){
        queue.Draw(0, texto);
        queue.Draw(12, sp1);
        queue.Draw(2, sp2);
    }
};

#endif /* _STATE1_H_ */
