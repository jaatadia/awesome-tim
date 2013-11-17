#pragma once

#include <map>
#include <string>
#include "Constantes.h"

#define POP_BALLOON "../music/pop.wav"
#define SHOT_ARROW "..music/flecha.wav"
#define FIRE_GUN "../music/disparoEscopeta.wav"
#define MUSIC "../music/modoEstatico.wav"
#define VICTORY_MUS "../music/victory.ogg"
#define FLIPPER_UP "../music/flipperup.wav"
#define FLIPPER_DOWN "../music/flipperdown.wav"
#define CARRITO_MUSIC "../music/carrito.wav"
#define HUEVO_MUSIC "../music/Huevo_rompiendose.wav"
#define MOTOR_MUSIC "../music/motor.wav"
#define VELA_MUSIC "../music/vela.wav"

class Sonidos{
private:
	static bool initialized;
	static std::map<std::string,void*>* mapa;

public:
	static void playSound(const char *file);
	static void playMusic(const char *file);
	static void stopMusic();
	static void end();

private:
	static void initialize();
	
};