#pragma once
#include "Monster.h"

#include<cstdlib>
#include<ctime>
#include <stdint.h>
/*se mueven en la dirección en la
que estaban mirando con una probabilidad de 0,75. En el caso que
no continúen en la dirección anterior, es equiprobable que salten,
que se muevan en la dirección contraria o que se queden quietos
por 0,5 segs.*/

//	/		Troll Toll		/	//
#define WaitingTimeCG 7




class CrazyGuy :
	public Monster{
public:
	CrazyGuy(uint32_t x, uint32_t y,uint32_t ID=0);
	virtual ~CrazyGuy(){}
	void chooseAction(void *ptr);
	void next();//Define la proxima accion

private:
};

