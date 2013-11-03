#pragma once

#include <map>
#include <string>
#include "Constantes.h"

#define POP_BALLOON "../images/pop.wav"
#define MUSIC "../images/music.wav"
#define VICTORY_MUS "../images/victory.ogg"

class Sonidos{
private:
	static bool initialized;
	static std::map<std::string,void*>* mapa;

public:
	static void playSound(const char *file);
	static void playMusic(const char *file);
	static void stopMusic();

private:
	static void initialize();
	
};