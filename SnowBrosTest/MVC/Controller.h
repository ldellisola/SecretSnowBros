#pragma once
class Controller
{
public:
	Controller();
	~Controller();
	virtual void * getEvent(void * ptr) = 0;
};

