#pragma once

#include <map>
#include <string>
#include "Constantes.h"

#define MUSIC ""//"../music/modoEstatico.wav"
#define VICTORY_MUS ""//"../music/victory.ogg"

//MUSICA
#define MOTOR_MUSIC "../music/motor.wav"
#define VELA_MUSIC "../music/vela.wav"
#define GLOBO_MUSIC ""
#define CINTA_TRANSP_MUSIC ""
#define ENGRANAJE_MUSIC ""
#define MOTOR_RATON_MUSIC ""

//SONIDOS
#define POP_BALLOON "../music/pop.wav"
#define SHOT_ARROW "..music/flecha.wav"
#define FIRE_GUN "../music/disparoEscopeta.wav"
#define FLIPPER_UP "../music/flipperup.wav"
#define FLIPPER_DOWN "../music/flipperdown.wav"
#define HUEVO_SOUND "../music/Huevo_rompiendose.wav"
#define CARRITO_MUSIC "../music/carrito.wav"
#define CANIO_SOUND ""
#define CODO_SOUND ""
#define BASKET_SOUND ""
#define BALANCIN_SOUND ""
#define BOWLING_SOUND ""
#define TENIS_SOUND ""
#define TIJERA_SOUND ""
#define YUNQUE_SOUND ""

class Sonidos{
private:
	static bool initialized;
	static std::map<std::string,void*>* mapa;

public:
	static void playSound(const char *file,int cant=0);
	static void playMusic(const char *file);
	static void stopMusic();
	static void end();

private:
	static void initialize();
	
};