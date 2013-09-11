#include "Programa.h"
#include "Juego.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"

//Inclusion de Test
#include "Test_Triangulo.h"
//#include "Test_Cuadrado.h"

void test(void){
	//CargadorYaml::cargarJuego("archivoYaml.yaml", NULL, NULL); //Linea para poder probar el YAML!!
	GeneradorYaml::pruebayaml();
	//Test_Triangulo::prueba_triangulo();
	//Test_Cuadrado::prueba_cuadrado();
	//Contenedor::pruebaContenedor();
}

int main(int argc, char* argv[]){

	//Activar solo en caso de que se deseen correr las pruebas
	test();

/*		
	Programa prog = Programa(argv[0]);//creo el programa
	prog.correr();//lo corro (duhh)
*/
	Juego juego = Juego(argv[0]);
	while (juego.isRunning()&&(!juego.huboFallos())){
		juego.onEvent();
		juego.onLoop();
		juego.onRender();
	}

	return 0;
}