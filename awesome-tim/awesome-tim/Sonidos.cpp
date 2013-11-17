#include "Sonidos.h"
#include "SDL_mixer.h"


bool Sonidos::initialized = false;
std::map<std::string,void*>* Sonidos::mapa = new std::map<std::string,void*>;


void Sonidos::initialize(){
	initialized = true;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	(*mapa)[POP_BALLOON] = (void*)Mix_LoadWAV(POP_BALLOON); //OK
	(*mapa)[SHOT_ARROW] = (void*)Mix_LoadWAV(SHOT_ARROW); //No suena :S
	(*mapa)[FIRE_GUN] = (void*)Mix_LoadWAV(FIRE_GUN); //OK
	(*mapa)[FLIPPER_UP] = (void*)Mix_LoadWAV(FLIPPER_UP); //OK
	(*mapa)[FLIPPER_DOWN] = (void*)Mix_LoadWAV(FLIPPER_DOWN); //OK

	(*mapa)[CARRITO_MUSIC] = (void*)Mix_LoadWAV(CARRITO_MUSIC);
	(*mapa)[HUEVO_MUSIC] = (void*)Mix_LoadWAV(HUEVO_MUSIC);
	(*mapa)[MOTOR_MUSIC] = (void*)Mix_LoadWAV(MOTOR_MUSIC);
	(*mapa)[VELA_MUSIC] = (void*)Mix_LoadWAV(VELA_MUSIC);

	(*mapa)[VICTORY_MUS] = (void*)Mix_LoadMUS(VICTORY_MUS);
	(*mapa)[MUSIC] = (void*)Mix_LoadMUS(MUSIC);
}

void Sonidos::end(){
	//try{
	//	if(!initialized) return;

	//	Mix_FreeChunk((Mix_Chunk*)(*mapa)[POP_BALLOON]);
	//	Mix_FreeChunk((Mix_Chunk*)(*mapa)[FLIPPER_UP]);
	//	Mix_FreeChunk((Mix_Chunk*)(*mapa)[FLIPPER_DOWN]);

	//	Mix_FreeMusic((Mix_Music*)(*mapa)[VICTORY_MUS]);
	//	Mix_FreeMusic((Mix_Music*)(*mapa)[MUSIC]);
	//	delete(mapa);

	//	Mix_CloseAudio();
	//}catch(...){
	//}
}

void Sonidos::playSound(const char *file){
	try{
		if(!initialized) initialize();
		Mix_PlayChannel(-1,(Mix_Chunk*)(*mapa)[file],0);
	}catch(...){
	}
}

void Sonidos::playMusic(const char* file){
	try{
		if(!initialized) initialize();
		stopMusic();
		Mix_PlayMusic((Mix_Music*)(*mapa)[file],-1);
	}catch(...){
	}
}

void Sonidos::stopMusic(){
	try{
		if(!initialized) initialize();
		Mix_HaltMusic();
	}catch(...){
	}
}
