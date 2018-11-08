#pragma once
#include "Monster.h"
#include<cstdlib>
#include<ctime>
#include <stdint.h>
#include "Projectiles/FireProjectile.h"
#include "Shooter.h"
/*dispara con
probabilidad 0.3 o si camina en el sentido en el que estaba mirando
con probabilidad 0.6. En caso contrario a ambos, decide si saltar,
moverse en la direcci�n contraria o quedarse quieto por 0.5
segundos de manera equiprobable. */

//	/		Ranovich		/	//
#define WaitingTimeGF 7
class GreenFatty :
	public Monster, public Shooter<FireProjectile>
{
public:
	GreenFatty(uint32_t x, uint32_t y, uint32_t ID = 0);
	~GreenFatty() {}
	void next();//Define la proxima accion
	void startWait(); //Lo pone en modo diablo
	void freeWait();//Lo libera
	void update(void * ptr);
	
private:
	//CGAction doing;
	uint16_t tickWaitStart;
	BeingState  currentState;
};
