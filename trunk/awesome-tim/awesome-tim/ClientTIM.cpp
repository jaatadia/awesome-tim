#include "ClientTIM.h"

ClientTIM::ClientTIM(void)
{
}

ClientTIM::~ClientTIM(void)
{
}

void ClientTIM::run(char* rutaIn, char* rutaOut){
	MEstados juego = MEstados(rutaIn,rutaOut);

	double tiempoTardado = 0;
	double tiempoExtra = 0;
	double frames = 0;
	double tiempo = 0;
	double cant = 0;

	struct timeb tInicial, tFinal;

	while (juego.isRunning()&&(!juego.huboFallos())){
		
		if(tiempo>=1000){
			std::cout<<"FPS: "<< frames*1000/tiempo << " FramesSkipped: "<<cant<<"\n";
			tiempo = 0;
			frames = 0;
			cant=0;
		}
		
		frames++;

		//clock_t tInicial = clock();
   		ftime(&tInicial);

		bool aux = juego.onEvent();
		juego.onLoop();
		juego.onRender();
		
		if (aux) continue;

		//clock_t tFinal = clock();
		ftime(&tFinal);
		
		tiempoTardado = (1000.0 *tFinal.time + tFinal.millitm) - (1000.0 *tInicial.time + tInicial.millitm);

		tiempoExtra += FRAME_FRECUENCY - tiempoTardado;
		tiempoExtra = FRAME_FRECUENCY - tiempoTardado;

		tiempo += tiempoTardado;

		if(tiempoExtra>=0){
			juego.esperar(tiempoExtra);
			tiempo+=tiempoExtra;;
			tiempoExtra=0;
		}else{
			while(tiempoExtra<0){
				cant++;
				
				ftime(&tInicial);
				juego.onLoop();
				ftime(&tFinal);

				tiempoTardado = (1000.0 *tFinal.time + tFinal.millitm) - (1000.0 *tInicial.time + tInicial.millitm);
				tiempo += tiempoTardado;
				tiempoExtra += (FRAME_FRECUENCY -tiempoTardado);

			}
			//std::cout<<"Ciclios salteados: "<< cant << "\n";

		}	
	}
	//mato el thread
	this->kill();
}