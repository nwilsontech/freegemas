/**
 * @file juego.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2010
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


#include "juego.h"

#include <cmath>
#include <algorithm>

Juego::Juego () : Gosu::Window(800, 600, false) {
    // Cambiamos el título de la ventana.
    setCaption(L"FreeGemas v0.1");

    // Cargamos la imagen para el puntero del ratón
    puntero.reset(new Gosu::Image(graphics(), 
				  L"media/handCursor.png"));

    // Cargamos la imagen del tablero
    imgTablero.reset(new Gosu::Image( graphics(),
				     L"media/tablero.png"));

    // Cargamos la imagen del selector de casilla
    imgSelector.reset(new Gosu::Image( graphics(), 
				      L"media/selector.png"));    

    // Inicializamos al estado inicial
    estado = eInicialGemas;

    // Al no haber ninguna casilla marcada, ponemos las coordenadas a -1
    casillaMarcadaX = -1;
    casillaMarcadaY = -1;

    // Cargamos las imágenes de las gemas
    cargarGemas();

    // Variables que controlan las animaciones
    pasoAnim = 0;
    totalAnim = 17;
    totalAnimInit = 50;

}

void Juego::update(){
    // Estado: Están apareciendo todas las gemas del tablero
    if(estado == eInicialGemas){
      	// Si se ha llegado al final de la animación

	if(++pasoAnim == totalAnimInit){
	    // Pasamos al estado de espera (juego normal)
	    estado = eEspera;

	    // Restablecemos las variables de animación de las casillas
	    tablero.cancelarAnimaciones();

	    // Ponemos a 0 el contador de las animaciones
	    pasoAnim = 0;
	}
    }

    // Estado: Las dos gemas seleccionadas haciendo click están intercambiándose
    else if(estado == eGemasCambiando){	

	// ¿Fin de animación?
	if(++pasoAnim == totalAnim){

	    // Hacemos desaparecer las casillas que forman filas y columnas
	    estado = eGemasDesapareciendo;

	    // Intercambiamos en el objeto las dos casillas clickeadas
	    tablero.swap(casillaMarcadaX, casillaMarcadaY,
			 casillaMarcada2X, casillaMarcada2Y);

	    // Ponemos el contador de animaciones a cero
	    pasoAnim = 0;
	}
    }

    // Estado: Las gemas que forman filas y columnas desaparecen
    else if(estado == eGemasDesapareciendo){

	// ¿Fin de animación?
	if(pasoAnim++ == totalAnim){

	    // Hacemos que los espacios del tablero se rellen con nuevas fichas
	    estado = eGemasNuevasCayendo;
	    
	    // Borramos del tablero las casillas que forman filas y columnas
	    for(size_t i = 0; i < casillasGanadoras.size(); ++i){
		tablero.del(casillasGanadoras[i].x,
			    casillasGanadoras[i].y);
	    }

	    /*
	      Al borrar las gemas forman filas y columnas, aquellas
	      gemas que estuvieran por encima tienen ahora que bajar y
	      ocupar las posiciones vacías.

	      Con esta primera función calculamos las posiciones
	      finales de las gemas.
	     */
	    tablero.calcularMovimientosCaida();

	    // Luego, aplicamos las posiciones calculadas a las fichas
	    tablero.aplicarCaida();

	    // Finalmente, rellenamos los espacios que quedan arriba con nuevas gemas.
	    tablero.rellenarEspacios();

	    pasoAnim = 0;
	}
    }

    // Estado: Las gemas nuevas están cayendo
    else if(estado == eGemasNuevasCayendo){

	// ¿Fin de la animación?
	if(pasoAnim++ == totalAnim){
	    
	    // Reiniciamos el contador de animaciones
	    pasoAnim = 0;

	    // Reiniciamos las variables que controlan la animación de
	    // cada gema a su estado inicial
	    for(int x = 0; x < 8; ++x){
		for(int y = 0; y < 8; ++y){
		    tablero.casillas[x][y].origY = y;
		    tablero.casillas[x][y].destY = 0;
		    tablero.casillas[x][y].debeCaer = false;
		}
	    }

	    /*
	      Tras caer las nuevas fichas, puede que accidentalmente
	      se hayan hecho nuevos grupos. Por ello, comprobamos si
	      hay nuevas casillas ganadoras.
	     */
	    casillasGanadoras = tablero.comprobar();

	    // Si existe alguna fila o columna ganadora
	    if(! casillasGanadoras.empty()){
	
		// Volvemos al estado en el que desaparecen las filas
		// y columnas ganadoras
		estado = eGemasDesapareciendo;
	    }
	    
	    /*
	      Parece que no hay ninguna fila o columna ganadora. Ahora
	      comprobamos si desde este tablero, es posible hacer
	      alguna combinación; es decir, que no se trata de un
	      tablero sin salida.

	     */
	    else if(tablero.existeSolucion().empty()){
		// No existen más movimientos
		
		// Hacemos desaparecer el tablero actual
		estado = eDesapareceTablero;

		// Damos valores a las variables de animación de todas
		// las gemas para hacer desaparecer el tablero actual.
		for(int x = 0; x < 8; ++x){
		    for(int y = 0; y < 8; ++y){
			tablero.casillas[x][y].debeCaer = true;
			tablero.casillas[x][y].origY = y;
			tablero.casillas[x][y].destY = 7 + Gosu::random(1,7);
		    }
		}
	    }
	    
	    /*
	      Si no ocurre nada de lo contrario (no hay casillas
	      ganadoras y sí existen posibles soluciones a partir del
	      tablero), volvemos al estado de espera (juego normal).
	     */
	    else{
		// Ahora que las nuevas gemas están
		estado = eEspera;
	    }
	}
    }

    // Estado: Las gemas están desapareciendo porque el tablero anterior ya no tenía más soluciones
    else if(estado == eDesapareceTablero){

	// ¿Fin de la animación?
	if(++pasoAnim == totalAnimInit){

	    // Volvemos al estado inicial
	    estado = eInicialGemas;

	    // Generamos un tablero nuevo
	    tablero.generar();

	    // Reiniciamos el contador de animaciones
	    pasoAnim = 0;
	}
    }

}

/*
  tiempo pasado, beginning, change, duration
 */
float Juego::eqMov(float t, float b, float c, float d) {
    t/=d;
    return -c *(t)*(t-2) + b;
};



void Juego::draw(){
    // Dibujamos el tablero
    imgTablero -> draw(0,0,0);

    // Obtenemos las coordenadas del ratón
    int mX =  input().mouseX();
    int mY =  input().mouseY();

    // Dibujamos el puntero del ratón por encima de todo (Z=90)
    puntero -> draw(mX, mY, 90);

    // Posición de la primera casilla
    int origenX = 241, 
	origenY = 41;

    // Si se encuentra sobre una casilla, dibujamos el selector de
    // casilla (amarillo) sobre ella

    if(sobreGema(mX, mY) ){
	imgSelector -> draw( origenX + dameGema(mX, mY).x * 65,
			     origenY + dameGema(mX, mY).y * 65,
			     4);
    }

    // Si hay alguna gema marcada, pintamos el selector de casilla
    // marcada (rojo) sobre aquella

    if(estado == eGemaMarcada){
	imgSelector -> draw(origenX + casillaMarcadaX * 65,
			    origenY + casillaMarcadaY * 65,
			    4, 1, 1,
			    Gosu::Color(0xffff0000));
    }


    // Utilizaremos un puntero para pintar cada casilla.
    boost::shared_ptr<Gosu::Image> img;

    // Recorremos todas las casillas
    for(int i = 0; i < 8; ++i){
	for(int j = 0; j < 8; ++j){

	    // Miramos el tipo de cada casilla
	    switch(tablero.casillas[i][j]){

	    case casBlanca:
		img = imgBlanca;
		break;

	    case casRoja:
		img = imgRoja;
		break;

	    case casLila:
		img = imgLila;
		break;

	    case casNaranja:
		img = imgNaranja;
		break;

	    case casVerde:
		img = imgVerde;
		break;

	    case casAmarilla:
		img = imgAmarilla;
		break;

	    case casAzul:
		img = imgAzul;
		break;

	    case casVacia:
		img.reset();
		break;
	    } // fin switch

	    // Si el puntero no es nulo (es decir, no es una casilla vacía)
	    if(img != NULL){

		// Estado: TODAS las casillas están animándose
		if(estado == eInicialGemas || 
		   estado == eDesapareceTablero){

		    img -> draw(origenX + i * 65,
				eqMov(pasoAnim,
				      origenY + tablero.casillas[i][j].origY * 65,
				      tablero.casillas[i][j].destY * 65,
				      totalAnimInit),
				3);

		}

		// Estado: Sólo las casillas marcadas (debeCaer = true) están animándose
		else if(estado == eEspera || 
			estado == eGemaMarcada || 
			estado == eGemasNuevasCayendo){

		    // Si debe animarse
		    if(tablero.casillas[i][j].debeCaer){
			img -> draw(origenX + i * 65,
				    eqMov(pasoAnim,
					  origenY + tablero.casillas[i][j].origY * 65,
					  tablero.casillas[i][j].destY * 65,
					  totalAnim),
				    3);
		    }

		    // Si no, pintamos la casilla tal cual
		    else{
			img -> draw(origenX + i * 65,
				    origenY + j * 65,
				    3);
		    }
		}
	    
		// El par de casillas clickeadas se intercambian
		else if(estado == eGemasCambiando){

		    // Si la casilla actual es la primera casilla marcada
		    if(i == casillaMarcadaX && 
		       j == casillaMarcadaY){

			img -> draw(eqMov(pasoAnim,
					  origenX + i * 65,
					  (casillaMarcada2X - casillaMarcadaX) * 65,
					  totalAnim),

				    eqMov(pasoAnim,
					  origenY + j * 65,
					  (casillaMarcada2Y - casillaMarcadaY) * 65,
					  totalAnim),

				    3);

		    }
		
		    // Si la casilla actual es la segunda casilla marcada
		    else if(i == casillaMarcada2X && 
			    j == casillaMarcada2Y){
		
			img -> draw(eqMov(pasoAnim,
					  origenX + i * 65,
					  (casillaMarcadaX - casillaMarcada2X) * 65,
					  totalAnim),

				    eqMov(pasoAnim,
					  origenY + j * 65,
					  (casillaMarcadaY - casillaMarcada2Y) * 65,
					  totalAnim),

				    3);

		    }

		    // Para el resto de casillas
		    else{
			img -> draw(origenX + i * 65,
				    origenY + j * 65,
				    3);
		    }
		
		}

		// Estado: Desaparición de las gemas ganadoras
		else if(estado == eGemasDesapareciendo){
		    
		    // Si la casilla actual es una de las casillas ganadoras
		    if(find(casillasGanadoras.begin(), 
			    casillasGanadoras.end(), 
			    coord(i, j)) != casillasGanadoras.end() ){
			
			// La pintamos haciendo que se desvanezca
			img -> draw(origenX + i * 65,
				    origenY + j * 65,
				    3, 1, 1,
				    Gosu::Color(255 * (1 -(float)pasoAnim/totalAnim), 255, 255, 255));
		    }

		    // Para el resto de casillas
		    else{
			img -> draw(origenX + i * 65,
				    origenY + j * 65,
				    3);
		    }
		    

		}
	    } // Fin if (img != NULL)

	    // Reiniciamos el puntero a la imagen
	    img.reset();
	}
    }

}

bool Juego::sobreGema(int mX, int mY){
    /*
      La matriz es de 8x8, cada casilla es cuadradada y mide 65
      píxeles de lado, y la primera casilla está en 241,41
     */

    return (mX > 241 && mX < 241 + 65 * 8 &&
	    mY > 41 && mY < 41 + 65 * 8);
}

coord Juego::dameGema(int mX, int mY){
    return coord((mX - 241) / 65 , 
		 (mY - 41) / 65 );
}

void Juego::buttonDown (Gosu::Button B){
    // Si se pulsa escape, salimos
    if(B == Gosu::kbEscape){
	 close();
    }

    // Si hacemos click con el ratón
    else if(B == Gosu::msLeft){ 

	int mX =  input().mouseX();
	int mY =  input().mouseY();

	// Si se pulsó sobre una gema
	if(sobreGema(mX, mY)){ 
	
	    // Si no hay ninguna gema marcada
	    if(estado == eEspera){ 
		
		// Pasamos al estado de gema marcada
		estado = eGemaMarcada;

		// Guardamos las coordenadas de la priemra gema marcada
		casillaMarcadaX = dameGema(mX, mY).x;
		casillaMarcadaY = dameGema(mX, mY).y;
	    }
	    
	    // Si ya había una gema marcada
	    else if(estado == eGemaMarcada){ 
		coord res = dameGema(mX, mY);

		casillaMarcada2X = res.x;
		casillaMarcada2Y = res.y;

		// Si es una gema CONTIGUA
		if(abs(casillaMarcadaX - casillaMarcada2X) 
		   + abs(casillaMarcadaY - casillaMarcada2Y) == 1){ 

		    Tablero temporal = tablero;
		    temporal.swap(casillaMarcadaX, casillaMarcadaY,
				  casillaMarcada2X, casillaMarcada2Y);

		    casillasGanadoras = temporal.comprobar();
		    
		    // SI ES UN MOVIMIENTO GANADOR
		    if(! casillasGanadoras.empty()){
			estado = eGemasCambiando;
		    }
		    
		    // SI ES CONTIGUA pero no es un movimiento ganador
		    else{
			casillaMarcadaX = -1;
			casillaMarcadaY = -1;
			estado = eEspera;		    
		    }
		}
		
		// Si NO ES contigua
		else{
		    casillaMarcadaX = -1;
		    casillaMarcadaY = -1;
		    estado = eEspera;		    
		}
	    }
	}

    }
}

Juego::~Juego(){
    
}

void Juego::cargarGemas(){
    Gosu::Graphics & g = graphics();

    imgBlanca.reset(new Gosu::Image(g, L"media/gemBlanca.png"));
    imgRoja.reset(new Gosu::Image(g, L"media/gemRoja.png"));
    imgLila.reset(new Gosu::Image(g, L"media/gemLila.png"));
    imgNaranja.reset(new Gosu::Image(g, L"media/gemNaranja.png"));
    imgVerde.reset(new Gosu::Image(g, L"media/gemVerde.png"));
    imgAmarilla.reset(new Gosu::Image(g, L"media/gemAmarilla.png"));
    imgAzul.reset(new Gosu::Image(g, L"media/gemAzul.png"));

}

