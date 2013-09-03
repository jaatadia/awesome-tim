#include "Programa.h"
#include "Juego.h"

int main(int argc, char* argv[]){
	
	
	Programa prog = Programa(argv[0]);//creo el programa
	prog.correr();//lo corro (duhh)

	
	Juego juego = Juego(argv[0]);
	while (juego.isRunning()&&(!juego.huboFallos())){
		juego.onEvent();
		juego.onLoop();
		juego.onRender();
	}
	
	return 0;
}