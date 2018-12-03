#include "AllegroController.h"



Local2PlayerController::Local2PlayerController(ALLEGRO_EVENT_QUEUE * eventQueue, uint16_t player1ID, uint16_t player2ID)
	:eventFactory(eventQueue),Player1ID(player1ID),Player2ID(player2ID){}

void * Local2PlayerController::getEvent(void * data)
{
	runEv();

	void * temp = nullptr;
	if (events.size() != 0) {
		temp = events.front();	
		events.pop();
	}

	return temp;
}

Local1PlayerController::Local1PlayerController(ALLEGRO_EVENT_QUEUE * eventQueue, uint16_t player1ID)
	:eventFactory(eventQueue), Player1ID(player1ID) {}

void * Local1PlayerController::getEvent(void * data)
{
	runEv();

	void * temp = nullptr;
	if (events.size() != 0) {
		temp = events.front();	// Le tengo miedo a esto. Puede que se borren solos
		events.pop();
	}

	return temp;
}

void Local1PlayerController::runEv()
{

	if (eventFactory.getEvent()) {
		uint16_t id = this->Player1ID;
		GameEventType type = GameEventType::None;
		bool start = true;
		switch (eventFactory.getEventType())
		{
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (eventFactory.getKeyboardEvent().keycode)
			{
			case ALLEGRO_KEY_W:	type = GameEventType::Jump; id = Player1ID; start = true; break;
			case ALLEGRO_KEY_A:	type = GameEventType::Left; id = Player1ID; start = true; break;
			case ALLEGRO_KEY_D:	type = GameEventType::Right; id = Player1ID; start = true; break;
			case ALLEGRO_KEY_C:	type = GameEventType::Shoot; id = Player1ID; start = true; break;
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			switch (eventFactory.getKeyboardEvent().keycode)
			{
			case ALLEGRO_KEY_W:	type = GameEventType::Jump; id = Player1ID; start = false; break;
			case ALLEGRO_KEY_A:	type = GameEventType::Left; id = Player1ID; start = false; break;
			case ALLEGRO_KEY_D:	type = GameEventType::Right; id = Player1ID; start = false; break;
			case ALLEGRO_KEY_C:	type = GameEventType::Shoot; id = Player1ID; start = false; break;
			}
			break;
		case ALLEGRO_EVENT_TIMER:
			type = GameEventType::Timer;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			type = GameEventType::Exit;
			break;
		}

		if (type != GameEventType::None)
			this->events.push(new GameEvent(type, id,start));
	}
}



void Local2PlayerController::runEv()
{

	if (eventFactory.getEvent()) {
		uint16_t id;
		GameEventType type = GameEventType::None;
		switch (eventFactory.getEventType())
		{
		case ALLEGRO_EVENT_KEY_DOWN:			
			switch (eventFactory.getKeyboardEvent().keycode)
			{
			case ALLEGRO_KEY_W:	type = GameEventType::Jump; id = Player1ID; break;
			case ALLEGRO_KEY_A:	type = GameEventType::Left; id = Player1ID; break;
			case ALLEGRO_KEY_D:	type = GameEventType::Right; id = Player1ID; break;
			case ALLEGRO_KEY_C:	type = GameEventType::Shoot; id = Player1ID; break;
			case ALLEGRO_KEY_UP:	type = GameEventType::Jump; id = Player2ID; break;
			case ALLEGRO_KEY_LEFT:	type = GameEventType::Left; id = Player2ID; break;
			case ALLEGRO_KEY_RIGHT:	type = GameEventType::Right; id = Player2ID; break;
			case ALLEGRO_KEY_M:		type = GameEventType::Shoot; id = Player2ID; break;
			}
			break;
		case ALLEGRO_EVENT_TIMER:
			type = GameEventType::Timer;
			break;
		}

		if (type != GameEventType::None) 
			this->events.push(new GameEvent(type, id,true));
	}
}
