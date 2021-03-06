#pragma once
#include "Controller.h"
#include "Event.h"
#include "AllwInit/AllegroFactory.h"

#include <queue>
#include <memory>
//Clase encargada de la obtencion de inputs
class Local1PlayerController: public Controller
{
public:
	Local1PlayerController(ALLEGRO_EVENT_QUEUE * eventQueue,uint16_t player1ID);


	void * getEvent(void * data);
private:
	AllegroEventFactory eventFactory;

	void runEv();



	std::queue<GameEvent*> events;
	const uint16_t Player1ID;
};

