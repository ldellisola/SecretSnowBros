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
	//this->currentState = BeingState::Still; 
	//this->doing = CGAction::Straight;
}

void GreenFatty::next() {
	uint16_t probs = rand() % 100;
	/*if (probs < 30)	this->doing = CGAction::Shooting;
	else if (probs < 90) this->doing = CGAction::Straight;
	else if (probs < 93) this->doing = CGAction::Jump;
	else if (probs < 96) this->doing = CGAction::Still;
	else this->doing = CGAction::Reverse;*/
}

void GreenFatty::startWait() {
//	this->tickWaitStart = this->getTick();
	this->currentState = BeingState::Waiting;
}
void GreenFatty::freeWait() {
	/*if (this->getTick() > this->tickWaitStart + WaitingTimeGF) {
		this->currentState = BeingState::Still;
		this->tickWaitStart = 0;
	}*/
}
void GreenFatty::update(void * ptr){
//	if (this->getState() == BeingState::Walking && this->getTick() == this->maxWalkTick) {
//
//		World * map = (World *)ptr;
//		updateTicks();
//
//		if (this->getDirection() == BeingDirection::Left && x - 1 >= 0 && map->map[x - 1][y] != 'F')
//			this->x--;
//		else if (this->getDirection() == BeingDirection::Right && x + 1 < map->columna &&map->map[x + 1][y] != 'F')
//			this->x++;
//
//		this->setState(BeingState::Still);
//		this->resetTicks();
//	}
//	else if (this->getState() == BeingState::Jumping) {
//		World * map = (World *)ptr;
//		updateTicks();
//
//		if (this->getTick() == this->maxJumpTick / 2 && this->y + 1 < map->fila && map->map[x][y + 1] != 'F') {
//			this->y++;
//		}
//		else if (this->getTick() == this->maxJumpTick && this->y + 1 < map->fila && map->map[x][y + 1] == 'F') {
//			this->y++;
//			this->setState(BeingState::Falling);
//			this->resetTicks();
//		}
//		else if (this->getTick() == this->maxJumpTick && this->y + 1 < map->fila && map->map[x][y + 1] != 'F') {
//			this->y++;
//			this->setState(BeingState::Still);
//			this->resetTicks();
//		}
//	}
//	else if (this->getState() == BeingState::Shooting && this->getTick() == this->maxShootTicks) {
//		updateTicks();
//		
////		this->shoot();
//		this->setState(BeingState::Still);
//		this->resetTicks();
//	}
//	else if (this->getState() == BeingState::Falling) {
//
//		World * map = (World *)ptr;
//		updateTicks();
//
//		if (this->getTick() == this->maxJumpTick &&  this->y - 1 >= 0) {
//
//			if (map->map[x][y - 1] == 'F') {
//				this->setState(BeingState::Still);
//				this->resetTicks();
//			}
//			else {
//				this->y--;
//				this->resetTicks();
//			}
//
//		}
//
//	
//
//
//	}
//	else if (this->freezeState > 0 && this->getState() != BeingState::Frozen) {
//		this->setState(BeingState::Frozen);
//		this->resetTicks();
//	}
//	else if (this->getState() == BeingState::Frozen) {
//		if (this->freezeState == 1 && this->getTick() > 134) {
//			this->setState(BeingState::Still);
//			this->resetTicks();
//		}
//		else if (this->freezeState == 2 && this->getTick() > 134) {
//			this->freezeState = 1;
//			this->resetTicks();
//		}
//		else if (this->freezeState == 3 && this->getTick() > 134) {
//			this->freezeState = 2;
//			this->resetTicks();
//		}
//		else if (this->freezeState == 4 && this->getTick() > 134) {
//			this->freezeState = 3;
//			this->resetTicks();
//		}
//	}
}