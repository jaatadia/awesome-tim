#include "Sonidos.h"
#include "SDL_mixer.h"


bool Sonidos::initialized = false;
std::map<std::string,void*>* Sonidos::mapa = new std::map<std::string,void*>;


void Sonidos::initialize(){
	initialized = true;
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	(*mapa)[POP_BALLOON] = (void*)Mix_LoadWAV(POP_BALLOON);
	(*mapa)[VICTORY_MUS] = (void*)Mix_LoadMUS(VICTORY_MUS);
	(*mapa)[MUSIC] = (void*)Mix_LoadMUS(MUSIC);
}

void Sonidos::end(){
	if(!initialized) return;

	Mix_FreeChunk((Mix_Chunk*)(*mapa)[POP_BALLOON]);
	Mix_FreeMusic((Mix_Music*)(*mapa)[VICTORY_MUS]);
	Mix_FreeMusic((Mix_Music*)(*mapa)[MUSIC]);
	delete(mapa);

    Mix_CloseAudio();
}

void Sonidos::playSound(const char *file){
	if(!initialized) initialize();
	Mix_PlayChannel(-1,(Mix_Chunk*)(*mapa)[file],0);
}

void Sonidos::playMusic(const char* file){
	if(!initialized) initialize();
	stopMusic();
	Mix_PlayMusic((Mix_Music*)(*mapa)[file],-1);
}

void Sonidos::stopMusic(){
	if(!initialized) initialize();
	Mix_HaltMusic();
}
