#include "Polea.h"



Figura* Polea::getIzq(Polea* poleaPadre){
	if(this->getFigura1() == NULL){
		return NULL;
	}else if(this->getFigura1()!=poleaPadre){
		if(this->getFigura1()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura1()))->getIzq(this);
		}else{
			return this->getFigura1();
		}
	}else{
		if(this->getFigura2() == NULL){
			return NULL;
		}if(this->getFigura2()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura2()))->getDer(this);
		}else{
			return this->getFigura2();
		}
	}
}

Figura* Polea::getDer(Polea* poleaPadre){
	if(this->getFigura2() == NULL){
		return NULL;
	}else if(this->getFigura2()!=poleaPadre){
		if(this->getFigura2()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura2()))->getDer(this);
		}else{
			return this->getFigura2();
		}
	}else{
		if(this->getFigura1() == NULL){
			return NULL;
		}if(this->getFigura1()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura1()))->getIzq(this);
		}else{
			return this->getFigura1();
		}
	}
}


Polea* Polea::getPolIzq(Polea* poleaPadre,int* num){
	if(this->getFigura1() == NULL){
		return NULL;
	}else if(this->getFigura1()!=poleaPadre){
		if(this->getFigura1()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura1()))->getPolIzq(this,num);
		}else{
			*num = 1;
			return this;
		}
	}else{
		if(this->getFigura2() == NULL){
			return NULL;
		}if(this->getFigura2()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura2()))->getPolDer(this,num);
		}else{
			*num = 2;
			return this;
		}
	}
}


Polea* Polea::getPolDer(Polea* poleaPadre,int* num){
	if(this->getFigura2() == NULL){
		return NULL;
	}else if(this->getFigura2()!=poleaPadre){
		if(this->getFigura2()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura2()))->getPolDer(this,num);
		}else{
			*num = 2;
			return this;
		}
	}else{
		if(this->getFigura1() == NULL){
			return NULL;
		}if(this->getFigura1()->getTipoFigura()==POLEA){
			return ((Polea*)(this->getFigura1()))->getPolIzq(this,num);
		}else{
			*num = 1;
			return this;
		}
	}
}
