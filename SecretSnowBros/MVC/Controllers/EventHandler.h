#pragma once
#include "Controller.h"
#include "Event.h"
#include <vector>
#include <queue>



class EventHandler

{
public:
	EventHandler();
	~EventHandler();

	void loadController(Controller * controller);
	void loadController(Controller& controller);
	void getEvent();
	void killEvent();
	GameEvent * returnEvent();


private:
	std::vector<Controller*> controllers;
	std::queue<GameEvent*> events;

	GameEvent * currentEvent = nullptr;



};

