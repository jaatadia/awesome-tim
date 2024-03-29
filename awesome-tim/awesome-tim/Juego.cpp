#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"
#include "Figura.h"
#include "Linea.h"
#include <vector>
#include "FactoryFiguras.h"

#include "ClientMessage.h"
#include "TransformFigureMessage.h"
#include "SetAreaMessage.h"
#include "CreateButtonMessage.h"
#include "UnionMessage.h"
#include "UnionMessage2.h"
#include "StringMessage.h"


Juego::Juego(const char *fileIn,const char *fileOut,MaquinaEstados* maq,bool usarVista){

	this->usarVista = usarVista;

	for(int i = 0;i<=MAX_CLIENTES;i++){
		this->botoneras[i] = new std::list<struct boton>;
	}

	posVector = 0;
	for(int i = 0;i<LARGO;i++){
		vector[i] = NULL;
	}

	for(int i=0;i<=MAX_CLIENTES;i++){
		areas[i][0] = i*10;
		areas[i][1] = i*10;
		areas[i][2] = (i+1)*10;
		areas[i][3] = (i+1)*10;
	}

	this->maq = maq;
	this->fileIn = fileIn;
	this->fileOut = fileOut;
	
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO,maq,false);
	if(usarVista){
		botonera = new BotoneraController(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	}
	
	for (int i = 0;i<=MAX_CLIENTES;i++){
		figuraEnAire[i]=NULL;
	}
	
	objetivo = cargar();

	if(usarVista){
		comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS,objetivo);
	}

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;
	clickPressed = false;
	contEventosMov = 0;

	Sonidos::playMusic(MUSIC);

}

std::string Juego::cargar(){

	cant_jugadores = 2;
	std::string objetivo = CargadorYaml::cargarJuego(fileIn,terreno,&cant_jugadores,botoneras,areas);
	this->maq->setMaxClients(cant_jugadores);

	std::list<Figura*> figs = terreno->getListaFigs();
	
	for (std::list<Figura*>::iterator iter = figs.begin();iter!= figs.end();iter++){
		while(vector[posVector]!=NULL){
			posVector++;
			if (posVector == LARGO/5){
				posVector = 0;
			}
		}
		(*iter)->numero = posVector;
		vector[posVector] = (*iter);
	}

	if(usarVista){
		for (std::list<struct boton>::iterator iter = botoneras[0]->begin(); iter != botoneras[0]->end();iter++){
			botonera->agregarBoton((*iter).figura,(*iter).cantInstancias);
		}
	}

	if(usarVista){
		if(botonera->estaVacia()){
			botonera->agregarBotonesDefault();
			botonera->resizear();
		}
		//necesario para que se ordenen cosas dentro de botonera
		botonera->ScrollUp();
	}
	
	return objetivo;
}

bool Juego::guardar(){
	return true;
}

Juego::~Juego(){
	
	for(int i = 0;i<=MAX_CLIENTES;i++){
		delete this->botoneras[i];
	}

	delete terreno;
	if(usarVista){
		delete botonera;
		delete comandos;
		delete EscalasDeEjes::getInstance();
		Contenedor::deleteContenedor();
	}
	for(int i=0;i<=MAX_CLIENTES;i++){
		if(figuraEnAire[i]!=NULL)delete figuraEnAire[i];
	}
}


//dibuja en pantalla

bool Juego:: onRender(Superficie* superficie){

	if (!usarVista) return false;

	bool dibujar = false;
	
	confirmarPosicionFiguraEnAire();
	
	if(this->huboCambios()){
		superficie->restore();
		setCambio(false);
		dibujar = true;
	}
	
	if(terreno->huboCambios()){
		//terreno->dibujate(superficie,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
		superficie->dibujarSupreficie(terreno->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
		dibujar = true;
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_BOTONERA_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_BOTONERA_LOGICO));
		dibujar = true;
	}
	
	if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
		dibujar = true;
	}

	for (int i = 0; i<=MAX_CLIENTES;i++){
		if(figuraEnAire[i]!=NULL){
			figuraEnAire[i]->dibujar(superficie);
			dibujar = true;
		}
	}

	return dibujar;
}
	
bool Juego:: onLoop(){
	
	//std::cout<<"Clientes Conectados: ";
	//for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
	//	std::cout<<(*iter)<<"|";
	//}
	//std::cout<<"\n";


	Message * msg;
	bool continuar = true;
	while ((continuar) && ((msg = this->maq->getProcessMessage())!=NULL)){
		switch(msg->getType()){
			/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
			case MSG_TYPE_CREATE_FIGURE:
				{
					CreateFigureMessage* c_msg = (CreateFigureMessage*)msg;
					Figura* fig = FactoryFiguras::create(c_msg);
					if(fig!=NULL){
						vector[fig->numero] = fig;
						if (c_msg->isInAir()){
							figuraEnAire[c_msg->getId()] = fig;
						}else{
							terreno->agregarFigura(fig);
						}
						for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
							if((*iter)!=(c_msg->getId())){
								this->maq->pushSendMessage(msg,(*iter));
							}
						}
					}
					cambiarInstancias(c_msg->getId(),c_msg->getFigureType(),-1);
				}
				break;
			/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
			case MSG_TYPE_CLIENT_MESSAGE:
				{
					ClientMessage* c_msg = (ClientMessage*)msg;
					switch (c_msg->getAction()){
						case A_CONNECT:
							{
								this->myClients.push_back(c_msg->getClientID());
								//mando las figuras del terreno
								std::list<Figura*> lista = terreno->getListaFigs();
								std::list<Figura*> listaUniones;
								for (std::list<Figura*>::iterator iter = lista.begin(); iter != lista.end();iter++){
									if((*iter)->esUnion()){//si es una union la mando despues
										listaUniones.push_back((*iter));
										continue;
									}
									CreateFigureMessage* f_msg = new CreateFigureMessage();
									f_msg->setId(0);
									f_msg->setFigureID((*iter)->numero);
									f_msg->setFigureType((*iter)->getTipoFigura());
									f_msg->setX((*iter)->getDimension()->getX());
									f_msg->setY((*iter)->getDimension()->getY());
									f_msg->setAngle((*iter)->getDimension()->getAngulo());
									f_msg->setInAir(false);
									double data1,data2;
									(*iter)->getExtraData(&data1,&data2);
									f_msg->setData1(data1);
									f_msg->setData2(data2);

									this->maq->pushSendMessage(f_msg,c_msg->getClientID());
								}

								//mando las uniones
								for (std::list<Figura*>::iterator iter = listaUniones.begin(); iter != listaUniones.end();iter++){

									//creo la union
									CreateFigureMessage* f_msg = new CreateFigureMessage();
									f_msg->setId(0);
									f_msg->setFigureID((*iter)->numero);
									f_msg->setFigureType((*iter)->getTipoFigura());
									f_msg->setX((*iter)->getDimension()->getX());
									f_msg->setY((*iter)->getDimension()->getY());
									f_msg->setAngle((*iter)->getDimension()->getAngulo());
									f_msg->setInAir(true);
									double data1,data2;
									(*iter)->getExtraData(&data1,&data2);
									f_msg->setData1(data1);
									f_msg->setData2(data2);
									this->maq->pushSendMessage(f_msg,c_msg->getClientID());

									//le asigno el punto1
									double x,y;
									UnionMessage* u_msg = new UnionMessage();
									u_msg->setClientID(0);
									((Linea*)(*iter))->getPunto1(&x,&y);
									u_msg->setFigsNum((*iter)->numero,x,y);
									this->maq->pushSendMessage(u_msg,c_msg->getClientID());
									
									//le asigno el punto2
									u_msg = new UnionMessage2();
									u_msg->setClientID(0);
									((Linea*)(*iter))->getPunto2(&x,&y);
									u_msg->setFigsNum((*iter)->numero,x,y);
									this->maq->pushSendMessage(u_msg,c_msg->getClientID());

									//la suelto
									TransformFigureMessage* t_msg = new TransformFigureMessage();
									t_msg->setClientID(0);
									t_msg->setFigureID((*iter)->numero);
									t_msg->setX((*iter)->getDimension()->getX());
									t_msg->setY((*iter)->getDimension()->getY());
									t_msg->setSizeChange(T_DROP);
									this->maq->pushSendMessage(t_msg,c_msg->getClientID());
									
								}


								
								//mando los botones
								std::list<struct boton>::iterator iter;
								for (iter = this->botoneras[c_msg->getClientID()]->begin();iter!=this->botoneras[c_msg->getClientID()]->end();iter++){
									CreateButtonMessage* b_msg = new CreateButtonMessage();
									b_msg->setId(0);
									b_msg->setFigureID((*iter).figura->numero);
									b_msg->setFigureType((*iter).figura->getTipoFigura());
									b_msg->setX((*iter).figura->getDimension()->getX());
									b_msg->setY((*iter).figura->getDimension()->getY());
									b_msg->setAngle((*iter).figura->getDimension()->getAngulo());
									b_msg->setInAir(false);
									double data1,data2;
									(*iter).figura->getExtraData(&data1,&data2);
									b_msg->setData1(data1);
									b_msg->setData2((*iter).cantInstancias);

									this->maq->pushSendMessage(b_msg,c_msg->getClientID());
								}
								
								//mandar tambien el area
								SetAreaMessage* a_msg = new SetAreaMessage();
								a_msg->setPuntos(this->areas[c_msg->getClientID()][0],this->areas[c_msg->getClientID()][1],this->areas[c_msg->getClientID()][2],this->areas[c_msg->getClientID()][3]);
								this->maq->pushSendMessage(a_msg,c_msg->getClientID());

								//mando las figuras en el aire
								for (int i = 0;i<=MAX_CLIENTES;i++){
									if(figuraEnAire[i] != NULL){
										CreateFigureMessage* f_msg = new CreateFigureMessage();
										f_msg->setId(i);
										f_msg->setFigureID(figuraEnAire[i]->numero);
										f_msg->setFigureType(figuraEnAire[i]->getTipoFigura());
										f_msg->setX(figuraEnAire[i]->getDimension()->getX());
										f_msg->setY(figuraEnAire[i]->getDimension()->getY());
										f_msg->setAngle(figuraEnAire[i]->getDimension()->getAngulo());
										f_msg->setInAir(true);
										double data1,data2;
										figuraEnAire[i]->getExtraData(&data1,&data2);
										f_msg->setData1(data1);
										f_msg->setData2(data2);
										this->maq->pushSendMessage(f_msg,c_msg->getClientID());

										//si es una linea y el primer punto ya fue puesto tengo que mandarlo
										if(figuraEnAire[i]->esUnion()){
											double x,y;
											((Linea*)figuraEnAire[i])->getPunto1(&x,&y);
											if(!(x < -100)){
												UnionMessage* u_msg = new UnionMessage();
												u_msg->setClientID(i);
												u_msg->setFigsNum(figuraEnAire[i]->numero,x,y);
												this->maq->pushSendMessage(u_msg,c_msg->getClientID());
											}
										}

									}
								}

								//mando el objetivo
								StringMessage* s_msg = new StringMessage();
								s_msg->setString(this->objetivo);
								this->maq->pushSendMessage(s_msg,c_msg->getClientID());
								
								std::cout<<"Se conecto el cliente n: "<< c_msg->getClientID() <<"\n";

								delete msg;
							}
							break;
						case A_DISCONECT:
							{
								if(this->figuraEnAire[c_msg->getClientID()]!=NULL){
									TransformFigureMessage* t_msg = new TransformFigureMessage();
									t_msg->setClientID(c_msg->getClientID());
									t_msg->setSizeChange(T_DROPDEAD);
									t_msg->setFigureID(figuraEnAire[c_msg->getClientID()]->numero);
									this->maq->returnProcessMessage(t_msg);
								}

								if(this->jugadoresListos.size()==this->cant_jugadores){
									for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
										if((*iter)!=((ClientMessage*)msg)->getClientID()){
											this->maq->pushSendMessage(msg,(*iter));
										}
									}
								}
								this->maq->removeClient(c_msg->getClientID());
								this->myClients.remove(c_msg->getClientID());
								try{
									this->jugadoresListos.remove(c_msg->getClientID());
								}catch(...){
								}
								
								std::cout<<"Se desconecto el cliente n: "<< c_msg->getClientID() <<"\n";
								if(this->myClients.size()==0){
									this->reload();
									std::cout << "Se han desconectado todos los clientes reiniciando el juego...\n";
								}
							}
							break;
						case A_READY:
							{
								this->jugadoresListos.push_back(c_msg->getClientID());
								this->jugadoresListos.unique();
								if(jugadoresListos.size()==this->cant_jugadores){
									continuar = false;
									this->maq->pushSendMessage(c_msg);
									this->play();
								}
							}
							break;
						case A_UNREADY:
							{
								if(this->jugadoresListos.size()==this->cant_jugadores){
									this->maq->pushSendMessage(c_msg);
								}
								try{
									this->jugadoresListos.remove(c_msg->getClientID());
								}catch(...){
								}
							}
					}
				}
				break;
			/* ++++++++++++++++++++++++++++++++++++++++++++++++*/
			case MSG_TYPE_TRANSFORM_FIGURE:
				{
					TransformFigureMessage* t_msg = (TransformFigureMessage*) msg;
					Figura* fig = vector[t_msg->getFigureID()];
					if(fig!=NULL){
						switch(t_msg->getSizeChange()){
							case T_RESTORE:
								fig->setLargo(t_msg->getLength());
							case T_ROTATE:
								fig->setAngulo(t_msg->getAngle());
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figuraEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_SHIFT:
								fig->shift();
								fig->setAngulo(t_msg->getAngle());
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figuraEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_SHRINK:
								fig->achicar();
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figuraEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_GROW:
								fig->agrandar();
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figuraEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_NONE:
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figuraEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_DROP:
								{
									figuraEnAire[t_msg->getClientID()] = NULL;
									terreno->agregarFigura(fig);
									fig->setX(t_msg->getX());
									fig->setY(t_msg->getY());

									if(!fig->esUnion()){
										DropFigureMessage* d_msg = new DropFigureMessage();
										d_msg->setClientID(t_msg->getClientID());
										d_msg->setFigureID(t_msg->getFigureID());
										this->maq->returnProcessMessage(d_msg);
									}
								}
								break;
							case T_DROPDEAD:
								cambiarInstancias(t_msg->getClientID(),fig->getTipoFigura(),1);
								figuraEnAire[t_msg->getClientID()] = NULL;
								vector[t_msg->getFigureID()] = NULL;
								delete fig;
								break;
							case T_REMOVE:
								cambiarInstancias(t_msg->getClientID(),fig->getTipoFigura(),1);
								fig->desUnir();
								vector[t_msg->getFigureID()] = NULL;
								terreno->eliminarFigura(fig);
								terreno->setCambio(true);
								delete fig;
								break;
						}

					}
					
					for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
						if((*iter)!=((CreateFigureMessage*)msg)->getId()){
							this->maq->pushSendMessage(msg,(*iter));
						}
					}
				}
				break;
			/* +++++++++++++++++++++++++++++++++++++++++++++++++++ */
			case MSG_TYPE_UNION1:
				{
					UnionMessage* u_msg = (UnionMessage*) msg;
					int numFig;
					double x,y;
					u_msg->getFigsNum(&numFig,&x,&y);
					((Linea*)vector[numFig])->setPunto1(x,y);

					for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
						if((*iter)!=u_msg->getClientID()){
							this->maq->pushSendMessage(msg,(*iter));
						}
					}
				}
				break;
			/* +++++++++++++++++++++++++++++++++++++++++++++++++++ */
			case MSG_TYPE_UNION2:
				{
					UnionMessage2* u_msg = (UnionMessage2*) msg;
					int numFig;
					double x,y;
					u_msg->getFigsNum(&numFig,&x,&y);
					((Linea*)vector[numFig])->setPunto2(x,y);

					for(std::list<int>::iterator iter = myClients.begin();iter != myClients.end();iter++){
						if((*iter)!=u_msg->getClientID()){
							this->maq->pushSendMessage(msg,(*iter));
						}
					}
				}
				break;
			/* +++++++++++++++++++++++++++++++++++++++++++++++++++ */
			case MSG_TYPE_DROP:
				{
					DropFigureMessage* d_msg = (DropFigureMessage*) msg;
					int clientID = d_msg->getClientID();
					int figureID = d_msg->getFigureID();

					Figura* fig = vector[figureID];

					if(terreno->posicionOcupada(fig)){
						DeleteFigureMessage* d_msg = new DeleteFigureMessage();
						d_msg->setClientID(clientID);
						d_msg->setFigureID(figureID);
						this->maq->pushSendMessage(d_msg,clientID);
					}
				}
				break;
			}
	}

	terreno->actualizarModelo(vector);
	return !continuar;
}

//manejo de eventos
bool Juego:: onEvent(Ventana* ventana,Superficie** sup){

if(!usarVista) return false;

SDL_Event evento;
double posClickX, posClickY;
bool aux = false;

while(SDL_PollEvent(&evento)){
	switch(evento.type){
		case SDL_WINDOWEVENT:
		{
			actuarVentana(ventana,sup,evento.window.windowID,evento.window);
			//actualiza las escalas si fue un resize
			break;
		}
		case SDL_KEYDOWN: 
		{
			if ((evento.key.keysym.sym == SDLK_LSHIFT) || (evento.key.keysym.sym == SDLK_RSHIFT))
				shiftPressed = true;

			//si fue backtrace entonces borrar una letra de comandos
			if (evento.key.keysym.sym == SDLK_BACKSPACE)
				comandos->borrarLetra();

			if (evento.key.keysym.sym == SDLK_KP_ENTER || evento.key.keysym.sym == SDLK_RETURN)
				comandos->enterKeyPressed(this);

			if (evento.key.keysym.sym == SDLK_TAB){
				if(clickPressed){
					if(figuraEnAire[0]) figuraEnAire[0]->shift();
					else terreno->shiftFigura();
				}
			}	

			break;
		}
		case SDL_KEYUP: 
		{
			if ((evento.key.keysym.sym == SDLK_LSHIFT) || (evento.key.keysym.sym == SDLK_RSHIFT))
				shiftPressed = false;

			break;
		}
		case SDL_TEXTINPUT:
		{
			char charIngresado;

			charIngresado = evento.text.text[0];
//			if(clickPressed){
				if(charIngresado == '+'){
					if(figuraEnAire[0]) figuraEnAire[0]->agrandar();
					else terreno->agrandarFigura();
				}else if(charIngresado == '-'){
					if(figuraEnAire[0]) figuraEnAire[0]->achicar();
					else terreno->achicarFigura();
//				}
			}else comandos->agregarLetra(charIngresado);

			break;
		}
		case SDL_MOUSEMOTION:
		{
			//convertir a unidades logicas

			double cantMovX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.motion.xrel);
			double cantMovY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.motion.yrel);

			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.motion.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.motion.y);

			//averiguar si esta en terreno o figuraViva u otro lado
				
			// y verificar que el boton izq este apretado o no deberia pasar arrastre, idem boton derecho
			if (terreno->adentroZonaTerreno(posClickX-X_TERRENO_LOGICO,posClickY-Y_TERRENO_LOGICO))
				if (evento.motion.state == SDL_BUTTON_LMASK){				
					terreno->arrastrarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
					}

			//muevo la figura voladora, si es que la hay
			if (figuraEnAire[0])
				if ((estaActiva)){
					confirmarPosicionFiguraEnAire();
					figuraEnAire[0]->cambiarPosicion(cantMovX, cantMovY);
					//como ver si se superpone tarda demasiado lo hago solo cada 5 movimientos!
					
					//para saber si choca con las de terreno tengo que relativizar su posicion!
					figuraEnAire[0]->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);

					if (contEventosMov % ITER_CHOQUE == 0){
						//si choca es superpuesta
						//para que no choque con las de terreno que sobrepasan el canvas
						if (terreno->adentroZonaTerreno(figuraEnAire[0]->getDimension()->getX()-X_TERRENO_LOGICO,figuraEnAire[0]->getDimension()->getY()-Y_TERRENO_LOGICO)){
							figuraEnAire[0]->setSuperpuesta( terreno->posicionOcupada(figuraEnAire[0]) );
						}else{
							figuraEnAire[0]->setSuperpuesta( false );
						}
					}
					//y vuelvo para atras
					figuraEnAire[0]->cambiarPosicion(X_TERRENO_LOGICO,Y_TERRENO_LOGICO);
				}
						
			//chequeo la posicion del mouse por si hay perdida de foco del terreno
			if (!terreno->adentroZonaTerreno(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO))
				terreno->soltarFigura();

			contEventosMov++;

			if (contEventosMov > 10000){
				contEventosMov = 0;
			}

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(figuraEnAire[0]){
				set2Click();
				break;
			}
			clickPressed = true;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			if (terreno->adentroZonaTerreno(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed)){
					//al borrar algo restauro su contador de instancias
					std::list<int> tipoFig = terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO,vector);
					botonera->restaurarInstancias(tipoFig);
				}
				else
					terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				

			if (posEnBotonera(posClickX,posClickY)){
				//es de la botonera
				botonera->handleEventBotonera(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_BOTONERA_LOGICO),  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_BOTONERA_LOGICO),  evento.button.type);
			}

			//puede que me haya devuelto la figura en aire
			figuraEnAire[0] = botonera->obtenerFiguraActual();
			if (figuraEnAire[0]){
				estaActiva = true;
				while(vector[posVector]!=NULL){
					posVector++;
					if (posVector == LARGO/5){
						posVector = 0;
					}
				}
				//innecesario pero por si acaso
				figuraEnAire[0]->numero = posVector;
				vector[posVector] = figuraEnAire[0];
				figuraEnAire[0]->setX(posClickX);
				figuraEnAire[0]->setY(posClickY);
			}
			if (posEnComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					comandos->click(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
				}

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			clickPressed = false;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			//O se suelta la figura agarrada por terreno
			terreno->soltarFigura();

			//Es siempre para la botonera, hasta que no se deja de clickear sigue scrolleando
			botonera->handleEventBotonera(posClickX - X_BOTONERA_LOGICO,  posClickY - Y_BOTONERA_LOGICO,  evento.button.type);

			if (figuraEnAire[0]){
				//o es de figura viva
				if(!(figuraEnAire[0]->getTipoFigura()==LINEA)&& !(figuraEnAire[0]->getTipoFigura()==SOGA)){
					soltarFiguraEnAire();
				}
			}

			comandos->release(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO),&aux,this);

			break;
		}
		case SDL_MOUSEWHEEL:
		{
			//scroll de botonera SIEMPRE sin importar la posicion
			if (evento.wheel.y > 0){	
				if(clickPressed){
					if(figuraEnAire[0]){
						figuraEnAire[0]->agrandar();
						if (terreno->adentroZonaTerreno(figuraEnAire[0]->getDimension()->getX()-X_TERRENO_LOGICO,figuraEnAire[0]->getDimension()->getY()-Y_TERRENO_LOGICO)){
							figuraEnAire[0]->setSuperpuesta( terreno->posicionOcupada(figuraEnAire[0]) );
						}else{
							figuraEnAire[0]->setSuperpuesta( false );
						}
					}else terreno->agrandarFigura();
				}else{
					this->botonera->ScrollUp();
				}
			}else if (evento.wheel.y < 0){
				if(clickPressed){
					if(figuraEnAire[0]){
						figuraEnAire[0]->achicar();
						if (terreno->adentroZonaTerreno(figuraEnAire[0]->getDimension()->getX()-X_TERRENO_LOGICO,figuraEnAire[0]->getDimension()->getY()-Y_TERRENO_LOGICO)){
							figuraEnAire[0]->setSuperpuesta( terreno->posicionOcupada(figuraEnAire[0]) );
						}else{
							figuraEnAire[0]->setSuperpuesta( false );
						}
					}else terreno->achicarFigura();
				}else{
					this->botonera->ScrollDown();
				}
			}
			break;
		}
		case SDL_QUIT: 
		{
			//salir del juego
			quit();
			break;
		}
	}
}
return aux;
}


void Juego::quit(){
	guardar();
	maq->salir();
}

void Juego::play(){
	Sonidos::stopMusic();
	maq->play(this->terreno);
}

void Juego::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

	switch (evento.event){
		case SDL_WINDOWEVENT_CLOSE:
		{
			//if (evento.windowID == ventana->getID())
				quit();

			break;
		}	
		//INVESTIGAR ESTE CASO

		//case SDL_WINDOWEVENT_SIZE_CHANGED:
		//{
		//	//cambio las escalas

		//break;
		//}
		case SDL_WINDOWEVENT_LEAVE:
		{
			//mouse salio de la pantalla
			
			terreno->soltarFigura();

			if (figuraEnAire[0])
				soltarFiguraEnAire();

			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			double anchoActual= evento.data1;
			double altoActual= evento.data2;

			if(anchoActual != altoActual){
				if(anchoActual<altoActual){
					altoActual = anchoActual;
				}else{
					anchoActual = altoActual;
				}
				ventana->resize(anchoActual,altoActual);
			}
			EscalasDeEjes::getInstance()->setEscalaX(UNIDADES_LOGICAS_TOTAL/anchoActual);
			EscalasDeEjes::getInstance()->setEscalaY(UNIDADES_LOGICAS_TOTAL/altoActual);
			//obtengo superficie resizeada para el juego, esta es la grande donde se pegan las otras.
			delete (*sup);
			(*sup) = new Superficie(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_PANTALLA_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_PANTALLA_LOGICO));

			//Y tambien cambian todas las vistas!!
			resizear();
			break;
		}
	}
}

void Juego::resume(){
	Sonidos::playMusic(MUSIC);
	this->setCambio(true);
	resizear();
}

void Juego::resizear(){
	if(usarVista){
		terreno->cambioVistaFiguras();
		terreno->resizear();

		botonera->resizear();
		//necesario moverla para que se ajuste la vista...
		botonera->ScrollDown();

		comandos->resizear();
	}
}

void Juego::setFondo(const char* dir){
	if(usarVista){
		terreno->setFondo(dir);
	}
}

bool Juego::posEnTerreno(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_TERRENO_LOGICO ;
	finalLogicoX = ANCHO_TERRENO_LOGICO + X_TERRENO_LOGICO;
	ppioLogicoY = Y_TERRENO_LOGICO;
	finalLogicoY = ALTO_TERRENO_LOGICO + Y_TERRENO_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::posEnBotonera(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_BOTONERA_LOGICO ;
	finalLogicoX = ANCHO_BOTONERA_LOGICO + X_BOTONERA_LOGICO;
	ppioLogicoY = Y_BOTONERA_LOGICO;
	finalLogicoY = ALTO_BOTONERA_LOGICO + Y_BOTONERA_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::posEnComandos(double posX,double posY){
	
	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_COMANDOS_LOGICO;
	finalLogicoX = ANCHO_COMANDOS_LOGICO + X_COMANDOS_LOGICO;
	ppioLogicoY = Y_COMANDOS_LOGICO;
	finalLogicoY = ALTO_COMANDOS_LOGICO + Y_COMANDOS_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

void Juego::confirmarPosicionFiguraEnAire(){
	if(usarVista){
		if (figEnEspacioIntermedio()){
			setCambio(true);
			terreno->setCambio(true);
			botonera->setCambio(true);
			comandos->setCambio(true);
		}else{
			if (figEnBotonera())
				botonera->setCambio(true);
			if (figEnTerreno())
				terreno->setCambio(true);
			if (figEnComandos())
				comandos->setCambio(true);
		}
	}
}

bool Juego::figEnEspacioIntermedio(){

	//intersecar figura en aire con los 12 segmentos en cuestion
	//si cruza cualquiera de los bordes asumo que toca el espacio de separacion
	//no es necesariamente cierto, puede tener un borde coincidente y estar incluido en una de las 3 areas y si alguien
	//tiene ganas de chequear eso hagalo.

	//obviamente tambien asumo que no puede estar por completo en la separacion.
	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figuraEnAire[i] ==NULL) continue;
		if( figuraEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||

			figuraEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||

			figuraEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
			figuraEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) 
			)
			return true;
	}
	return false;
}

//solo se usan si la figura en aire no toco contra ningun borde
//entonces si un punto coincide esta dentro de quien corresponda.
bool Juego::figEnBotonera(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figuraEnAire[i] ==NULL) continue;
		if (figuraEnAire[i]->getDimension()->getX()>X_BOTONERA_LOGICO && figuraEnAire[i]->getDimension()->getX()<X_BOTONERA_LOGICO+ANCHO_BOTONERA_LOGICO
			&& figuraEnAire[i]->getDimension()->getY()>Y_BOTONERA_LOGICO && figuraEnAire[i]->getDimension()->getY()<Y_BOTONERA_LOGICO+ALTO_BOTONERA_LOGICO )
			return true;
	}
	
	return false;
}

bool Juego::figEnTerreno(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figuraEnAire[i] ==NULL) continue;
		if (figuraEnAire[i]->getDimension()->getX()>X_TERRENO_LOGICO && figuraEnAire[i]->getDimension()->getX()<X_TERRENO_LOGICO+ANCHO_TERRENO_LOGICO
			&& figuraEnAire[i]->getDimension()->getY()>Y_TERRENO_LOGICO && figuraEnAire[i]->getDimension()->getY()<Y_TERRENO_LOGICO+ALTO_TERRENO_LOGICO )
			return true;
	}	
	return false;
}

bool Juego::figEnComandos(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figuraEnAire[i] ==NULL) continue;
		if (figuraEnAire[i]->getDimension()->getX()>X_COMANDOS_LOGICO && figuraEnAire[i]->getDimension()->getX()<X_COMANDOS_LOGICO+ANCHO_COMANDOS_LOGICO
			&& figuraEnAire[i]->getDimension()->getY()>Y_COMANDOS_LOGICO && figuraEnAire[i]->getDimension()->getY()<Y_COMANDOS_LOGICO+ALTO_COMANDOS_LOGICO )
			return true;
	}
	return false;
}




void Juego::soltarFiguraEnAire(){

	if(!usarVista) return;
	confirmarPosicionFiguraEnAire();

	if (terreno->adentroZonaTerreno(figuraEnAire[0]->getDimension()->getX()-X_TERRENO_LOGICO,figuraEnAire[0]->getDimension()->getY()-Y_TERRENO_LOGICO) && !figuraEnAire[0]->superpuesta){
		//relativizar posiciones al terreno!
		figuraEnAire[0]->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		terreno->agregarFigura( figuraEnAire[0] );
		figuraEnAire[0] = NULL;
	}else{

		botonera->restaurarInstanciaActual();
		vector[figuraEnAire[0]->numero] = NULL;
		delete figuraEnAire[0];
		figuraEnAire[0] = NULL;
	}
}


void Juego::set2Click(){
	if(!usarVista) return;
	if(figuraEnAire[0]->getTipoFigura()==LINEA){
		
		Linea* linea = ((Linea*)figuraEnAire[0]);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableCorrea(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();
			vector[figuraEnAire[0]->numero] = NULL;
			delete figuraEnAire;
			figuraEnAire[0] = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			botonera->setCambio(true);
			comandos->setCambio(true);
		}else{
			result->posAtableCorrea(&x,&y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);
				linea->actualizar();
			}else{
				if(linea->getFigura1() == result){
					botonera->restaurarInstanciaActual();
					vector[figuraEnAire[0]->numero] = NULL;
					delete figuraEnAire;
					figuraEnAire[0] = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					botonera->setCambio(true);
					comandos->setCambio(true);
				}else{
					linea->setFigura2(result);
					linea->getFigura1()->atarCorrea();
					linea->getFigura2()->atarCorrea();
					terreno->agregarFigura( figuraEnAire[0] );
					linea->actualizar();
					figuraEnAire[0] = NULL;
				}
			}
		}
	}else if(figuraEnAire[0]->getTipoFigura()==SOGA){
		
		Linea* linea = ((Linea*)figuraEnAire[0]);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableSoga(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();
			vector[figuraEnAire[0]->numero] = NULL;
			delete figuraEnAire[0];
			figuraEnAire[0] = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			comandos->setCambio(true);
			botonera->setCambio(true);
		}else{
			int res = result->esAtableSoga(x,y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);
				((Soga*)linea)->setNumsPosAtable(res,0);
				linea->actualizar();
			}else{
				if (result == linea->getFigura1()){
					botonera->restaurarInstanciaActual();			
					vector[figuraEnAire[0]->numero] = NULL;
					delete figuraEnAire[0];
					figuraEnAire[0] = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					comandos->setCambio(true);
					botonera->setCambio(true);
				}else{
					linea->setFigura2(result);
					((Soga*)linea)->setNumsPosAtable(((Soga*)linea)->num1,res);
					linea->actualizar();
					linea->getFigura1()->atarSoga(((Soga*)linea)->num1);
					linea->getFigura2()->atarSoga(((Soga*)linea)->num2);
					terreno->agregarFigura( figuraEnAire[0] );
					figuraEnAire [0]= NULL;
				}
			}
		}
	}
}

void Juego::cambiarInstancias(int cliente,int tipoFigura,int cantidad){
	std::list<struct boton>::iterator it;
	for(it = botoneras[cliente]->begin();it != botoneras[cliente]->end();it++){
		if((*it).figura->getTipoFigura()==tipoFigura){
			(*it).cantInstancias += cantidad;
		}
	}
}

void Juego::reload(){
	
	for(int i = 0;i<=MAX_CLIENTES;i++){
		delete this->botoneras[i];
	}
	for(int i=0;i<=MAX_CLIENTES;i++){
		if(figuraEnAire[i]!=NULL)delete figuraEnAire[i];
	}

	delete terreno;
	if(this->usarVista){
		delete botonera;
		delete comandos;
	}
	


	for(int i = 0;i<=MAX_CLIENTES;i++){
		this->botoneras[i] = new std::list<struct boton>;
	}

	for(int i=0;i<=MAX_CLIENTES;i++){
		areas[i][0] = i*10;
		areas[i][1] = i*10;
		areas[i][2] = (i+1)*10;
		areas[i][3] = (i+1)*10;
	}

	posVector = 0;
	for(int i = 0;i<LARGO;i++){
		vector[i] = NULL;
	}

	for (int i = 0;i<=MAX_CLIENTES;i++){
		figuraEnAire[i]=NULL;
	}

	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO,maq,false);
	if(usarVista){
		botonera = new BotoneraController(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	}
	
	objetivo = cargar();

	if(usarVista){
		comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS,objetivo);
	}

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;
	clickPressed = false;
	contEventosMov = 0;

	Sonidos::playMusic(MUSIC);


}
/*
bool Juego::posicionOcupada(){
	
	bool choca1 = false;
	bool choca2 = false;

	for(int i = 0 ; i < MAX_CLIENTES+1 ; i++){
		if (figuraEnAire[i]){
			choca1 = figuraEnAire[0]->choqueConFigura(figuraEnAire[i]);
			choca2 = figuraEnAire[i]->choqueConFigura(figuraEnAire[0]);
		}
	}

	return (choca1 || choca2);
}
*/