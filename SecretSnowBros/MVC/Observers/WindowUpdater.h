#pragma once



#include "Observer.h"
#include"AllwBasics/AllegroWindow.h"




class WindowUpdater :
	public Observer
{
public:
	WindowUpdater(AllegroWindow& win)
		:wind(win)
	{	}
	~WindowUpdater(){}
	void draw(void *ptr) {
		wind.update();
	}
private:
	AllegroWindow& wind;
};



