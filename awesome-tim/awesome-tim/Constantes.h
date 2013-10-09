#pragma once
#define NOMBRE_JUEGO "The Incredible Machine"

//frecuencias de simulacion y dibujo
#define FPS 60
#define FRAME_FRECUENCY 1000.0/FPS

//posiciones de las distintas partes del juego
#define ANCHO_PANTALLA 600 //ancho de la superficie
#define ANCHO_PANTALLA_LOGICO 120
#define ALTO_PANTALLA 600 //alto de la superficie
#define ALTO_PANTALLA_LOGICO 120

#define SEPARACION 10
#define SEPARACION_LOGICA 2

#define X_TERRENO (SEPARACION)
#define X_TERRENO_LOGICO (SEPARACION_LOGICA)

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

//tipos de figuras
#define TRIANGULO 1
#define CUADRADO 2
#define CIRCULO 3
#define POLIGONOREGULAR 4

#define PELOTABASQUET 5
#define PELOTABOWLING 6
#define GLOBOHELIO 7
#define BALANCIN 8
#define SOGA 9
#define PLATAFORMA 10
#define PELOTATENIS 11
#define ENGRANAJE 12
#define ENGRANAJE2 13
#define CINTATRANSPORTADORA 14
#define MOTOR 15
#define CORREA 16
#define LINEA 17

//valores fisicos

#define GRAVEDADY 9.8f * 10
#define GRAVEDADX 0.0f

#define RADIO_PELOTATENIS 2.0
#define RESTITUCION_PELOTATENIS 0.9999999999
#define DENSIDAD_PELOTATENIS 0.5
#define FRICCION_PELOTATENIS 0.3

#define RADIO_PELOTABASQUET 6.0
#define RESTITUCION_PELOTABASQUET 0.999999999999 //mas de 1 gana velocidad cada vez que rebota
#define DENSIDAD_PELOTABASQUET 2.0
#define FRICCION_PELOTABASQUET 0.999

#define RADIO_PELOTABOWLING 5.0
#define RESTITUCION_PELOTABOWLING 0.3
#define DENSIDAD_PELOTABOWLING 6.0
#define FRICCION_PELOTABOWLING 0.3

#define RADIO_GLOBOHELIO 4.0
#define RESTITUCION_GLOBOHELIO 0.5
#define FRICCION_GLOBOHELIO 0.3
#define DENSIDAD_GLOBOHELIO 0.01
#define VELOCIDAD_GLOBOHELIO -20.0

#define LARGO_SEGMENTO_SOGA 1
#define ALTO_SEGMENTO_SOGA 5

#define ANCHO_PLATAFORMA 10
#define ALTO_PLATAFORMA 5
#define PLATAFORMA_DENSIDAD 1
#define PLATAFORMA_FRICCION 1
#define PLATAFORMA_MAXLARGO (ANCHO_TERRENO_LOGICO/ANCHO_PLATAFORMA) //no me gusta, es corto, deberia cubrir la diagonal

#define RADIO_MINENGRANAJE 5.0
#define RADIO_MAXENGRANAJE 15.0
#define RESTITUCION_ENGRANAJE 0.3
#define DENSIDAD_ENGRANAJE 6.0
#define FRICCION_ENGRANAJE 5 //1.5
#define VELOCIDAD_ENGRANAJE2 10

#define RADIO_PUNTA_BALANCIN 1.5
#define ANCHO_BALANCIN 4
#define ALTO_BALANCIN 2

//cuadrantes
#define CUADRANTE1 1
#define CUADRANTE2 2
#define CUADRANTE3 3
#define CUADRANTE4 4

//Datos Default
#define FONDO_TERRENO "../images/fondo-gris.jpg"
#define ANGULO_DEFAULT 0
#define POSX_DEFAULT 0
#define POSY_DEFAULT 0
#define RADIO_DEFAULT 5
#define ANCHO_DEFAULT 5
#define ALTO_DEFAULT 5
#define BASE_DEFAULT 7
#define LARGO_PLATAFORMA_DEFAULT 10
#define INSTANCIAS_DEFAULT 100
#define VERTICES_DEFAULT 5
#define ID_DEFAULT ""

//Por si no estuviese claro: PI
#define PI 3.1415926535897932384626433832795028841971693993751058209749

//id imagenes
#define ImgSegmSoga "../images/Cuadrado.png"
#define ID_PLATAFORMA "../images/plataforma_madera.png"
#define ID_GLOBO "../images/Globo-Azul.jpg"
#define ID_PELOTATENIS "../images/Pelota-Tenis.png"
#define ID_PELOTABASQUET "../images/Pelota-Basket.png"
#define ID_PELOTABOWLING "../images/Bowling.png"
#define ID_ENGRANAJE "../images/engranaje.png"

#define ID_ENGRANAJE2_1 "../images/engranaje2-1.png"
#define ID_ENGRANAJE2_2 "../images/engranaje2-2.png"

#define ID_CINTA ""
#define ID_PUNTA_CINTA_IZQ ""
#define ID_PUNTA_CINTA_DER ""
#define ID_MOTOR ""
#define ID_CORREA "../images/correa.png"
#define ID_TABLA_BALANCIN ""
#define ID_PUNTA_BALANCIN ""

