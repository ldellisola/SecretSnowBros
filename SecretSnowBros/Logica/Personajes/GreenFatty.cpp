#include "GreenFatty.h"

#define ms50 (3)

#define WalkTicks (ms50*6)	// 300ms
#define JumpTicks (ms50* 24)	// 1200ms
#define ShootTicks (ms50*18)		// 900ms
#define FallTicks (ms50*6)
#define StillTicks (ms50*10)	// 500ms

#define PointsAwarded (10)




GreenFatty::GreenFatty(uint32_t x, uint32_t y, uint32_t ID)
	:Monster (JumpTicks,WalkTicks,StillTicks,FallTicks,x,y,ID, PointsAwarded),
	Shooter(ShootTicks)
{
	this->lives = 1; 
	this->setHorizontalState(BeingState::StillWalk);
	setVerticalState(BeingState::StillJump);
}

void GreenFatty::next() {
	uint16_t probs = rand() % 100;
	if (probs < 30) {
		// Dispara
		futureDirections.push(BeingState::Shooting);
	}
	else if (probs < 90) {
		//se queda Camina hacia adelante
		this->futureDirections.push(BeingState::Walking);
		this->futureDirections.push(BeingState::StillWalk);
	}
	else if (probs < 93) {
		//salta
		this->futureDirections.push(BeingState::Jumping);
		this->futureDirections.push(BeingState::StillJump);
	}
	else if (probs < 96) {
		// se queda quieto
		this->futureDirections.push(BeingState::Waiting);
	}
	else {
		// camina hacia el otro lado
		if (getDirection() == BeingDirection::Left)
			setMovement(BeingDirection::Right);
		else if (getDirection() == BeingDirection::Right)
			setMovement(BeingDirection::Left);

		this->futureDirections.push(BeingState::Walking);
		this->futureDirections.push(BeingState::StillWalk);
	}

}

void GreenFatty::update(void * ptr){


	if (isFrozen()) {
		updateFreezeTick();

		if (getFreezeTick() == maxFrozenTick) {
			unfreeze();
			resetFreezeTick();
		}
	}
	else {
		if (getHorizontalState() == BeingState::StillWalk && getVerticalState() == BeingState::StillJump) {
			if (!futureDirections.empty() ) {
				setState(futureDirections.front());
				futureDirections.pop();
			}

		}
		else if (getHorizontalTicks() == 0 && getVerticalTicks() == 0) {
			if (!futureDirections.empty() ) {
				setState(futureDirections.front());
				futureDirections.pop();
			}
		}

		if (!isCoolingDown() && isShooting()) {
			World& map = *(World*)ptr;

			if (this->getDirection() == BeingDirection::Right && this->x + 1 < map.columna)
				this->shoot(this->x + 1, this->y, ProjectileDirection::Right);
			else if (this->getDirection() == BeingDirection::Left && x - 1 >= 0)
				this->shoot(this->x - 1, this->y, ProjectileDirection::Left);
			stopShooting();
			startCoolDown();
		}
		else if (isCoolingDown()) {
			updateShootingTicks();
			if (getShootingTicks() == 0) {
				stopCoolDown();
			}

		}



		Being::update(ptr);
		Shooter::updateProjectiles(ptr);
	}

	

	
}

void GreenFatty::chooseAction(void * ptr)
{
	if (getHorizontalState() == BeingState::StillWalk && getVerticalState() == BeingState::StillJump) {
		next();
	}

}

void GreenFatty::setState(BeingState state)
{
	Monster::setState(state);
	if (!isWaiting()) {
		if (state == BeingState::Shooting) {
			if (!isCoolingDown()) {
				resetShootingTicks();
				startShooting();
			}
		}
	}
}
