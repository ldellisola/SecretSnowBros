#pragma once
#include "Controller.h"
#include "Event.h"
#include "../AllegroV2/AllegroFactory.h"

#include <queue>
#include <memory>

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



class Local2PlayerController : public Controller
{
public:
	Local2PlayerController(ALLEGRO_EVENT_QUEUE * eventQueue, uint16_t player1ID, uint16_t player2ID = NAN);

	void * getEvent(void * data);
private:
	AllegroEventFactory eventFactory;

	void runEv();

	std::queue<GameEvent*> events;
	const uint16_t Player1ID, Player2ID;
};