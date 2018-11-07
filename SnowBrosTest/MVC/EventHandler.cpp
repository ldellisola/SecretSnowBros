#include "EventHandler.h"



EventHandler::EventHandler()
#ifdef _DEBUG
	:Logger("Logs/EventHandler", true)
#endif // _DEBUG


{
}


EventHandler::~EventHandler()
{

}

void EventHandler::loadController(Controller * controller)
{
	this->controllers.push_back(controller);

#if _DEBUG
	log("Loaded Controller N" + std::to_string(controllers.size()));
#endif

}

void EventHandler::loadController(Controller & controller)
{
	this->controllers.push_back(&controller);
#if _DEBUG
	log("Loaded Controller N" + std::to_string(controllers.size()));
#endif
}

void EventHandler::getEvent()
{
	for (Controller * controller : controllers) {
		GameEvent *ev = (GameEvent *)controller->getEvent(nullptr);
		if (ev != nullptr) {
			this->events.push(ev);

#if _DEBUG
			if (ev->getEventType() != GameEventType::Timer)
				log("Event retrieved from controller " + gameEv[(int)ev->getEventType()] + "as "+ (ev->isItStart() ? "start" : "stop"));
#endif
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
#if _DEBUG
		if (currentEvent->getEventType() != GameEventType::Timer)
			log("Event sent to Model " + gameEv[(int)currentEvent->getEventType()] + "as " + (currentEvent->isItStart() ? "start" : "stop"));
#endif

		events.pop();

		return currentEvent;
	}
	return nullptr;
}
