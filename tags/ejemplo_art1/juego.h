#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <Gosu/Gosu.hpp>

class Juego : public Gosu::Window{
	Gosu::Image img;
public:

	Juego() : 
		Gosu::Window(800, 600, false),
		img(graphics(), L"imagen.png")
		{  

		}

	void update() { 
		// aquí iría la lógica del juego
	}

	void draw() { 
		img.draw(175, 212, 1);
	}  

	void buttonDown(Gosu::Button B) { 
		close(); 
	}

};

#endif /* _JUEGO_H_ */
