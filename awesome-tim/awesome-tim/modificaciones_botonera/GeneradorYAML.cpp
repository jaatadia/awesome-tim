#include "GeneradorYaml.h"


bool GeneradorYaml::guardarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	return false;
};

YAML::Emitter& operator << (YAML::Emitter& out,Dimension* dim){
out << YAML::BeginMap;
out << YAML::Key << "angulo";
out << YAML::Value << dim->getAngulo();
out << YAML::Key << "posX";
out << YAML::Value << dim->getX();
out << YAML::Key << "posY";
out << YAML::Value << dim->getY();
out << YAML::EndMap;
return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Figura* fig){
out << YAML::BeginMap;
out << YAML::Key << "ID";
out << YAML::Value << fig->getID();
out << YAML::Key << "dimension";
out << YAML::Value << YAML::BeginSeq;
out << fig->getDimension();
out << YAML::EndSeq;
out << YAML::EndMap;
return out;
}

/*
YAML::Emitter& operator << (YAML::Emitter& out,Botonera* botonera){

	//cosas de la botonera
	//lista de botones
	//out << YAML::BeginSeq;

	return out;
};
*/

YAML::Emitter& operator << (YAML::Emitter& out,Terreno* terreno){

	//cosas del terreno
	out << YAML::BeginMap;

		//necesito un metodo para obtener la img de fondo
		out << YAML::Key << "alto";
		out << YAML::Value << terreno->getAlto();
		out << YAML::Key << "ancho";
		out << YAML::Value << terreno->getAncho();

		//lista de figuras
		out << YAML::Key << "lista_figuras";
		out << YAML::Value << YAML::BeginSeq;
			//necesito un metodo de terreno q me itere y devuelva de a una las figuras
		out << YAML::EndSeq;

	out << YAML::EndMap;

	return out;
};

int GeneradorYaml::pruebayaml(){

Cuadrado* dim_cuad = new Cuadrado(10,10,3,3,60);
Circulo* dim_circ = new Circulo(5,30,40,9);
Figura* fig1 = new Figura("../img/Cuadrado.jpg",dim_cuad);
Figura* fig2 = new Figura("../img/Circulo.jpg",dim_circ);


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
	out << YAML::Value << YAML::BeginSeq; //adentro de juego
		/*
		out << YAML::BeginMap;
			out << YAML::Key << "botonera";
			out << YAML::Value << botonera; //adentro de botonera
		out << YAML::EndMap;
		*/
		out << YAML::BeginMap;
			out << YAML::Key << "terreno";
			out << YAML::Value << terr; //adentro de terreno
		out << YAML::EndMap;

	out << YAML::EndSeq;
out << YAML::EndMap;


//pasar el emiter al archivo
arch << out.c_str() << "\n";

//cerrar el archivo
arch.close();

delete fig1;
delete fig2;

return 0;
}