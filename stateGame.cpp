#include "stateGame.h"
#include "log.h"
#include "game.h"

#include <cmath>
#include <algorithm>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

using boost::format;

StateGame::StateGame(Game * p) : State(p){
    lDEBUG << Log::CON("StateGame");

    imgBoard.reset(new Gosu::Image(parent -> graphics(),
				     L"media/board.png"));

    imgSelector.reset(new Gosu::Image(parent -> graphics(), 
				      L"media/selector.png"));    

    state = eInicialGemas;

    casillaMarcadaX = -1;
    casillaMarcadaY = -1;


    loadGems();

    pasoAnim = 0;
    totalAnim = 17;
    totalAnimInit = 50;

    puntos = 0;

    redrawPoints();

    mostrandoPista = -1;
    totalAnimPista = 50;
}

void StateGame::redrawPoints(){
    Gosu::Bitmap temporal = Gosu::createText(boost::lexical_cast<wstring>(puntos),
					     L"media/fuentelcd.ttf", 33, 0, 190, Gosu::taRight);

    txtPuntos.reset(new Gosu::Image(parent -> graphics(),
				    temporal));
}

void StateGame::update(){
    if(state == eInicialGemas){
	if(++pasoAnim == totalAnimInit){
	    lDEBUG << "Fichas iniciales colocadas";

	    state = eEspera;
	    board.endAnimations();

	    pasoAnim = 0;
	}
    }

    else if(state == eGemasCambiando){	
	if(++pasoAnim == totalAnim){
	    lDEBUG << "Fin eGemasCambiando";

	    state = eGemasDesapareciendo;
	    board.swap(casillaMarcadaX, casillaMarcadaY,
			 casillaMarcada2X, casillaMarcada2Y);

	    pasoAnim = 0;
	}
    }

    else if(state == eGemasDesapareciendo){
	if(pasoAnim++ == totalAnim){
	    lDEBUG << "Fin eGemasDesapareciendo";

	    state = eGemasNuevasCayendo;
	    
	    puntos += 10 * groupedSquares.size();
	    redrawPoints();

	    for(size_t i = 0; i < groupedSquares.size(); ++i){
		board.del(groupedSquares[i].x,
			    groupedSquares[i].y);
	    }

	    // Calculando los movimientos de caída...

	    board.calcFallMovements();

	    //Aplicando las modificaciones según caídas a la matriz de squares...

	    board.applyFall();

	    // Rellenando los espacios que han quedado por arriba...

	    board.fillSpaces();

	    pasoAnim = 0;
	}
    }

    else if(state == eGemasNuevasCayendo){
	if(pasoAnim++ == totalAnim){
	    lDEBUG << "Fin eGemasNuevasCayendo";

	    state = eEspera;
	    pasoAnim = 0;

	    for(int x = 0; x < 8; ++x){
		for(int y = 0; y < 8; ++y){
		    board.squares[x][y].origY = y;
		    board.squares[x][y].destY = 0;
		    board.squares[x][y].mustFall = false;
		}
	    }

	    // Fin de turno, pero comprobamos posibles movimientos ganadores indirectos...

	    groupedSquares = board.check();

	    if(! groupedSquares.empty()){
		// Si encontramos más filas o columnas
		
		state = eGemasDesapareciendo;
	    }

	    else if(board.solutions().empty()){

		// Si el tablero no tiene más juegos posibles

		lDEBUG << Log::cRojo << "ZOMG NO EXISTEN MÁS MOVIMIENTOS";
		
		state = eDesapareceBoard;

		for(int x = 0; x < 8; ++x){
		    for(int y = 0; y < 8; ++y){
			board.squares[x][y].mustFall = true;
			board.squares[x][y].origY = y;
			board.squares[x][y].destY = 7 + Gosu::random(1,7);
		    }
		}
	    }
	}
    }

    else if(state == eDesapareceBoard){
	if(++pasoAnim == totalAnimInit){
	    lDEBUG << "Board desaparecido";

	    state = eInicialGemas;
	    board.generate();

	    pasoAnim = 0;
	}
    }

}

/*
  tiempo pasado, beginning, change, duration
 */
float StateGame::eqMov(float t, float b, float c, float d) {
    t/=d;
    return -c *(t)*(t-2) + b;
};


void StateGame::draw(){
    imgBoard -> draw(0,0,1);

    int posX = 241, 
	posY = 41;

    tr1::shared_ptr<Gosu::Image> img;

    for(int i = 0; i < 8; ++i){
	for(int j = 0; j < 8; ++j){
	    switch(board.squares[i][j]){
	    case sqWhite:
		img = imgWhite;
		break;

	    case sqRed:
		img = imgRed;
		break;

	    case sqPurple:
		img = imgPurple;
		break;

	    case sqOrange:
		img = imgOrange;
		break;

	    case sqGreen:
		img = imgGreen;
		break;

	    case sqYellow:
		img = imgYellow;
		break;

	    case sqBlue:
		img = imgBlue;
		break;

	    case sqEmpty:
		img.reset();
		break;
	    } // fin switch

	    if(img != NULL){
		if(state == eInicialGemas || state == eDesapareceBoard){
		    img -> draw(posX + i * 65,
				eqMov(pasoAnim,
				      posY + board.squares[i][j].origY * 65,
				      board.squares[i][j].destY * 65,
				      totalAnimInit),
				3);
		}
		else if(state == eEspera || state == eGemaMarcada || state == eGemasNuevasCayendo){

		    if(board.squares[i][j].mustFall){
			img -> draw(posX + i * 65,
				    eqMov(pasoAnim,
					  posY + board.squares[i][j].origY * 65,
					  board.squares[i][j].destY * 65,
					  totalAnim),
				    3);
		    }else{
			img -> draw(posX + i * 65,
				    posY + j * 65,
				    3);
		    }
		}
	    

		else if(state == eGemasCambiando){
		    if(i == casillaMarcadaX && 
		       j == casillaMarcadaY){

			img -> draw(eqMov(pasoAnim,
					  posX + i * 65,
					  (casillaMarcada2X - casillaMarcadaX) * 65,
					  totalAnim),

				    eqMov(pasoAnim,
					  posY + j * 65,
					  (casillaMarcada2Y - casillaMarcadaY) * 65,
					  totalAnim),

				    3);

		    }
		
		    else if(i == casillaMarcada2X && 
			    j == casillaMarcada2Y){
		
			img -> draw(eqMov(pasoAnim,
					  posX + i * 65,
					  (casillaMarcadaX - casillaMarcada2X) * 65,
					  totalAnim),

				    eqMov(pasoAnim,
					  posY + j * 65,
					  (casillaMarcadaY - casillaMarcada2Y) * 65,
					  totalAnim),

				    3);

		    }

		    else{
			img -> draw(posX + i * 65,
				    posY + j * 65,
				    3);
		    }
		
		}

		else if(state == eGemasDesapareciendo){
		    // Desaparición de las gemas ganadoras
		    
		    if(find(groupedSquares.begin(), 
			    groupedSquares.end(), 
			    coord(i, j)) != groupedSquares.end() ){
			
			img -> draw(posX + i * 65,
				    posY + j * 65,
				    3, 1, 1,
				    Gosu::Color(255 * (1 -(float)pasoAnim/totalAnim), 255, 255, 255));
		    }
		    else{
			img -> draw(posX + i * 65,
				    posY + j * 65,
				    3);
		    }
		    

		}
	    } // Fin if (img != NULL)

	    img.reset();
	}
    }

    int mX = parent -> input().mouseX();
    int mY = parent -> input().mouseY();

    if(overGem(mX, mY) ){
	imgSelector -> draw( 241 + getCoord(mX, mY).first * 65,
			     41 + getCoord(mX, mY).second * 65,
			     4);
    }

    if(state == eGemaMarcada){
	imgSelector -> draw(241 + casillaMarcadaX * 65,
			    41 + casillaMarcadaY * 65,
			    4, 1, 1,
			    Gosu::Color(0xffff0000));
    }

    if(mostrandoPista != -1){
	imgSelector -> draw(241 + coordPista.x * 65,
			    41 + coordPista.y * 65,
			    3, 1, 1,
			    Gosu::Color((float)mostrandoPista / totalAnimPista * 255, 0, 255, 0));
	mostrandoPista --;
    }

    txtPuntos -> draw(8, 127, 5, 1, 1, Gosu::Color(0xff4ec1be));
}

bool StateGame::overGem(int mX, int mY){
    return (mX > 241 && mX < 241 + 65 * 8 &&
	    mY > 41 && mY < 41 + 65 * 8);
}

pair<int,int> StateGame::getCoord(int mX, int mY){
    return make_pair((mX - 241) / 65 , 
		     (mY - 41) / 65 );
}

void StateGame::buttonDown (Gosu::Button B){
    if(B == Gosu::kbEscape){
	parent -> close();
    }

    else if(B == Gosu::msLeft){ // Se pulsó el ratón

	int mX = parent -> input().mouseX();
	int mY = parent -> input().mouseY();
	lDEBUG << "Click @ " << mX << "," << mY;

	if(overGem(mX, mY)){ // Si se pulsó sobre una gema
	
	    if(state == eEspera){ // Si no hay ninguna gema marcada
		state = eGemaMarcada;
		casillaMarcadaX = getCoord(mX, mY).first;
		casillaMarcadaY = getCoord(mX, mY).second;
	    }

	    else if(state == eGemaMarcada){ // Si ya había una gema marcada
		pair<int,int> res = getCoord(mX, mY);

		casillaMarcada2X = res.first;
		casillaMarcada2Y = res.second;

		// Si es una gema CONTIGUA
		if(abs(casillaMarcadaX - casillaMarcada2X) 
		   + abs(casillaMarcadaY - casillaMarcada2Y) == 1){ 

		    lDEBUG << "Casilla contigua";

		    Board temporal = board;
		    temporal.swap(casillaMarcadaX, casillaMarcadaY,
				  casillaMarcada2X, casillaMarcada2Y);

		    groupedSquares = temporal.check();
		    
		    // SI ES UN MOVIMIENTO GANADOR
		    if(! groupedSquares.empty()){
			lDEBUG << "Movimiento ganador!";

			state = eGemasCambiando;
		    }
		    
		    // SI ES CONTIGUA pero no es un movimiento ganador
		    else{
			casillaMarcadaX = -1;
			casillaMarcadaY = -1;
			state = eEspera;		    
		    }
		}
		
		// Si NO ES contigua
		else{
		    casillaMarcadaX = -1;
		    casillaMarcadaY = -1;
		    state = eEspera;		    
		}
	    }
	}

    }

    else if(B == Gosu::kbH){
	lDEBUG << "Hint...";
	vector<coord> posibilidades = board.solutions();
	if(posibilidades.empty()){

	}else{
	    coordPista = posibilidades[0];
	    mostrandoPista = totalAnimPista;
	}	
    }

    else if(B == Gosu::kbP){
	state = eDesapareceBoard;

	for(int x = 0; x < 8; ++x){
	    for(int y = 0; y < 8; ++y){
		board.squares[x][y].mustFall = true;
		board.squares[x][y].origY = y;
		board.squares[x][y].destY = 8 + Gosu::random(1,7);
	    }
	}
	
    }
}

StateGame::~StateGame(){
    lDEBUG << Log::DES("StateGame");
}

void StateGame::loadGems(){
    Gosu::Graphics & g = parent -> graphics();

    imgWhite.reset(new Gosu::Image(g, L"media/gemWhite.png"));
    imgRed.reset(new Gosu::Image(g, L"media/gemRed.png"));
    imgPurple.reset(new Gosu::Image(g, L"media/gemPurple.png"));
    imgOrange.reset(new Gosu::Image(g, L"media/gemOrange.png"));
    imgGreen.reset(new Gosu::Image(g, L"media/gemGreen.png"));
    imgYellow.reset(new Gosu::Image(g, L"media/gemYellow.png"));
    imgBlue.reset(new Gosu::Image(g, L"media/gemBlue.png"));

}