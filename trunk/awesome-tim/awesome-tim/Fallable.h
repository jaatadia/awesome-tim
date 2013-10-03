#pragma once

//clase base para saber si una clase fallo, implementada por ventana, superficie, e imagen

/* ejemplo de uso
	Superficie* superf = new Superficie(80,80);
	if superf->huboFallos() doStuff();


	otro ejemplo: si estamos implementando una clase que extiende fallable

	if (hacerCosa()==-1){
		this->fallar();
		return;
	}


*/


class Fallable
{
private:
	bool fallo;
public:
	virtual ~Fallable(){};
	Fallable();//cosntructor
	bool huboFallos();//devuelve true si hubo fallos
	void fallar();//indica que el objeto debe fallar (uso interno pero se permite usar por que se me antoja :P )
};
