/**
 * @file juego.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Fichero con la clase para la ventana principal
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
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


#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <Gosu/Gosu.hpp>

#include <tr1/memory>
#include <string>
using namespace std;

#include "log.h"
#include "tablero.h"

/**
 * @class Juego
 *
 * @brief Clase principal del juego.
 *
 * Hemos intentando mantener este ejemplo con el menor tamaño posible
 * para que sea más fácil de entender. Esta clase llevará a cabo toda
 * la ejecución del juego, pero en el caso de que quisiéramos añadir
 * menús, pantallas de crédito y demás, tendríamos que utilizar
 * diferentes clases para cada uno de los estados, que es lo que se ha
 * llevado a cabo en la rama principal del proyecto.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Juego : public Gosu::Window{
public:
    /// Inicializa las variables y carga las imágenes
    Juego ();
    
    /// Realiza las operaciones lógicas
    void update();

    /// Dibuja las imágenes en pantalla
    void draw();

    /// Responde a la entrada del usuario
    void buttonDown(Gosu::Button boton);

    ~Juego();

private:
    /// Imagen para el puntero del ratón
    tr1::shared_ptr<Gosu::Image> puntero;

    /** Función para el cálculo de animaciones.

	@param t Tiempo transcurrido
	@param b Valor inicial (beginning)
	@param c Diferencia entre inicial y final (change)
	@param d Duración
    */
    static float eqMov(float t, float b, float c, float d);

    /// Lleva el control de la aparición de la pista. Inicialmente
    /// vale -1, y al pulsar el botón H valdrá totalAnimPista, e irá
    /// disminuyendo según pasa los frames hasta que la pista
    /// desaparezca.
    int mostrandoPista;

    /// Duración de la pista en pantalla.
    int totalAnimPista;

    /// Coordenadas de la casilla que sirve como pista.
    coord coordPista;

    /// Carga las imágenes de las gemas
    void cargarGemas();

    /// Indica si está sobre una gema
    bool sobreGema(int mX, int mY);

    /// Devuelve las coordenadas de casilla correspondientes a las coordenadas de ratón mX,mY.
    coord dameGema(int mX, int mY);

    /// Regenera la imagen del marcador de puntos
    void repintarPuntos();

    /// Tablero de casillas
    Tablero tablero;

    /// Estados para el autómata
    enum tEstado{
	eInicialGemas,
	eEspera,
	eGemaMarcada,
	eGemasCambiando,
	eGemasDesapareciendo,
	eGemasNuevasCayendo,
	eDesapareceTablero
    };

    /// Estado actual de la clase
    tEstado estado;

    /// Coordenadas de la primera casilla marcada
    int casillaMarcadaX, casillaMarcadaY;

    /// Coordenadas de la segunda casilla marcada
    int casillaMarcada2X, casillaMarcada2Y;

    /// Paso actual en la animación
    int pasoAnim;

    /// Total de pasos en las animaciones
    int totalAnim;

    /// Total de pasos en la animación inicial
    int totalAnimInit;

    /// Contenedor temporal de las casillas a borrar
    vector<coord> casillasGanadoras;

    /// Imagen para el tablero
    tr1::shared_ptr<Gosu::Image> imgTablero;

    /// Imágenes de las gemas
    tr1::shared_ptr<Gosu::Image> imgBlanca;
    tr1::shared_ptr<Gosu::Image> imgRoja;
    tr1::shared_ptr<Gosu::Image> imgLila;
    tr1::shared_ptr<Gosu::Image> imgNaranja;
    tr1::shared_ptr<Gosu::Image> imgVerde;
    tr1::shared_ptr<Gosu::Image> imgAmarilla;
    tr1::shared_ptr<Gosu::Image> imgAzul;

    /// Imagen del cuadrado de selección de casilla
    tr1::shared_ptr<Gosu::Image> imgSelector;

    /// Imagen para el marcador de puntos
    tr1::shared_ptr<Gosu::Image> txtPuntos;

    /// Número de puntos del usuario
    int puntos;

};

#endif /* _JUEGO_H_ */
