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

	if (player->getX() == this->getX() && player->getY() == this->getY()) {
		player->kill();
	}

	if (dynamic_cast<Shooter<FireProjectile>*>(this)) {
		auto temp = (Shooter<Projectile>*) this;

		std::vector<Projectile*>& shoots = temp->getProjectiles();
		
		//for (Projectile * sht : shoots) {
		//	player->collition(sht);
		//}
	}


	
}

void Monster::collition(Projectile * proy)
{
	if (proy->getX() == this->getX() && proy->getY() == this->getY() ) {
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
		if (getHorizontalState() == HorizontalState::Still && getVerticalState() == VerticalState::Still) {
			if (!futureDirections.empty() && futureDirections.front() != BeingState::Shooting) {
				setState(futureDirections.front());
				futureDirections.pop();
			}

		}
		else if (getHorizontalTicks() == 0 && getVerticalTicks() == 0) {
			if (!futureDirections.empty() && futureDirections.front() != BeingState::Shooting) {
				setState(futureDirections.front());
				futureDirections.pop();
			}
		}


		Being::update(ptr);
	}

	
}