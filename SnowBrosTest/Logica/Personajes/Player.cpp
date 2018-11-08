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
	
	Being::update(ptr);
#ifdef _DEBUG
	if(getVerticalState() == BeingState::Jumping)
		if(getVerticalTicks() == maxJumpTick/2)
			log("Jumped halfway at [" + std::to_string(x) + "," + std::to_string(y) + "], to "+ "[" + std::to_string(x) + ", " + std::to_string(y-1) + "]");
	else if(getVerticalState() == BeingState::Falling)
		if (getVerticalTicks() == 0) 
			log("Falling at [" + std::to_string(x) + "," + std::to_string(y) + "]");
	
	if(getHorizontalState() == BeingState::Walking)
		if(getHorizontalTicks() == 0)
			log("Walked from [" + std::to_string(x) + "," + std::to_string(y) + "] in direction: " + _BeingDir[(int)getDirection()]);


#endif // _DEBUG





	World& map = *(World*)ptr;



	if (!isCoolingDown() && isShooting()) {
#ifdef _DEBUG
		log("Current score is:" + std::to_string(this->getScoreCounter()->getActualScore()));
		log("Shoot at [" + std::to_string(x) + "," + std::to_string(y) + "] in direction: " + _BeingDir[(int)this->getDirection()]);
#endif // _DEBUG

		if (this->getDirection() == BeingDirection::Right && this->x + 1 < map.columna)
			this->shoot(this->x + 1, this->y, ProjectileDirection::Right, this->getScoreCounter());
		else if (this->getDirection() == BeingDirection::Left && x - 1 >= 0)
			this->shoot(this->x - 1, this->y, ProjectileDirection::Left, this->getScoreCounter());
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
	if (proy->getX() == this->x && proy->getY() == this->y) {
		this->kill();
#ifdef _DEBUG
		log("Collision with projectile");
#endif // _DEBUG
	}
}

void Player::setState(BeingState state)
{
	Being::setState(state);						// Para no meter cosas que no van en Being, sobrecargo la funcion en player y le agrego la habilidad
												// de disparar. Idealmente esto iria en shooter, pero shooter no tiene acceso a being

	if(state == BeingState::Shooting ){
		if (!isCoolingDown()) {
			resetShootingTicks();
			this->startShooting();
		}
		
	}
}

