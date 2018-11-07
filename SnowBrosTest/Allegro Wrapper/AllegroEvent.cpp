#include "AllegroEvent.h"



AllegroEventHandler::AllegroEventHandler(ALLEGRO_EVENT_QUEUE * queue)
{
	this->eventF = new AllegroEventFactory(queue);
	this->evnt = new AllegroEvent(EventType::Empty, 0);
}

AllegroEventHandler::~AllegroEventHandler()
{
	if (this->eventF != nullptr)
		delete this->eventF;
	if (this->evnt != nullptr)
		delete this->evnt;
}

bool AllegroEventHandler::isThereEvent()
{
	if (this->eventQueue.size() != 0)
		return true;
	else return false;
}

void AllegroEventHandler::getEvent()
{
	
	if (this->eventF->getEvent()) {
		
		switch (this->eventF->getEventType()) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			evnt->setType(EventType::DisplayClose);
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			evnt->setType(EventType::KeyDown);
			evnt->setValue(eventF->getKeyboardEvent().keycode);
			evnt->setTimestamp(eventF->getKeyboardEvent().timestamp);
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			evnt->setType(EventType::KeyChar);
			evnt->setValue(eventF->getKeyboardEvent().keycode);
			evnt->setModifier(eventF->getKeyboardEvent().modifiers);
			evnt->setTimestamp(eventF->getKeyboardEvent().timestamp);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			evnt->setType(EventType::KeyUp);
			evnt->setValue(eventF->getKeyboardEvent().keycode);
			evnt->setTimestamp(eventF->getKeyboardEvent().timestamp);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			evnt->setType(EventType::MouseDown);
			evnt->setValue(eventF->getMouseEvent().button);
			evnt->setCoordinates(eventF->getMouseEvent().x, eventF->getMouseEvent().y);
			evnt->setTimestamp(eventF->getMouseEvent().timestamp);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			evnt->setType(EventType::MouseUp);
			evnt->setValue(eventF->getMouseEvent().button);
			evnt->setCoordinates(eventF->getMouseEvent().x, eventF->getMouseEvent().y);
			evnt->setTimestamp(eventF->getMouseEvent().timestamp);
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			evnt->setType(EventType::MouseMoved);
			evnt->setCoordinates(eventF->getMouseEvent().x, eventF->getMouseEvent().y);
			break;
		case ALLEGRO_EVENT_TIMER:
			evnt->setType(EventType::Timer);
			break;
		}
		if (evnt->getType() != EventType::Empty) {
			eventQueue.push(*evnt);
			evnt->setType(EventType::Empty);
		}
	}





}

AllegroEvent AllegroEventHandler::ObtainEvent()
{
	AllegroEvent temp = this->eventQueue.front();
	this->eventQueue.pop();
	return temp;
}
