#pragma once

/* ejemplo de uso: es un rectangulo que guarda coordenadas,
	Rectangulo rect = Rectango(0,0,20,20);
	if(rect.isIn(10,10))yay();
	else boo();

	tambien sirve para pasar todas las coordenadas mas facilmente que andar pasando todas una por una
*/

class Rectangulo
{

public:
	double x,y,ancho,alto;

public:
	Rectangulo();
	Rectangulo(double x,double y,double ancho,double alto); //crea el rectangulo
	bool isIn(double x, double y);//devuelve true si el punto pasado es parte del rectangulo
	~Rectangulo(void);//destruye el rectangulo
};
