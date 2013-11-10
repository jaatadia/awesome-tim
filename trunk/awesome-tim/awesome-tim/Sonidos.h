#pragma once

#include <map>
#include <string>
#include "Constantes.h"

#define POP_BALLOON "../music/pop.wav"
#define SHOT_ARROW POP_BALLOON
#define FIRE_GUN POP_BALLOON
#define MUSIC "../music/modoEstatico.wav"
#define VICTORY_MUS "../music/victory.ogg"

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