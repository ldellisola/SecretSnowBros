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
}

void GreenFatty::next() {
	//uint16_t probs = rand() % 100;
	uint16_t probs = 20;//DEBUG
	if (probs < 30) {
		// Dispara
		futureDirections.push(BeingState::Shooting);
	}
	else if (probs < 90) {
		//se queda Camina hacia adelante
		if (getHorizontalDir() == HorizontalDirection::Left)
			this->futureDirections.push(BeingState::WalkingLeft);
		else if (getHorizontalDir() == HorizontalDirection::Right)
			this->futureDirections.push(BeingState::WalkingRight);
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
		if (getHorizontalDir() == HorizontalDirection::Left)
			this->futureDirections.push(BeingState::WalkingRight);
		else if (getHorizontalDir() == HorizontalDirection::Right)
			this->futureDirections.push(BeingState::WalkingLeft);
		this->futureDirections.push(BeingState::StillWalk);
	}

}

void GreenFatty::update(void * ptr){
	World& map = *(World *)ptr;

	if (isFrozen()) {
		updateFreezeTick();

		if (getFreezeTick() == maxFrozenTick) {
			unfreeze();
			resetFreezeTick();
		}
	}
	else {
		if (getHorizontalState() == HorizontalState::Still && getVerticalState() == VerticalState::Still) {
			if (this->getHorizontalDir() == HorizontalDirection::Left && futureDirections.front() == BeingState::WalkingLeft && map.map[this->getY()][this->getX() - 1] == 'F') {
				setState(BeingState::WalkingRight);
				futureDirections.pop();
			}
			else if (this->getHorizontalDir() == HorizontalDirection::Right && futureDirections.front() == BeingState::WalkingRight && map.map[this->getY()][this->getX() + 1] == 'F') {
				setState(BeingState::WalkingLeft);
				futureDirections.pop();
			}
			else {
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

			if (this->getHorizontalDir() == HorizontalDirection::Right && this->getX() + 1 < map.columna)
				this->shoot(this->getX() + 1, this->getY(), HorizontalDirection::Right);
			else if (this->getHorizontalDir() == HorizontalDirection::Left && getX() - 1 >= 0)
				this->shoot(this->getX() - 1, this->getY(), HorizontalDirection::Left);
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
		
	}

	Shooter::updateProjectiles(ptr);

}

void GreenFatty::chooseAction(void * ptr)
{
	if (getHorizontalState() == HorizontalState::Still && getVerticalState() == VerticalState::Still) {
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
