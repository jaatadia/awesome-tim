#include "GeneradorYaml.h"

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

YAML::Emitter& operator << (YAML::Emitter& out,PoligonoRegular* polig){
out << YAML::BeginMap;
out << YAML::Key << "posX";
out << YAML::Value << polig->getX();
out << YAML::Key << "posY";
out << YAML::Value << polig->getY();
out << YAML::Key << "angulo";
out << YAML::Value << polig->getAngulo();
out << YAML::Key << "cant_vertices";
out << YAML::Value << polig->getCantVertices();
out << YAML::Key << "radio";
out << YAML::Value << polig->getRadio();
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

			case POLIGONOREGULAR:
				out << YAML::Value << "POLIGONOREGULAR";

				out << YAML::Key << "dimension";
				out << YAML::Value << (PoligonoRegular*) fig->getDimension();
				break;
			
			default:
				out << YAML::Value << "";
		};
		
	out << YAML::EndMap;
	return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,BotoneraController* botonera){

	//cosas de la botonera
	out << YAML::BeginMap;

		/*out << YAML::Key << "alto";
		out << YAML::Value << botonera->getAlto();
		out << YAML::Key << "ancho";
		out << YAML::Value << botonera->getAncho();
		*/

		//lista de figuras
		out << YAML::Key << "lista_figuras";
		out << YAML::Value << YAML::BeginSeq;
			//itero y imprimo de a una las figuras en sequence
			
			std::list<map<Figura *, int>> lista_figs = botonera->getListaFiguras();
			std::list<map<Figura *, int>>::iterator iter;
			
			for (iter = lista_figs.begin(); iter != lista_figs.end(); ++iter){
				out << YAML::BeginMap;
				out << YAML::Key << "figura";
				out << YAML::Value << ((std::map<Figura*,int>::iterator)((*iter).begin()))->first; //obtengo la figura y la emito
				out << YAML::Key << "cantidad_de_instancias";
				out << YAML::Value << ((std::map<Figura*,int>::iterator)((*iter).begin()))->second; //obtengo la cant de instancias q se pueden crear de esa fig
				out << YAML::EndMap;
			};
			
		out << YAML::EndSeq;

	out << YAML::EndMap;


	//lista de botones
	//out << YAML::BeginSeq;

	return out;
};

YAML::Emitter& operator << (YAML::Emitter& out,Terreno* terreno){

	//cosas del terreno
	out << YAML::BeginMap;

		/*out << YAML::Key << "alto";
		out << YAML::Value << terreno->getAlto();
		out << YAML::Key << "ancho";
		out << YAML::Value << terreno->getAncho();*/
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

	try{
	arch.open(file,std::ios::out);
	} catch (...) {
		return false;
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
	
	 //ERROREEEES???

	//creacion del emitter
	YAML::Emitter out;
	//para cambiar la indentacion
	//out.SetIndent(4);

	//llenar el emitter
	out << YAML::BeginMap;
		out << YAML::Key << "juego";
		out << YAML::Value <<			//adentro de juego
			
			YAML::BeginMap;
				out << YAML::Key << "terreno";
				out << YAML::Value << terreno; //adentro de terreno
	
				out << YAML::Key << "botonera";
				out << YAML::Value << botonera; //adentro de botonera
			out << YAML::EndMap;

	out << YAML::EndMap;


	//pasar el emiter al archivo
	arch << out.c_str(); //<< "\n";

	//cerrar el archivo
	try{
	arch.close();
	} catch (...) {
		return false;
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
	

	return true;
};

/*------------------------------------------------------------------------------
---------------------------PRUEBA GENERADOR YAML--------------------------------
------------------------------------------------------------------------------*/
int GeneradorYaml::pruebayaml(){

//Cuadrado* dim_cuad = new Cuadrado(10,10,3,3,60);
//Circulo* dim_circ = new Circulo(5,30,40,9);
//Figura* fig1 = new Figura("../images/Cuadrado.png",dim_cuad);
Figura* fig1 = new Figura("../images/Cuadrado.png",new Cuadrado(10,10,3,3,60));
//Figura* fig2 = new Figura("../images/Circulo.png",dim_circ);
Figura* fig2 = new Figura("../images/Circulo.png",new Circulo(5,30,40,9));


std::list<Figura*> lista_fig = std::list<Figura*>();
lista_fig.push_back(fig1);
lista_fig.push_back(fig2);


BotoneraController* botonera = new BotoneraController(8,80,2);
botonera->agregarBoton(fig1,10);
botonera->agregarBoton(fig2,10);

Terreno* terr = new Terreno(80,80);
terr->agregarFigura(fig1);
terr->agregarFigura(fig2);

guardarJuego("../yaml/GameStatePrueba.yml",botonera,terr);

delete fig1;
delete fig2;

return 0;
}
