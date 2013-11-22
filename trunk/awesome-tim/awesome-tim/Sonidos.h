#pragma once

#include <map>
#include <string>
#include "SDL_mixer.h"
#include "Constantes.h"

#define MUSIC "../music/modoEstatico.ogg"
#define VICTORY_MUS "../music/victory.ogg"

//MUSICA
#define MOTOR_MUSIC "../music/motor.ogg"
#define VELA_MUSIC "../music/vela.ogg"


//SONIDOS
#define POP_BALLOON "../music/pop.ogg"
#define SHOT_ARROW "..music/flecha.ogg"
#define FIRE_GUN "../music/disparoEscopeta.ogg"
#define FLIPPER_UP "../music/flipperup.ogg"
#define FLIPPER_DOWN "../music/flipperdown.ogg"
#define HUEVO_SOUND "../music/Huevo_rompiendose.ogg"
#define CARRITO_MUSIC "../music/carrito.ogg"
#define MOTOR_RATON_MUSIC "../music/raton.ogg"

class Sonidos{
private:
	static bool initialized;
	static std::map<std::string,Mix_Chunk*>* mapaS;
	static std::map<std::string,Mix_Music*>* mapaM;
	static bool playSounds;
public:
	static void playSound(const char *file,int cant=0);
	static void playMusic(const char *file);
	static void stopMusic();
	static void end();
	static void noSound();

//private:
	static void initialize();
	
};