#pragma once
class Observer
{
public:
	Observer();
	~Observer();
	virtual void draw(void * data) = 0;
};

