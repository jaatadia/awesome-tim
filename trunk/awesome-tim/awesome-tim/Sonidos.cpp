#include "Sonidos.h"


bool Sonidos::initialized = false;
bool Sonidos::playSounds = true;
std::map<std::string,Mix_Chunk*>* Sonidos::mapaS = new std::map<std::string,Mix_Chunk*>;
std::map<std::string,Mix_Music*>* Sonidos::mapaM = new std::map<std::string,Mix_Music*>;

#include <iostream>

void Sonidos::initialize(){
	initialized = true;

	int aux = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	if(aux==-1){
		 printf("Mix_OpenAudio: %s\n", Mix_GetError());
		 initialized = false;
		 return;
	}

	//Sonidos:
	(*mapaS)[POP_BALLOON] = Mix_LoadWAV(POP_BALLOON); //OK
	(*mapaS)[SHOT_ARROW] = Mix_LoadWAV(SHOT_ARROW); //No suena :S
	(*mapaS)[FIRE_GUN] = Mix_LoadWAV(FIRE_GUN); //OK
	(*mapaS)[FLIPPER_UP] = Mix_LoadWAV(FLIPPER_UP); //OK
	(*mapaS)[FLIPPER_DOWN] = Mix_LoadWAV(FLIPPER_DOWN); //OK
	(*mapaS)[HUEVO_SOUND] = Mix_LoadWAV(HUEVO_SOUND); //OK
	(*mapaS)[CARRITO_MUSIC] = Mix_LoadWAV(CARRITO_MUSIC); //OK
	(*mapaS)[MOTOR_RATON_MUSIC] = Mix_LoadWAV(MOTOR_RATON_MUSIC); //No suena :S
	(*mapaS)[CANIO_SOUND] = Mix_LoadWAV(CANIO_SOUND);
	(*mapaS)[CODO_SOUND] = Mix_LoadWAV(CODO_SOUND);
	(*mapaS)[BASKET_SOUND] = Mix_LoadWAV(BASKET_SOUND);
	(*mapaS)[BALANCIN_SOUND] = Mix_LoadWAV(BALANCIN_SOUND);
	(*mapaS)[BOWLING_SOUND] = Mix_LoadWAV(BOWLING_SOUND);
	(*mapaS)[TENIS_SOUND] = Mix_LoadWAV(TENIS_SOUND);
	(*mapaS)[TIJERA_SOUND] = Mix_LoadWAV(TIJERA_SOUND);
	(*mapaS)[YUNQUE_SOUND] = Mix_LoadWAV(YUNQUE_SOUND);
	
	//Musica:
	//(*mapaM)[MOTOR_MUSIC] = Mix_LoadMUS(MOTOR_MUSIC); //OK
	//(*mapaM)[VELA_MUSIC] = Mix_LoadMUS(VELA_MUSIC); //OK
	//(*mapaM)[GLOBO_MUSIC] = Mix_LoadMUS(GLOBO_MUSIC);
	//(*mapaM)[CINTA_TRANSP_MUSIC] = Mix_LoadMUS(CINTA_TRANSP_MUSIC);
	//(*mapaM)[ENGRANAJE_MUSIC] = Mix_LoadMUS(ENGRANAJE_MUSIC);

	(*mapaM)[VICTORY_MUS] = Mix_LoadMUS(VICTORY_MUS); //OK
	(*mapaM)[MUSIC] = Mix_LoadMUS(MUSIC); //OK
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
		if((*mapaS).count(file)<=0) return;
		if((*mapaS)[file]!=NULL){
			Mix_PlayChannel(-1,(*mapaS)[file],0);
		}
	}catch(...){
	}
}

void Sonidos::playMusic(const char* file){
	if(!playSounds) return;
	try{
		if(!initialized) initialize();
		stopMusic();
		if((*mapaM).count(file)<=0) return;
		if((*mapaM)[file]!=NULL){
			Mix_PlayMusic((*mapaM)[file],-1);
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