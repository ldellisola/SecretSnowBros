#pragma once
#include <stdint.h>
#include <string>

enum class GameEventType
{
	Jump,Shoot,Left,Right,Timer,Exit,None
};

#ifdef _DEBUG
const std::string gameEv[] = { "Jump","Shoot","Left","Right","Timer","Exit","Stop","None" };

#endif


class GameEvent
{
public:
	GameEvent(GameEventType type, uint16_t ID, bool start) {
		this->eventType = type;
		this->ID = ID;
		this->start = start;
	}
	GameEvent(){}
	GameEventType getEventType() { return eventType; }
	void setEventType(GameEventType eventType) { this->eventType = eventType; }
	uint16_t getID() { return ID; }
	void setID(uint16_t ID) { this->ID = ID; }
	bool isItStart() { return start; }
private:
	GameEventType eventType;
	bool start ;
	uint16_t ID;

};

