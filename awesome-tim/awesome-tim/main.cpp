#include "Programa.h"
#include "Juego.h"
#include "CargadorYaml.h"

int main(int argc, char* argv[]){

	GeneradorYaml::pruebayaml();
/*		
	Programa prog = Programa(argv[0]);//creo el programa
	prog.correr();//lo corro (duhh)
*/
	//CargadorYaml::cargarJuego("archivoYaml.yaml", NULL, NULL); //Linea para poder probar el YAML!!

	Juego juego = Juego(argv[0]);
	while (juego.isRunning()&&(!juego.huboFallos())){
		juego.onEvent();
		juego.onLoop();
		juego.onRender();
	}

	return 0;
}