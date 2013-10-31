#pragma once
#define NOMBRE_JUEGO "The Incredible Machine"
#define CANT_JUG_MAX 4

#define CANT_JUG_DEFAULT 1

//#define ES_SERVIDOR 1

//frecuencias de simulacion, dibujo y calculo de cosas
#define FPS 60
#define FRAME_FRECUENCY 1000.0/FPS

#define ITER_CHOQUE 4 //cantidad de movimientos a realizar entre verificaciones de choques

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
#define CINTATRANSPORTADORA 13
#define MOTOR 14
#define CORREA 15
#define LINEA 16
#define PEDACITOSOGA 17
#define VELA 18
#define POLEA 19 //el aro es lo mismo que la Polea
#define YUNQUE 20
#define CLAVO 21
#define TIJERA 22
#define HUEVO 23
#define DOMINO 24

//valores fisicos



#define COEF_MULT 52
#define GRAVEDADY 9.8f * 10
#define GRAVEDADX 0.0f

#define ANCHO_TIJERA 10
#define ALTO_TIJERA 5
#define DENSIDAD_TIJERA 1
#define FRICCION_TIJERA 1
#define RESTITUCION_TIJERA 0.1

#define BASE_CLAVO 0.07 * COEF_MULT //2.0
#define ALTURA_CLAVO 0.07 * COEF_MULT
#define DENSIDAD_CLAVO 1
#define FRICCION_CLAVO 1
#define RESTITUCION_CLAVO 0.1

#define RADIO_ARO 0.04 * COEF_MULT
#define RADIO_POLEA 0.05 * COEF_MULT
#define DENSIDAD_POLEA 1
#define FRICCION_POLEA 0.1
#define RESTITUCION_POLEA 0

#define RADIO_PELOTATENIS 0.045 * COEF_MULT //2.0
#define RESTITUCION_PELOTATENIS 0.76 //0.9
#define DENSIDAD_PELOTATENIS 3.0
#define FRICCION_PELOTATENIS 0.3

#define RADIO_PELOTABASQUET 0.11 * COEF_MULT //6.0
#define RESTITUCION_PELOTABASQUET 0.88 //0.9 //mas de 1 gana velocidad cada vez que rebota
#define DENSIDAD_PELOTABASQUET 2.0 //2.0
#define FRICCION_PELOTABASQUET 0.8

#define RADIO_PELOTABOWLING 0.10 * COEF_MULT //5.0
#define RESTITUCION_PELOTABOWLING 0.4 //0.3
#define DENSIDAD_PELOTABOWLING 20.0 //6.0
#define FRICCION_PELOTABOWLING 0.3

#define RADIO_GLOBOHELIO 0.09 * COEF_MULT //8.0
#define RESTITUCION_GLOBOHELIO 0.1
#define FRICCION_GLOBOHELIO 0.01 //0.01
#define DENSIDAD_GLOBOHELIO 1.1 //si se baja verificar que siga moviendo las plataformas
#define VELOCIDAD_GLOBOHELIO -20.0

#define ANCHO_PLATAFORMA 11
#define ALTO_PLATAFORMA 6
#define PLATAFORMA_DENSIDAD 1
#define PLATAFORMA_FRICCION 10
#define PLATAFORMA_MAXLARGO (ANCHO_TERRENO_LOGICO/ANCHO_PLATAFORMA) //no me gusta, es corto, deberia cubrir la diagonal
#define PLATAFORMA_MINLARGO 1

#define ANCHO_YUNQUE 10
#define ALTO_YUNQUE 5
#define DENSIDAD_YUNQUE 100
#define RESTITUCION_YUNQUE 0
#define FRICCION_YUNQUE 0.01

#define RADIO_MINENGRANAJE 5.0
#define RADIO_MAXENGRANAJE 15.0
#define RESTITUCION_ENGRANAJE 0.3
#define DENSIDAD_ENGRANAJE 6.0
#define FRICCION_ENGRANAJE 5 //1.5
#define VELOCIDAD_MOTOR 10
#define PORCENTAJE_SUPERPOSICION_ENGRANAJE 0.7

#define RADIO_PUNTA_BALANCIN 1.5
#define ANCHO_BALANCIN 30
#define ALTO_BALANCIN 4.5
#define ANGULO_BALANCIN_IZQ 45
#define ANGULO_BALANCIN_DER 315

#define RADIO_CINTA_TRANSPORTADORA RADIO_MAXENGRANAJE //de box2d, para cambiar la velocidad de giro de la vista
#define VELOCITY_MULTIPLIER 1 //junto con el de arriba para cambiar la velocidad de velocidad impuesta por la cinta

#define ALTO_CINTA 6
#define CINTA_TRANSP_MAXLARGO (ANCHO_TERRENO_LOGICO/ANCHO_CINTA) //no me gusta, es corto, deberia cubrir la diagonal
#define CINTA_TRANSP_MINLARGO 3
#define RADIO_CTRANSP_CIRC (ALTO_CINTA-1)/2
#define ANCHO_CINTA 8
#define RADIO_CTRANSP_CLAVO 0.88

#define ALTO_VELA 5
#define ANCHO_VELA 2
#define RADIO_LLAMA 2
#define RESTITUCION_VELA 0.2
#define DENSIDAD_VELA 5.0
#define FRICCION_VELA 0.1

#define RADIO_HUEVO 3
#define RESTITUCION_HUEVO 0.4
#define DENSIDAD_HUEVO 6.0
#define FRICCION_HUEVO 0.3

#define ANCHO_DOMINO 2
#define ALTO_DOMINO 4
#define RESTITUCION_DOMINO 0.5
#define DENSIDAD_DOMINO 5.0
#define FRICCION_DOMINO 0.3


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
#define INSTANCIAS_DEFAULT 100
#define VERTICES_DEFAULT 5
#define ID_DEFAULT ""
#define LARGO_PLATAFORMA_DEFAULT 2

//Por si no estuviese claro: PI
#define PI 3.1415926535897932384626433832795028841971693993751058209749

//id imagenes
//#define ImgSegmSoga "../images/Cuadrado.png"
#define ID_PLATAFORMA "../images/plataforma_madera.png"
#define ID_PELOTATENIS "../images/Pelota-Tenis.png"
#define ID_PELOTABASQUET "../images/Pelota-Basket.png"
#define ID_PELOTABOWLING "../images/Bowling.png"
#define ID_ENGRANAJE "../images/Icon-Gear02-Blue.png"

#define ID_MOTOR_1 "../images/engranaje2-1.png"
#define ID_MOTOR_2 "../images/engranaje2-2.png"

#define ID_CINTA "../images/cintamedio2.png"
#define ID_CTRANSP_CIRC "../images/cintacirculo.png"
#define ID_CTRANSP_CLAVO "../images/clavo.png"
#define ID_CINTA_TRANSPORTADORA "../images/cintatransport.png"

#define ID_MOTOR "../images/motor.jpg"
#define ID_CORREA "../images/correa.png"
#define ID_TABLA_BALANCIN "../images/rect.png"
#define ID_PUNTA_BALANCIN "../images/circulopunta.png"
#define ID_BALANCIN_IZQ "../images/balancin_izq.png"
#define ID_BALANCIN_DER "../images/balancin_der.png"
#define ID_SOGA "../images/rope.png"

#define ID_VELA_CERA "../images/vela_cera.png"
#define ID_LLAMA "../images/llama.png"
#define ID_VELA "../images/vela.jpg"

#define ID_POLEA "../images/polea.png"
#define ID_ARO "../images/aro.png"

#define ID_YUNQUE "../images/yunque.png"
#define ID_CLAVO "../images/clavoNinja.png"
#define ID_TIJERA "../images/tijeraAbierta.png"
#define ID_TIJERA_CERRADA "../images/tijeraCerrada.png"

#define ID_HUEVO "../images/huevo.jpg"
#define ID_HUEVO_ROMPIENDO "../images/huevoPartido.jpg"

#define ID_DOMINO "../images/domino.png"
#define ID_FICHA_DOMINO "../images/fichaDomino.jpg"

//posiciones de balancin
#define IZQUIERDA 1
#define DERECHA 2

//Sentidos del motor
#define SENT_HORARIO 1
#define SENT_ANTIHORARIO -1

//Para chocar circulos
#define VERTICES_ENVOLVENTE 7

//colores del globo
#define ID_GLOBO "../images/globoceleste.png"
#define ID_GLOBO_EXPLOTANDO1 "../images/globoExp1.png"
#define ID_GLOBO_EXPLOTANDO2 "../images/globoExp2.png"
#define ID_GLOBO_EXPLOTANDO3 "../images/globoExp3.png"
#define CANT_COLORES 6
#define COLOR_CELESTE "../images/globoceleste.png"
#define COLOR_ROJO "../images/globorojo.png"
#define COLOR_VERDE "../images/globoverde.png"
#define COLOR_AMARILLO "../images/globoamarillo.png"
#define COLOR_ROSA "../images/globorosa.png"
#define COLOR_VIOLETA "../images/globovioleta.png"

//constantes para la pantalla de que gano
#define DURACION_SEGS 1
#define DURACION_FRAMES DURACION_SEGS*FPS
#define CANT_IMGS 6 //si se quieren agregar mas hay que tocar juego play actualizarVictoria()
#define REPEAT true


#define INICIO_GANO1 0
#define GANO_1 "../images/gano1.png"
#define INICIO_GANO2 1*DURACION_FRAMES/CANT_IMGS
#define GANO_2 "../images/gano2.png"
#define INICIO_GANO3 2*DURACION_FRAMES/CANT_IMGS
#define GANO_3 "../images/gano3.png"
#define INICIO_GANO4 3*DURACION_FRAMES/CANT_IMGS
#define GANO_4 "../images/gano4.png"
#define INICIO_GANO5 4*DURACION_FRAMES/CANT_IMGS
#define GANO_5 "../images/gano5.png"
#define INICIO_GANO6 5*DURACION_FRAMES/CANT_IMGS
#define GANO_6 "../images/gano6.png"

#define REPEAT_FROM INICIO_GANO5

// NET
#define PUERTO "1111"
#define TAM_BUFFER 512