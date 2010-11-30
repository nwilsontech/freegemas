#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <Gosu/Gosu.hpp>

class Juego : public Gosu::Window{
	Gosu::Image * imagen, * fondo;
public:

	Juego() : Gosu::Window(800, 600, false){
		imagen = new Gosu::Image(graphics(), L"imagen.png");
		fondo = new Gosu::Image(graphics(), L"background.png");
		
	}

	void update() { 
		// aquí iría la lógica del juego
	}

	void draw() { 
		imagen -> draw(175, 212, 1);
		fondo -> draw(0,0,0);
	}  

	void buttonDown(Gosu::Button B) { 
		close(); 
	}

	~Juego(){
		delete imagen;
		delete fondo;
	}

};

#endif /* _JUEGO_H_ */
