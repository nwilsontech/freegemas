#include "Animation.h"
#include "log.h"

Animation::Animation(int n, int d, tipoAnim anim, int e) :
    numAttr(n), duracion(d), esperaInicial(e), time(0){
    
    // Guardamos la memoria para los diferentes vectores
    inicial = new int[numAttr];
    final = new int[numAttr];
    change = new int[numAttr];
    actual = new float[numAttr];

    // Asigna valores perdeterminados a los vectores
    for (int i = 0; i < n; ++i)
    {
	inicial[i] = final[i] = change[i] = actual[i] = 0;
    }

    // Define el tipo de animación
    setTipoAnimation(anim);

    lDEBUG << Log::CON("Animación") << " . " << n << " parámetros.";
}


Animation::~Animation(){
    delete inicial;
    delete final;
    delete change;
    delete actual;
    
    lDEBUG << Log::DES("Animación");
}

void Animation::setTipoAnimation(tipoAnim a){
    anim = a;

    // Quad
    if(anim == tEaseInQuad){
	puntFun = &Animation::easeInQuad;
    }
    else if(anim == tEaseOutQuad){
	puntFun = &Animation::easeOutQuad;
    }
    else if(anim == tEaseInOutQuad){
	puntFun = &Animation::easeInOutQuad;
    }
	
    // Cubic
    else if(anim == tEaseInCubic){
	puntFun = &Animation::easeInCubic;
    }
    else if(anim == tEaseOutCubic){
	puntFun = &Animation::easeOutCubic;
    }
    else if(anim == tEaseInOutCubic){
	puntFun = &Animation::easeInOutCubic;
    }

    // Quart
    else if(anim == tEaseInQuart){
	puntFun = &Animation::easeInQuart;
    }
    else if(anim == tEaseOutQuart){
	puntFun = &Animation::easeOutQuart;
    }
    else if(anim == tEaseInOutQuart){
	puntFun = &Animation::easeInOutQuart;
    }

    // Back
    else if(anim == tEaseOutBack){
	puntFun = &Animation::easeOutBack;
    }

    // Linear y default
    else{
	puntFun = &Animation::easeLinear;
    }

}

void Animation::update(bool a){

    if(time - esperaInicial > duracion){
	for (int i = 0; i < numAttr; ++i)
	{
	    actual[i] = final[i];
	}
	return;
    }

    else if(time >= esperaInicial)
    {
	for (int i = 0; i < numAttr; ++i){
	    actual[i] = (*puntFun)(time - esperaInicial, inicial[i], change[i], duracion);
	}

    }
    
    if(a) ++time;
}



float Animation::get(int i){
    if(i < numAttr){
	return actual[i];
    }else{
	return 0;
    }
}

void Animation::setInicial(int i, int v){
    if(i < numAttr){
	inicial[i] = v;
	change[i] = final[i] - v;
	actual[i] = v;
    }
}
	
void Animation::setFinal(int i, int v){
    if(i < numAttr){
	final[i] = v;
	change[i] = v - inicial[i];
    }
}

void Animation::set(int i, int v1, int v2){
    if(i < numAttr){
	inicial[i] = v1;
	final[i] = v2;
	change[i] = v2 - v1;
	actual[i] = v1;
    }
}

void Animation::reverse(){
    int a;
    for (int i = 0; i < numAttr; ++i)
    {
	a = inicial[i];
	inicial[i] = final[i];
	final[i] = a;
	change[i] = final[i] - inicial[i];
    }

}

void Animation::end() { time = duracion + esperaInicial; update(false); };

void Animation::init() { time = 0; };

bool Animation::finished(){ 
/*
    int j = 0;
    for (int i = 0; i < numAttr; ++i)
    {
	if(final[i] == actual[i]) j++;
    }
    return j == numAttr;  //*/

    return time > duracion + esperaInicial;  
}
