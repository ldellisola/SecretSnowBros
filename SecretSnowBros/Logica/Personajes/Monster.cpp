#include "Monster.h"

#define ms50 (3)
#define FrozenTicks (ms50 *20 ) // 10 segundos 200


Monster::Monster(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxWaitTicks, uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID, uint16_t scorePoints)
	:Being(maxJumpTick,maxWalkTick, maxFallTicks,x,y,ID),
	maxWaitTick(maxWaitTicks),
	points(scorePoints),
	maxFrozenTick(FrozenTicks)
{
}
Monster ::~Monster ()
{
}

void Monster::freeze()
{
	if (freezeState<4)
	{
		freezeState++;
	}

}

void Monster::unfreeze()
{
	if (freezeState > 0) {
		freezeState--;
	}
}

void Monster::updateFreezeTick()
{
	freezeTick++;
}

void Monster::resetFreezeTick()
{
	freezeTick = 0;
}

uint16_t Monster::getFreezeState()
{
	return freezeState;
}

uint16_t Monster::getFreezeTick()
{
	return freezeTick;
}

bool Monster::isFrozen()
{
	return(freezeState > 0 ? true : false);
}

void Monster::setState(BeingState state)
{
	if (!isWaiting())
		Being::setState(state);
	else if (state == BeingState::Waiting)
		startWating();




}

void Monster ::collition(Being * player)
{
	if (player->getX() == this->x && player->getY() == this->y) {
		player->kill();
	}
	
}

void Monster::collition(Projectile * proy)
{
	if (proy->getX() == this->x && proy->getY() == this->y ) {
		this->freeze();
		proy->kill();
		proy->addScore(getPoints());
		
	}
}

void Monster::updateWaitTick()
{
	this->waitTick = (this->waitTick + 1) ;
}

void Monster::resetWaitTick()
{
	waitTick = 0;
}

bool Monster::isWaiting()
{
	return waiting;
}

void Monster::startWating()
{
	waiting = true;
}

void Monster::stopWaiting()
{
	waiting = false;
}

uint16_t Monster::getWaitTick()
{
	return waitTick;
}

uint16_t Monster::getPoints()
{
	return points;
}

void Monster::update(void * ptr) {

	if (isFrozen()) {
		updateFreezeTick();

		if (getFreezeTick() == maxFrozenTick) {
			unfreeze();
			resetFreezeTick();
		}
	}
	else {
		if (getHorizontalState() == BeingState::StillWalk && getVerticalState() == BeingState::StillJump) {
			if (!futureDirections.empty()) {
				setState(futureDirections.front());
				futureDirections.pop();
			}

		}
		else if (getHorizontalTicks() == 0 && getVerticalTicks() == 0) {
			if (!futureDirections.empty()) {
				setState(futureDirections.front());
				futureDirections.pop();
			}
		}


		Being::update(ptr);
	}

	/*if (this->getState() == BeingState::Walking && this->getTick() == this->maxWalkTick) {

		World * map = (World *)ptr;
		updateTicks();

		if (this->getDirection() == BeingDirection::Left && x - 1 >= 0 && map->map[x - 1][y] != 'F')
			this->x--;
		else if (this->getDirection() == BeingDirection::Right && x + 1 < map->columna &&map->map[x + 1][y] != 'F')
			this->x++;

		this->setState(BeingState::Still);
		this->resetTicks();
	}
	else if (this->getState() == BeingState::Jumping) {
		World * map = (World *)ptr;
		updateTicks();

		if (this->getTick() == this->maxJumpTick / 2 && this->y + 1 <map->fila && map->map[x][y + 1] != 'F') {
			this->y++;
		}
		else if (this->getTick() == this->maxJumpTick && this->y + 1 < map->fila && map->map[x][y + 1] == 'F') {
			this->y++;
			this->setState(BeingState::Falling);
			this->resetTicks();
		}
		else if (this->getTick() == this->maxJumpTick && this->y + 1 < map->fila && map->map[x][y + 1] != 'F') {
			this->y++;
			this->setState(BeingState::Still);
			this->resetTicks();
		}
	}
	else if (this->getState() == BeingState::Falling) {

		World * map = (World *)ptr;
		updateTicks();
		if (this->getTick() == this->maxJumpTick &&  this->y - 1 >= 0) {

			if (map->map[x][y - 1] == 'F') {
				this->setState(BeingState::Still);
				this->resetTicks();
			}
			else {
				this->y--;
				this->resetTicks();
			}

		}
	}
	else if (this->freezeState > 0 && this->getState()!= BeingState::Frozen) {
		this->setState(BeingState::Frozen);
		this->resetTicks();
	}
	else if (this->getState() == BeingState::Frozen) {
		if (this->freezeState==1 && this->getTick()> 134) {
				this->setState(BeingState::Still);
				this->resetTicks();
		}
		else if (this->freezeState == 2 && this->getTick()> 134) {
				this->freezeState = 1;
				this->resetTicks();
		}
		else if (this->freezeState == 3 && this->getTick()> 134) {
			this->freezeState = 2;
			this->resetTicks();
		}
		else if (this->freezeState == 4 && this->getTick()> 134) {
			this->freezeState = 3;
			this->resetTicks();
		}
	}*/
}