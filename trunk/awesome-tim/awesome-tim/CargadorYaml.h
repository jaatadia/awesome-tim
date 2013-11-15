#pragma once

#include "yaml-cpp/yaml.h"

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Constantes.h"

#include "BotoneraController.h"
#include "Terreno.h"
#include "Posicion.h"

#include "Cuadrado.h"
#include "Circulo.h"
#include "Triangulo.h"
#include "PoligonoRegular.h"

#include "Figura.h"
#include "Plataforma.h"
#include "PelotaBasquet.h"
#include "PelotaBowling.h"
#include "GloboHelio.h"
#include "PelotaTenis.h"
#include "Engranaje.h"
#include "Motor.h"
#include "Balancin.h"
#include "Linea.h"
#include "Soga.h"
#include "CintaTransportadora.h"
#include "GeneradorDeFigurasCompuestas.h"
#include "Vela.h"
#include "Clavo.h"
#include "Aro.h"
#include "Polea.h"
#include "Yunque.h"
#include "Huevo.h"
#include "Tijera.h"
#include "Domino.h"
#include "Carrito.h"
#include "Queso.h"
#include "PaletaFlipper.h"
#include "Arco.h"
#include "Flecha.h"
#include "Escopeta.h"
#include "MotorRaton.h"
#include "Canio.h"
#include "Codo.h"
#include "Chinche.h"

#include "Boton.h"

class CargadorYaml{
public:
	
	static std::string cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno, int* cant_jugadores);

	//botoneras y areas tienen 5 espacios en el array, para la botoneras del cliente 1 se deveria guardar en botonera[1] (si quieren la botonera del server y el area del server se puede guardar en el 0)
	//areas contiene las limitaciones de los terrenos de la misma manera que el anterior
	//areas[i][0] = x1; //del cliente nro i
	//areas[i][1] = y1; 
	//areas[i][2] = x2; 
	//areas[i][3] = y2; 
	static std::string cargarJuego(const char* fileIn,Terreno* terreno,int* cant_jugadores,std::list<struct boton> botoneras[],double areas[][4]){
		return "hola";
	}

private:

	static std::string ruta_archivo;

	static void cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera);
	static void cargar_botones_de_cliente(const YAML::Node& listaFiguras, BotoneraController* botonera);
	static void cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno);
	static Figura* cargar_figura(const YAML::Node& nodoFig);
	static Figura* crearFigura(const YAML::Node& nodoFigura, const char* tipo_figura);
	static void agregarZonasClientes(const YAML::Node& nodoTerrenoCliente,Terreno* terreno);

	//Funciones de validacion de datos
	static bool cant_instancias_valida(int instancias);
	static bool tipo_figura_valida(const char* tipo_figura);
	static bool posicion_validaX(double posX);
	static bool posicion_validaY(double posY);
	static bool angulo_valido(double angulo);
	static bool largo_valido(int largo);
	static bool alto_valido(double alto);
	static bool ancho_valido(double ancho);
	static bool radio_valido(double radio);
	static bool cant_vertices_valida(int cant);
	static bool base_triangulo_valida(double base);
	static bool sentido_valido(int sentido);
	static bool opcion_valida(const char* opcion);
	static bool cantidad_jugadores_valida(int cantidad);

	static std::string concatenar_archivo(std::string mensaje, int linea, std::string archivo);
	static std::string concatenar_archivo(std::string mensaje, std::string archivo);
	static void imprimir_error_linea(std::string mensaje, int linea);
	static void imprimir_error_sin_linea(std::string mensaje);
	static void imprimir_error_excepcion(std::string mensaje,std::string what);


	static Figura* crearCirculo(const YAML::Node& nodoFigura);
	static Figura* crearPoligono(const YAML::Node& nodoFigura);
	static Figura* crearCuadrado(const YAML::Node& nodoFigura);
	static Figura* crearTriangulo(const YAML::Node& nodoFigura);
	static Figura* crearPlataforma(const YAML::Node& nodoFigura);
	static Figura* crearBalancin(const YAML::Node& nodoFigura, int sentido);
	static Figura* crearGloboHelio(const YAML::Node& nodoFigura);
	static Figura* crearBolaBowling(const YAML::Node& nodoFigura);
	static Figura* crearPelotaBasquet(const YAML::Node& nodoFigura);
	static Figura* crearMotor(const YAML::Node& nodoFigura);
	static Figura* crearSoga(const YAML::Node& nodoFigura);
	static Figura* crearCorrea(const YAML::Node& nodoFigura);
	static Figura* crearEngranaje(const YAML::Node& nodoFigura);
	static Figura* crearCintaTransportadora(const YAML::Node& nodoFigura);
	static Figura* crearPelotaTenis(const YAML::Node& nodoFigura);
	static Figura* crearVela(const YAML::Node& nodoFigura);
	static Figura* crearClavo(const YAML::Node& nodoFigura);
	static Figura* crearAro(const YAML::Node& nodoFigura);
	static Figura* crearPolea(const YAML::Node& nodoFigura);
	static Figura* crearYunque(const YAML::Node& nodoFigura);
	static Figura* crearHuevo(const YAML::Node& nodoFigura);
	static Figura* crearTijera(const YAML::Node& nodoFigura);
	static Figura* crearDomino(const YAML::Node& nodoFigura);
	static Figura* crearCarrito(const YAML::Node& nodoFigura);
	static Figura* crearPaleta(const YAML::Node& nodoFigura);
	static Figura* crearQueso(const YAML::Node& nodoFigura);
	static Figura* crearArco(const YAML::Node& nodoFigura);
	static Figura* crearEscopeta(const YAML::Node& nodoFigura);
	static Figura* crearMotorRaton(const YAML::Node& nodoFigura);
	static Figura* crearChinche(const YAML::Node& nodoFigura);

	static Figura* crearCanio(const YAML::Node& nodoFigura);
	static Figura* crearCodo(const YAML::Node& nodoFigura);
	
	static void obtenerCantidadDeJugadores(const YAML::Node& nodo, int* cant);
	static void obtenerPosicion(const YAML::Node& nodoFigura, double* posX, double* posY);
	static void obtenerAngulo(const YAML::Node& nodoFigura, double* angulo);
	static void obtenerLargo(const YAML::Node& nodoFigura, int* largo);
	static void obtenerAncho(const YAML::Node& nodoFigura, double* ancho);
	static void obtenerAlto(const YAML::Node& nodoFigura, double* alto);
	static void obtenerID(const YAML::Node& nodoFigura, std::string* ID);
	static void obtenerRadio(const YAML::Node& nodoFigura,double* radio);
	static void obtenerVertices(const YAML::Node& nodoFigura,int* vertices);
	static void obtenerBaseTriangulo(const YAML::Node& nodoFigura, double* base);
	static void obtenerExtremos(const YAML::Node& nodoFigura,double* x1,double* y1,double* x2,double* y2);
	static void obtenerSentido(const YAML::Node& nodoFigura,int* sentido);
	static bool obtenerPropiedadFiguraFija(const YAML::Node& nodoFigura);
	static bool obtenerPropiedadFiguraObjetivo(const YAML::Node& nodoFigura);
	static bool obtenerPropiedadFiguraInteractuable(const YAML::Node& nodoFigura);
	static void establecerZonaPorDefault(double* x1,double* y1,double* x2,double* y2);
	static void obtenerZona(const YAML::Node& nodoZona,double* x1,double* y1,double* x2,double* y2);
	static void obtenerPos(const YAML::Node& nodoFigura,double* posX, double* posY, double X_Default, double Y_Default);
	static std::string obtenerObjetivo(const YAML::Node& nodo);

};
