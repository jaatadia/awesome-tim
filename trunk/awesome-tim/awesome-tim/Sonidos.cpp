#include "Sonidos.h"
#include "SDL_mixer.h"


bool Sonidos::initialized = false;
bool Sonidos::playSounds = true;
std::map<std::string,void*>* Sonidos::mapa = new std::map<std::string,void*>;

#include <iostream>

void Sonidos::initialize(){
	initialized = true;

	int aux = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	if(aux==-1){
		 printf("Mix_OpenAudio: %s\n", Mix_GetError());
	}

	//Sonidos:
	(*mapa)[POP_BALLOON] = (void*)Mix_LoadWAV(POP_BALLOON); //OK
	(*mapa)[SHOT_ARROW] = (void*)Mix_LoadWAV(SHOT_ARROW); //No suena :S
	(*mapa)[FIRE_GUN] = (void*)Mix_LoadWAV(FIRE_GUN); //OK
	(*mapa)[FLIPPER_UP] = (void*)Mix_LoadWAV(FLIPPER_UP); //OK
	(*mapa)[FLIPPER_DOWN] = (void*)Mix_LoadWAV(FLIPPER_DOWN); //OK
	(*mapa)[HUEVO_SOUND] = (void*)Mix_LoadWAV(HUEVO_SOUND); //OK
	(*mapa)[CARRITO_MUSIC] = (void*)Mix_LoadWAV(CARRITO_MUSIC); //OK
	(*mapa)[MOTOR_RATON_MUSIC] = (void*)Mix_LoadWAV(MOTOR_RATON_MUSIC); //No suena :S
	(*mapa)[CANIO_SOUND] = (void*)Mix_LoadWAV(CANIO_SOUND);
	(*mapa)[CODO_SOUND] = (void*)Mix_LoadWAV(CODO_SOUND);
	(*mapa)[BASKET_SOUND] = (void*)Mix_LoadWAV(BASKET_SOUND);
	(*mapa)[BALANCIN_SOUND] = (void*)Mix_LoadWAV(BALANCIN_SOUND);
	(*mapa)[BOWLING_SOUND] = (void*)Mix_LoadWAV(BOWLING_SOUND);
	(*mapa)[TENIS_SOUND] = (void*)Mix_LoadWAV(TENIS_SOUND);
	(*mapa)[TIJERA_SOUND] = (void*)Mix_LoadWAV(TIJERA_SOUND);
	(*mapa)[YUNQUE_SOUND] = (void*)Mix_LoadWAV(YUNQUE_SOUND);
	
	//Musica:
	(*mapa)[MOTOR_MUSIC] = (void*)Mix_LoadMUS(MOTOR_MUSIC); //OK
	(*mapa)[VELA_MUSIC] = (void*)Mix_LoadMUS(VELA_MUSIC); //OK
	(*mapa)[GLOBO_MUSIC] = (void*)Mix_LoadMUS(GLOBO_MUSIC);
	(*mapa)[CINTA_TRANSP_MUSIC] = (void*)Mix_LoadMUS(CINTA_TRANSP_MUSIC);
	(*mapa)[ENGRANAJE_MUSIC] = (void*)Mix_LoadMUS(ENGRANAJE_MUSIC);

	(*mapa)[VICTORY_MUS] = (void*)Mix_LoadMUS(VICTORY_MUS); //OK
	(*mapa)[MUSIC] = (void*)Mix_LoadMUS(MUSIC); //OK
}

void Sonidos::end(){
	//try{
	//	if(!initialized) return;

	//  stopMusic()

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

void Sonidos::playSound(const char *file,int cant){
	if(!playSounds) return;
	try{
		if(!initialized) initialize();
		if((*mapa)[file]!=NULL){
			Mix_PlayChannel(-1,(Mix_Chunk*)(*mapa)[file],cant);
		}
	}catch(...){
	}
}

void Sonidos::playMusic(const char* file){
	if(!playSounds) return;
	try{
		if(!initialized) initialize();
		stopMusic();
		if((*mapa)[file]!=NULL){
			Mix_PlayMusic((Mix_Music*)(*mapa)[file],-1);
		}
	}catch(...){
	}
}

void Sonidos::stopMusic(){
	if(!playSounds) return;
	try{
		if(!initialized) initialize();
		Mix_HaltMusic();
	}catch(...){
	}
}

void Sonidos::noSound(){
	playSounds = false;
}