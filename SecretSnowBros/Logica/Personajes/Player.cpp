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
	//this->lives = 1000;//DEBUG
}

Player::~Player()
{
}

void Player::update(void * ptr)
{
	Being::update(ptr);
#ifdef _DEBUG
	if(getVerticalState() == VerticalState::Jumping)
		if(getVerticalTicks() == MaxJumpingTicks/2)
			log("Jumped halfway at [" + std::to_string(getX()) + "," + std::to_string(getY()) + "], to "+ "[" + std::to_string(getX()) + ", " + std::to_string(getY() -1) + "]");
	else if(getVerticalState() == VerticalState::Falling)
		if (getVerticalTicks() == 0) 
			log("Falling at [" + std::to_string(getX()) + "," + std::to_string(getY()) + "]");
	
	if(getHorizontalState() == HorizontalState::Moving)
		if(getHorizontalTicks() == 0)
			log("Walked from [" + std::to_string(getX()) + "," + std::to_string(getY()) + "]");


#endif // _DEBUG


	if (isInmune()) {
		updateInmuneTick();

		if (getInmuneTick() == MaxInmuneTick) {
			resetInmuneTick();
			inmune = false;
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








void Player::collition(Projectile * proy)
{
	if (proy->getX() == this->getX() && proy->getY() == this->getY()) {
		this->kill();
#ifdef _DEBUG
		log("Collision with projectile");
#endif // _DEBUG
	}
}

void Player::setState(BeingState state)
{
	if (state == BeingState::Inmune) {
		this->inmune = true;
	}
	else
		Being::setState(state);						
											

	if(state == BeingState::Shooting ){
		if (!isCoolingDown()) {
			resetShootingTicks();
			this->startShooting();
		}
		
	}
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

