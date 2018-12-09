#include "AllegroController.h"


#include "allegro5/allegro.h"

Local1PlayerController::Local1PlayerController(ALLEGRO_EVENT_QUEUE * eventQueue, uint16_t player1ID)
	:eventFactory(eventQueue), Player1ID(player1ID) {

}

void * Local1PlayerController::getEvent(void * data)
{
	runEv();

	void * temp = nullptr;
	if (events.size() != 0) {
		temp = events.front();	
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
			case ALLEGRO_KEY_ESCAPE: type = GameEventType::Exit; id = Player1ID; start = true; break;
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


