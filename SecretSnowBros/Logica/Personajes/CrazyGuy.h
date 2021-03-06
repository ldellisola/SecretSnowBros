#pragma once
#include "Monster.h"

#include<cstdlib>
#include<ctime>
#include <stdint.h>
/*se mueven en la direcci�n en la
que estaban mirando con una probabilidad de 0,75. En el caso que
no contin�en en la direcci�n anterior, es equiprobable que salten,
que se muevan en la direcci�n contraria o que se queden quietos
por 0,5 segs.*/

//	/		Troll Toll		/	//





class CrazyGuy :
	public Monster{
public:
	CrazyGuy(uint32_t x, uint32_t y,uint32_t ID=0);
	virtual ~CrazyGuy(){}

	// It chooses the next action to be taken if the monster hasn't decided any other action before
	void chooseAction(void *ptr);
	

private:
	void next();
};

