#pragma once

#define NOMBRE_JUEGO "The Incredible Machine"

#define ANCHO_PANTALLA 600 //ancho de la superficie
#define ANCHO_PANTALLA_LOGICO 120
#define ALTO_PANTALLA 600 //alto de la superficie
#define ALTO_PANTALLA_LOGICO 120

#define SEPARACION 10
#define SEPARACION_LOGICA 2

#define X_TERRENO (SEPARACION)
#define X_TERRENO_LOGICO X_TERRENO/5

#define Y_TERRENO (SEPARACION)
#define Y_TERRENO_LOGICO (SEPARACION_LOGICA)

#define ANCHO_TERRENO 500
#define ANCHO_TERRENO_LOGICO 100
#define ALTO_TERRENO 500
#define ALTO_TERRENO_LOGICO 100

#define X_BOTONERA (X_TERRENO + ANCHO_TERRENO + SEPARACION) 
#define X_BOTONERA_LOGICO (X_TERRENO + ANCHO_TERRENO + SEPARACION)/5
#define Y_BOTONERA (SEPARACION)
#define Y_BOTONERA_LOGICO (SEPARACION_LOGICA)
#define ANCHO_BOTONERA (ANCHO_PANTALLA - X_BOTONERA - SEPARACION) 
#define ANCHO_BOTONERA_LOGICO (ANCHO_PANTALLA - X_BOTONERA - SEPARACION)/5
#define ALTO_BOTONERA (ALTO_TERRENO)
#define ALTO_BOTONERA_LOGICO (ALTO_TERRENO)/5

#define X_COMANDOS SEPARACION
#define X_COMANDOS_LOGICO SEPARACION_LOGICA
#define Y_COMANDOS (Y_TERRENO + ALTO_TERRENO + SEPARACION)
#define Y_COMANDOS_LOGICO (Y_TERRENO + ALTO_TERRENO + SEPARACION)/5
#define ANCHO_COMANDOS (ANCHO_PANTALLA - 2*SEPARACION)
#define ANCHO_COMANDOS_LOGICO (ANCHO_PANTALLA - 2*SEPARACION)/5
#define ALTO_COMANDOS (ALTO_PANTALLA - Y_COMANDOS - SEPARACION) 
#define ALTO_COMANDOS_LOGICO (ALTO_PANTALLA - Y_COMANDOS - SEPARACION) /5

#define UNIDADES_LOGICAS_TOTAL 120

#define PI 3.1415926535897932384626433832795028841971693993751058209749

#define TRIANGULO 1
#define CUADRADO 2
#define CIRCULO 3
#define POLIGONOREGULAR 4

#define CUADRANTE1 1
#define CUADRANTE2 2
#define CUADRANTE3 3
#define CUADRANTE4 4

//Datos Default
#define FONDO_TERRENO "../images/test.jpg"
#define ANGULO_DEFAULT 0
#define POSX_DEFAULT 0
#define POSY_DEFAULT 0
#define RADIO_DEFAULT 5
#define ANCHO_DEFAULT 5
#define ALTO_DEFAULT 5
#define INSTANCIAS_DEFAULT 100