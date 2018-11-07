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
	,Logger("Logs/Player-" + std::to_string(ID),true)
#endif // _DEBUG
{
	this->lives = 3;
}

Player::~Player()
{
}

void Player::update(void * ptr)
{
	World& map = *(World *)ptr;

	if (getVerticalState() != BeingState::StillJump)
		updateVerticalTicks();
	if (getHorizontalState() != BeingState::StillWalk)
		updateHorizontalTicks();



	switch (getVerticalState())
	{

	case BeingState::StillJump:
		if (y + 1 < map.fila && (map.map[y + 1][x] == 'E' || map.map[y][x] == 'F')) {
			this->setState(BeingState::Falling);
			resetVerticalTicks();
		}
		break;
	case BeingState::Jumping:
		if (getVerticalTicks() == maxJumpTick / 2) {
			if ((this->y - 1) >= 0) {
				y--;
#ifdef _DEBUG
				log("Jumped halfway at [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif // _DEBUG
			}
		}
		else if (getVerticalTicks() == maxJumpTick - 1) {
			if ((this->y - 1) >= 0) {
				y--;
#ifdef _DEBUG
				log("Jump complete at [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif // _DEBUG
			}

			this->setState(BeingState::StillJump);
			resetVerticalTicks();
		}
		break;
	case BeingState::Falling:
		if (getVerticalTicks() == maxFallTicks - 1) {
			y++;
#ifdef _DEBUG
			log("Falling at [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif // _DEBUG
			if (y + 1 < map.fila && map.map[y + 1][x] == 'F') {
				this->setState(BeingState::StillJump);
			}

			this->resetVerticalTicks();
		}
		break;

	}

	switch (getHorizontalState())
	{
	case BeingState::StillWalk:
		break;
	case BeingState::Walking:
		if (this->getHorizontalTicks() == this->maxWalkTick - 1) {

#ifdef _DEBUG
			log("Walked from [" + std::to_string(x) + "," + std::to_string(y) + "] in direction: " + _BeingDir[(int)getDirection()]);
#endif // _DEBUG

			if ((y + 1 < map.fila && map.map[y + 1][x] == 'E') && getVerticalState() == BeingState::StillJump) {

#ifdef _DEBUG
				log("State switched to Falling");
#endif // _DEBUG

				setState(BeingState::Falling);
			}
			if (this->getDirection() == BeingDirection::Left && x - 1 >= 0 && map.map[y][x - 1] != 'F')
				this->x--;
			else if (this->getDirection() == BeingDirection::Right && x + 1 < map.columna && map.map[y][x + 1] != 'F')
				this->x++;
			this->resetHorizontalTicks();

		}
		break;
	}

	if (!isCoolingDown() && isShooting()) {
#ifdef _DEBUG
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

