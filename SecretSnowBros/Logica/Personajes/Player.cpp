#include "Player.h"


#define ms50 (3)

#define WalkTicks (ms50*6)	// 300ms
#define JumpTicks (ms50* 24)	// 1200ms
#define ShootTicks (ms50*3)		// 900ms
#define FallTicks (ms50*6)
#define StillTicks (ms50*10)	// 500ms

Player::Player(uint16_t x, uint16_t y, uint16_t ID)
	:points(ID), 
	Being(JumpTicks,WalkTicks,FallTicks,x,y,ID),
	Shooter(ShootTicks)

#ifdef _DEBUG
	,Logger("Logs/Player ID -" + std::to_string(ID),true)
#endif // _DEBUG
{
	this->lives = 3;

}

Player::~Player()
{
}

void Player::update(void * ptr)
{
	if (!isCarried() && isAlive() && !isWaitingToRevive()) {
		Being::update(ptr);
#ifdef _DEBUG
		if (getVerticalState() == VerticalState::Jumping)
			if (getVerticalTicks() == MaxJumpingTicks / 2)
				log("Jumped halfway at [" + std::to_string(getX()) + "," + std::to_string(getY()) + "], to " + "[" + std::to_string(getX()) + ", " + std::to_string(getY() - 1) + "]");
			else if (getVerticalState() == VerticalState::Falling)
				if (getVerticalTicks() == 0)
					log("Falling at [" + std::to_string(getX()) + "," + std::to_string(getY()) + "]");

		if (getHorizontalState() == HorizontalState::Moving)
			if (getHorizontalTicks() == 0)
				log("Walked from [" + std::to_string(getX()) + "," + std::to_string(getY()) + "]");


#endif // _DEBUG


		if (isInmune() && !isWaitingToRevive()) {
			updateInmuneTick();

			if (getInmuneTick() == MaxInmuneTick) {
				resetInmuneTick();
				setInmune(false);
			}
		}


		World& map = *(World*)ptr;



		if (!isCoolingDown() && isShooting()) {
#ifdef _DEBUG
			log("Current score is:" + std::to_string(this->getScoreCounter()->getActualScore()));
			log("Shoot at [" + std::to_string(getX()) + "," + std::to_string(getY()) + "]");
#endif // _DEBUG

			if (this->getHorizontalDir() == HorizontalDirection::Right && this->getX() + 1 < map.columna)
				this->shoot(this->getX() + 1, this->getY(), HorizontalDirection::Right, this->getScoreCounter());
			else if (this->getHorizontalDir() == HorizontalDirection::Left && getX() - 1 >= 0)
				this->shoot(this->getX() - 1, this->getY(), HorizontalDirection::Left, this->getScoreCounter());
			stopShooting();
			startCoolDown();
		}
		else if (isCoolingDown()) {
			updateShootingTicks();
			if (getShootingTicks() == 0) {
				stopCoolDown();
			}

		}
	}
	else if (isWaitingToRevive()) {
		updateReviveTick();
	}

}




void Player::collition(Projectile * proy)
{
	if (proy->getX() == this->getX() && proy->getY() == this->getY() && !this->isInmune() && this->isAlive()) {
		this->kill();
#ifdef _DEBUG
		log("Collision with projectile");
#endif // _DEBUG
	}
}

void Player::setState(BeingState state)
{
	if (isAlive()) {
		if (state == BeingState::Shooting && !this->isCarried()) {
			if (!isCoolingDown()) {
				resetShootingTicks();
				this->startShooting();
			}

		}

		if (state == BeingState::Inmune) {
			setInmune(true);
		}
		else
			Being::setState(state);
	}
											


}

void Player::updateScore(uint16_t value)
{
	this->points += value;
}

void Player::MoveSnowBall(SnowBall * snowball, World * map)
{
	if (snowball->getY() == this->getY() && snowball->getState() == SnowBallState::Still) {
		if (Being::beingState == BeingState::WalkingLeft) {
			if (snowball->getX() == this->getX() && (map->map[getY()][getX() - 1] != 'F')) {
				snowball->setX(getX() - 1);
			}
		}
		else if (Being::beingState == BeingState::WalkingRight ) {
			if (snowball->getX() == this->getX() && (map->map[getY()][getX() + 1] != 'F')) {
				snowball->setX(getX() + 1);
			}
		}
		else if (Being::beingState == BeingState::Jumping && (getY()!=0)) {
			if (snowball->getX() == this->getX() && (map->map[getY() - 1][getX()] != 'F')) {
				snowball->setY(getY() - 1);
			}
		}
	}

}

void Player::kill()
{

	if (!isInmune()) {

#ifdef _DEBUG
		log("Player Killed at [" + std::to_string(getX()) + ", " + std::to_string(getY()) + "]");
#endif
		Being::kill();



		if (isAlive()) {
			this->startWaitingToRevive();
		}
	}




#ifdef _DEBUG
	if (lives > 0) {
		log("Player spawned at [" + std::to_string(getX()) + ", " + std::to_string(getY()) + "]");
	}
#endif
}

bool Player::shouldRevive()
{
	if (this->MaxReviveTick == getReviveTick()) {
		return true;
	}
	else {
		return false;
	}
}

void Player::revive()
{
	Jumper::setY(yStart);
	Slider::setX(xStart);
	Jumper::setVerticalState(VerticalState::Still);
	Slider::setHorizontalState(HorizontalState::Still);
	resetHorizontalTicks();
	resetVerticalTicks();
	setInmune(true);
	stopWaitingToRevive();
	resetReviveTick();

	resetInmuneTick();
}

void Player::setInmune(bool set)
{
	inmune = set;

#ifdef _DEBUG
	if (inmune) {
		log("Player is now inmune");
	}
	else
		log("Player stopped being inmune");
#endif
}

void Player::updateInmuneTick()
{
	this->inmuneTick++;
}

void Player::resetInmuneTick()
{
	inmuneTick = 0;
}

uint16_t Player::getInmuneTick()
{
	return inmuneTick;
}

void Player::setCarry(bool set)
{
	this->carried = set;
	if (carried) {
		this->setState(BeingState::StillJump);
		this->setState(BeingState::StillWalk);
	}
}

bool Player::isWaitingToRevive()
{
	return waitingToRevive;
}

void Player::startWaitingToRevive()
{
	this->setInmune(true);
	resetReviveTick();
	waitingToRevive = true;
#ifdef _DEBUG
		log("Player is waiting to revive");

#endif
}

void Player::stopWaitingToRevive()
{
	resetReviveTick();
	waitingToRevive = false;
#ifdef _DEBUG
	log("Player is will revive now");

#endif
}

void Player::updateReviveTick()
{
	this->reviveTick++;
}

void Player::resetReviveTick()
{
	reviveTick = 0;
}

uint16_t Player::getReviveTick()
{
	return reviveTick;
}

