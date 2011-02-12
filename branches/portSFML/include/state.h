// state.h --- Clase base state

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

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

#ifndef _STATE_H_
#define _STATE_H_

#include <Gosu/Gosu.hpp>
#include <iostream>

#include "base/window.h"
#include "log.h"

using namespace std;

class Game;

/**
 * @class State
 * 
 * @brief Clase base para los diferentes states del juego.
 *
 * Esta clase abstracta tiene los métodos a los que llamará la clase de control (Game).
 * Cada state deberá implementar estos métodos con las acciones que crea conveniente.
 * No puede instanciarse por sí misma, debe crearse una clase heredada.
*/

class State{
protected:
    /**
     @brief Puntero al padre creador.

    **/
    Game * parent;
    bool drawingDeclared;
public:
    /**
       @brief Constructor - Crea un state.

       Recibe un puntero a Game, que será quien lleve el control de los states.

       @param p puntero a la clase Game que controla la aplicación
    **/
    State(Game * p);

    /*
    /// Si es necesario lanzar acciones independientes del constructor, irán aquí.
    virtual void lanzar(){
	lDEBUG << "lanzar";
    }
    */

    /// Virtual puro. Cada state implementa la lógica de control aquí.
    virtual void update() = 0;

    /// Virtual puro. Cada state implementa el redibujado aquí.
    virtual void draw(DrawingManager & dMngr) = 0;

    /// Opcionalmente los states pueden responder a la entrada redefiniendo este método.
    virtual void buttonDown(sf::Key::Code button){};

    virtual void buttonUp(sf::Key::Code button){};

    virtual ~State();
};

#endif /* _STATE_H_ */
