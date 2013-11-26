#include "Sonidos.h"


bool Sonidos::initialized = false;
bool Sonidos::playSounds = true;
//bool Sonidos::playSounds = false;
std::map<std::string,Mix_Chunk*>* Sonidos::mapaS = new std::map<std::string,Mix_Chunk*>;
std::map<std::string,Mix_Music*>* Sonidos::mapaM = new std::map<std::string,Mix_Music*>;

#include <iostream>

void Sonidos::initialize(){
	if(initialized) return;
	initialized = true;

	int aux = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	if(aux==-1){
		 printf("Mix_OpenAudio: %s\n", Mix_GetError());
		 initialized = false;
		 return;
	}

	//Sonidos:
	(*mapaM)[POP_BALLOON] = Mix_LoadMUS(POP_BALLOON); //OK
	//(*mapaM)[SHOT_ARROW] = Mix_LoadMUS(SHOT_ARROW); //No suena :S
	(*mapaM)[FIRE_GUN] = Mix_LoadMUS(FIRE_GUN); //OK
	//(*mapaM)[FLIPPER_UP] = Mix_LoadMUS(FLIPPER_UP); //OK
	//(*mapaM)[FLIPPER_DOWN] = Mix_LoadMUS(FLIPPER_DOWN); //OK
	(*mapaM)[HUEVO_SOUND] = Mix_LoadMUS(HUEVO_SOUND); //OK
	//(*mapaM)[CARRITO_MUSIC] = Mix_LoadMUS(CARRITO_MUSIC); //OK
	//(*mapaM)[MOTOR_RATON_MUSIC] = Mix_LoadMUS(MOTOR_RATON_MUSIC); //No suena :S
	
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
	
	playMusic(file);
	//if(!playSounds) return;
	//try{
	//	if(!initialized) initialize();
	//	if((*mapaS).count(file)<=0) return;
	//	if((*mapaS)[file]!=NULL){
	//		Mix_PlayChannel(-1,(*mapaS)[file],0);
	//	}
	//}catch(...){
	//}
}

void Sonidos::playMusic(const char* file){
	if(!playSounds) return;
	try{
		if(!initialized) initialize();
		stopMusic();
		if((*mapaM).count(file)<=0) return;
		if((*mapaM)[file]!=NULL){
			Mix_PlayMusic((*mapaM)[file],0);
		}
	}catch(...){
	}
}

void Sonidos::stopMusic(){
	if(!playSounds) return;
	try{
		if(!initialized)initialize();
		Mix_HaltMusic();
	}catch(...){
	}
}

void Sonidos::noSound(){
	playSounds = false;
}