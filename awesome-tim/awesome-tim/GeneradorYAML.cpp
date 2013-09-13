#include "GeneradorYaml.h"
#include "FiguraCuadrada.h"
#include "FiguraCircular.h"


YAML::Emitter& operator << (YAML::Emitter& out,Cuadrado* cuad){
out << YAML::BeginMap;
out << YAML::Key << "ancho";
out << YAML::Value << cuad->getAncho();
out << YAML::Key << "alto";
out << YAML::Value << cuad->getAlto();
out << YAML::Key << "posX";
out << YAML::Value << cuad->getX();
out << YAML::Key << "posY";
out << YAML::Value << cuad->getY();
out << YAML::Key << "angulo";
out << YAML::Value << cuad->getAngulo();
out << YAML::EndMap;
return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Circulo* circ){
out << YAML::BeginMap;
out << YAML::Key << "radio";
out << YAML::Value << circ->getRadio();
out << YAML::Key << "posX";
out << YAML::Value << circ->getX();
out << YAML::Key << "posY";
out << YAML::Value << circ->getY();
out << YAML::Key << "angulo";
out << YAML::Value << circ->getAngulo();
out << YAML::EndMap;
return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Triangulo* triang){
out << YAML::BeginMap;
out << YAML::Key << "posX";
out << YAML::Value << triang->getX();
out << YAML::Key << "posY";
out << YAML::Value << triang->getY();
out << YAML::Key << "angulo";
out << YAML::Value << triang->getAngulo();
out << YAML::Key << "base";
out << YAML::Value << triang->getAncho();
out << YAML::Key << "altura";
out << YAML::Value << triang->getAlto();
out << YAML::EndMap;
return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Figura* fig){
	out << YAML::BeginMap;
	out << YAML::Key << "ID";
	out << YAML::Value << fig->getID();
	out << YAML::Key << "tipo_dimension";

	switch (fig->getTipoDimension()) {
			case CUADRADO:
				out << YAML::Value << "CUADRADO";

				out << YAML::Key << "dimension";
				out << YAML::Value << (Cuadrado*) fig->getDimension();
				break;
				
			case CIRCULO:
				out << YAML::Value << "CIRCULO";

				out << YAML::Key << "dimension";
				out << YAML::Value << (Circulo*) fig->getDimension();
				break;

			case TRIANGULO:
				out << YAML::Value << "TRIANGULO";

				out << YAML::Key << "dimension";
				out << YAML::Value << (Triangulo*) fig->getDimension();
				break;
			
			default:
				out << YAML::Value << "";
		};
		
	out << YAML::EndMap;
	return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Botonera* botonera){

	//cosas de la botonera
	//lista de botones
	//out << YAML::BeginSeq;

	return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Terreno* terreno){

	//cosas del terreno
	out << YAML::BeginMap;

		out << YAML::Key << "alto";
		out << YAML::Value << terreno->getAlto();
		out << YAML::Key << "ancho";
		out << YAML::Value << terreno->getAncho();
		out << YAML::Key << "fondo";
		out << YAML::Value << terreno->getFondo();

		//lista de figuras
		out << YAML::Key << "lista_figuras";
		out << YAML::Value << YAML::BeginSeq;
			//itero y imprimo de a una las figuras en sequence
			std::list<Figura*> lista_figs = terreno->getListaFigs();
			std::list<Figura*>::iterator iter;
			for (iter = lista_figs.begin(); iter != lista_figs.end(); ++iter){
				out << (*iter);
			};
		out << YAML::EndSeq;

	out << YAML::EndMap;

	return out;
};

bool GeneradorYaml::guardarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	//creacion del arhchivo
	std::ofstream arch;
	arch.open("../yaml/GameState.yaml",std::ios::out); //ERROREEEES???

	//creacion del emitter
	YAML::Emitter out;
	//para cambiar la indentacion
	//out.SetIndent(4);

	//llenar el emitter
	out << YAML::BeginMap;
		out << YAML::Key << "juego";
		out << YAML::Value << // YAML::BeginSeq; //adentro de juego

			/*out <<*/YAML::BeginMap;
				out << YAML::Key << "terreno";
				out << YAML::Value << terreno; //adentro de terreno
			out << YAML::EndMap;
			
			out << YAML::BeginMap;
				out << YAML::Key << "botonera";
				out << YAML::Value << botonera; //adentro de botonera
			out << YAML::EndMap;
			
		// out << YAML::EndSeq;
	out << YAML::EndMap;


	//pasar el emiter al archivo
	arch << out.c_str(); //<< "\n";

	//cerrar el archivo
	arch.close();  //ERROREEEES???

	return true;
};

/*------------------------------------------------------------------------------
---------------------------PRUEBA GENERADOR YAML--------------------------------
------------------------------------------------------------------------------*/
int GeneradorYaml::pruebayaml(){

//Cuadrado* dim_cuad = new Cuadrado(10,10,3,3,60);
//Circulo* dim_circ = new Circulo(5,30,40,9);
//Figura* fig1 = new Figura("../images/Cuadrado.jpg",dim_cuad);
Figura* fig1 = new FiguraCuadrada("../images/Cuadrado.jpg",10,10,3,3,60);
//Figura* fig2 = new Figura("../images/Circulo.jpg",dim_circ);
Figura* fig2 = new FiguraCircular("../images/Circulo.jpg",5,30,40,9);


std::list<Figura*> lista_fig = std::list<Figura*>();
lista_fig.push_back(fig1);
lista_fig.push_back(fig2);


//Botonera* botonera = new Botonera(10,80,2);
//botonera->agregarBoton(1, new Superficie(8,30)); //cuadrado
//botonera->agregarBoton(2, new Superficie(8,30)); //circulo

Terreno* terr = new Terreno(80,80);
terr->agregarFigura(fig1);
terr->agregarFigura(fig2);

//creacion del arhchivo
std::ofstream arch;
arch.open("../yaml/GameState.yaml",std::ios::out);

//creacion del emiter
YAML::Emitter out;

//llenar el emiter con lo que nos interesa
out << YAML::BeginMap;
	out << YAML::Key << "juego";
	out << YAML::Value << //YAML::BeginSeq; //adentro de juego

		/*out <<*/YAML::BeginMap;
			out << YAML::Key << "terreno";
			out << YAML::Value << terr; //adentro de terreno
		out << YAML::EndMap;
		/*
		out << YAML::BeginMap;
			out << YAML::Key << "botonera";
			out << YAML::Value << botonera; //adentro de botonera
		out << YAML::EndMap;
		*/
	//out << YAML::EndSeq;
out << YAML::EndMap;


//pasar el emiter al archivo
arch << out.c_str(); //<< "\n";

//cerrar el archivo
arch.close();

delete fig1;
delete fig2;

return 0;
}
