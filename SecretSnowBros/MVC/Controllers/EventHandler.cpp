#include "EventHandler.h"



EventHandler::EventHandler()



{
}


EventHandler::~EventHandler()
{

}

void EventHandler::loadController(Controller * controller)
{
	this->controllers.push_back(controller);



}

void EventHandler::loadController(Controller & controller)
{
	this->controllers.push_back(&controller);

}

void EventHandler::getEvent()
{
	for (Controller * controller : controllers) {
		GameEvent *ev = (GameEvent *)controller->getEvent(nullptr);
		if (ev != nullptr) {
			this->events.push(ev);

		}


	}

}

void EventHandler::killEvent()
{
	if (currentEvent != nullptr) {
		delete currentEvent;
		currentEvent = nullptr;
	}
}

GameEvent * EventHandler::returnEvent()
{
	if (events.size() > 0) {
		currentEvent = events.front();

		events.pop();

		return currentEvent;
	}
	return nullptr;
}
