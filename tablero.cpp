/**
 * @file tablero.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Fichero fuente de la clase tablero
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

#include "tablero.h"

#include <ctime>
#include <iostream>

Tablero::Tablero(){
    generar();
}

void Tablero::generar(){
    // Inicializamos la semilla aleatoria
    std::srand(time(0));

    // Generación de las casillas aleatorias
    do{
	for (int i = 0; i < 8; ++i)
	{
	    for (int j = 0; j < 8; ++j)
	    {
		// Tipo de gema
		casillas[i][j] = static_cast<tCasilla>((int)Gosu::random(1,8));

		// Animación inicial activa
		casillas[i][j].debeCaer = true;

		// Posición inicial de la animación por encima del
		// tablero (para que haga el efecto de caer).
		casillas[i][j].origY = Gosu::random(-7, -1);

		// Posición final de la casilla
		casillas[i][j].destY = j - casillas[i][j].origY;


	    }
	}
	
	// Regenera si hay alguna solución directa o si es imposible de resolver
    }while(!comprobar().empty() || existeSolucion().empty()); 

}

void Tablero::swap(int x1, int y1, int x2, int y2){

    // Intercambio básico de dos casillas
    tCasilla temp = casillas[x1][y1];

    casillas[x1][y1] = casillas[x2][y2];
    casillas[x2][y2] = temp;
}

void Tablero::del(int x, int y){
    casillas[x][y] = casVacia;
}

vector<coord> Tablero::existeSolucion(){
    vector<coord> resultados;

    // Si hay alguna solución directa, obviamente hay solución
    if(!comprobar().empty()){
	resultados.push_back(coord(-1,-1));
	return resultados;
    }


    // Hacemos una copia del tablero para hacer las comprobaciones
    Tablero temp = *this;

    for(int x = 0; x < 8; ++x){
	for(int y = 0; y < 8; ++y){
	    
	    // Cambiar con superior y comprobar
	    if(y > 0){
		temp.swap(x,y, x,y-1);
		if(!temp.comprobar().empty()){
		    resultados.push_back(coord(x,y));
		}
		temp.swap(x,y, x,y-1);
	    }

	    // Cambiar con inferior y comprobar
	    if(y < 7){
		temp.swap(x, y, x, y+1);
		if(!temp.comprobar().empty()){
		    resultados.push_back(coord(x,y));
		}
		temp.swap(x, y, x, y+1);
	    }

	    // Cambiar con celda izquierda y comprobar
	    if(x > 0){
		temp.swap(x, y, x - 1, y);
		if(!temp.comprobar().empty()){
		    resultados.push_back(coord(x,y));
		}
		temp.swap(x, y, x - 1, y);
	    }

	    // Cambiar con celda derecha y comprobar
	    if(x < 7){
		temp.swap(x, y, x + 1, y);
		if(!temp.comprobar().empty()){
		    resultados.push_back(coord(x,y));
		}
		temp.swap(x, y, x + 1, y);
	    }

	    
	}
    }
    
    return resultados;
}

vector<coord> Tablero::comprobar(){
    // Recorremos filas
    boost::array<boost::array<int, 8>, 8> comprobHor;
    boost::array<boost::array<int, 8>, 8> comprobVer;

    // Ponemos matrices de comprobación a cero
    for(int y = 0; y < 8; ++y){
	for(int x = 0; x < 8; ++x){
	    comprobHor[x][y] = comprobVer[x][y] = 0;
	}
    }

    // Rellenamos la matriz de comprobaciones por FILAS
    for(int y = 0; y < 8; ++y){ 
	for(int x = 0; x < 8; ++x){ 

	    /* Recorremos de x - 1 hasta el inicio */
	    for(int k = x - 1; k >= 0; --k){ 
		if(casillas[x][y] == casillas[k][y] && casillas[x][y] != casVacia){
		    comprobHor[x][y] = comprobHor[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }

	    /* Recorremos de x + 1 hasta el final */
	    for(int k = x + 1; k < 8; ++k){
		if(casillas[x][y] == casillas[k][y] && casillas[x][y] != casVacia){
		    comprobHor[x][y] = comprobHor[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }
	}
    }


    // Rellenamos la matriz de comprobaciones por COLUMNAS
    for(int x = 0; x < 8; ++x){ 
	for(int y = 0; y < 8; ++y){ 

	    /* Recorremos de y - 1 hasta el inicio */
	    for(int k = y - 1; k >= 0; --k){ 
		if(casillas[x][y] == casillas[x][k] && casillas[x][y] != casVacia){
		    comprobVer[x][y] = comprobVer[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }

	    /* Recorremos de y + 1 hasta el final */
	    for(int k = y + 1; k < 8; ++k){
		if(casillas[x][y] == casillas[x][k] && casillas[x][y] != casVacia){
		    comprobVer[x][y] = comprobVer[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }
	}
    }


    vector<coord> coordenadas;

    // Incluimos en el vector de coordenadas las celdas que forman parte de filas o columnas
    for(int y = 0; y < 8; ++y){ 
	for(int x = 0; x < 8; ++x){ 
	    if(comprobHor[x][y] > 1 || comprobVer[x][y] > 1){
		coordenadas.push_back(coord(x,y));
	    }
	}
    }

    return coordenadas;
}


void Tablero::calcularMovimientosCaida(){
    // Por cada columna x
    for(int x = 0; x < 8; ++x){

	/*
	  Vamos de abajo a arriba. Por cada celda vacía, recorremos
	  todas las gemas que están por encima, actualizando su
	  posición final tras la animación de caer.
	 */

	for(int y = 7; y >= 0; --y){

	    // Guardamos la posición vertical original para saber desde dónde hacer la animación de caída
	    casillas[x][y].origY = y;
	    
	    // Si la casilla es vacía, bajamos todas las casillas por encima
	    if(casillas[x][y] == casVacia){
		
		for(int k = y-1; k >= 0; --k){		    

		    // Ponemos la flag de caída 
		    casillas[x][k].debeCaer = true;

		    // Aumentamos en uno la cantida de desplazamientos
		    // verticales (celdas vacías) que debe caer.
		    casillas[x][k].destY ++;
		}
	    }
	}
    }
}

void Tablero::aplicarCaida(){
    for(int x = 0; x < 8; ++x){
	// Desde abajo a arriba para no sobreescribir casillas

	for(int y = 7; y >= 0; --y){
	    if(casillas[x][y].debeCaer && casillas[x][y] != casVacia){
		int y0 = casillas[x][y].destY;
		
		casillas[x][y + y0] = casillas[x][y];
		casillas[x][y] = casVacia;
	    }
	}
   }
}

void Tablero::rellenarEspacios(){

    // Recorremos cada columna x
    for(int x = 0; x < 8; ++x){

	int saltos = 0;

	// Contamos el número de casillas vacías que hay en la parte
	// superior de la columna, guardando el resultado en la
	// variable saltos
	for(int y = 0; y < 8; ++y){
	    if(casillas[x][y] != casVacia) break;
	    saltos ++;
	}
	
	// Por cada casilla libre en cada columna
	for(int y = 0; y < 8; ++y){

	    if(casillas[x][y] == casVacia) {
		
		// Generamos un tipo aleatorio de casilla
		casillas[x][y] = static_cast<tCasilla> ( (int)Gosu::random(1,8) );
		
		// La nueva casilla debe aparecer desde arriba
		casillas[x][y].debeCaer = true;  

		// La posición inicial estará por encima del tablero
		// tantas casillas como sitios libres
		casillas[x][y].origY = y - saltos;
		
		// Por tanto, se moverá ese número de posiciones verticalmente
		casillas[x][y].destY = saltos;
	    }		
	}
    }	
}

void Tablero::cancelarAnimaciones(){
    for(int x = 0; x < 8; ++x){
	for(int y = 0; y < 8; ++y){
	    casillas[x][y].debeCaer = false;
	    casillas[x][y].origY = y;
	    casillas[x][y].destY = 0;
	}
    }
}


