#include "SnowBall.h"

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*4)	// 200ms
#define FallTicks (ms50*6)	// 300ms

SnowBall::SnowBall(Monster * monster, Score * PlayerScore)
	:Slider(monster->getX(), WalkTicks),Jumper(monster->getY(), JumpTicks, FallTicks)
{

	
	this->setHorizontalDir(HorizontalDirection::Left);
	setState(SnowBallState::Still);
	this->capturedMonster = monster;
	this->playerScore = PlayerScore;
	this->enemyHits = 0;
	this->wallHits = 0;
}

bool SnowBall::collision(Being * being)
{

	if (this->getX() == being->getX() && this->getY() == being->getY()  ) {
		if (being->isAlive() && state == SnowBallState::Rolling) {

			if (dynamic_cast<Monster*>(being)) {
				this->enemyHits++;
				being->kill();
				for (int i = 1; i <= enemyHits; i++) {
					*playerScore += i * 1000;
				}
			}
			else if (dynamic_cast<Player *>(being)) {
				auto player = ((Player*)being);

				if (!player->isCarried() && !player->isInmune()) {
					hijackedPlayers.push_back((Player*)being);
					player->setCarry(true);
				}
			}
			return true;
		}
	}

	return false;
}

bool SnowBall::collision(Projectile * proj) {

	if (proj->getX() == this->getX() && proj->getY() == this->getY()) {
		if (proj->getDistanceFromStart() == 0) {
			this->setState(SnowBallState::Rolling);
			this->setHorizontalDir(proj->getHorizontalDir());
			proj->kill();
			return true;
		}
	}
	return false;

}

void SnowBall::update(void * ptr)
{

	World& world = *(World *) ptr;

	switch (getHorizontalDir())
	{
	case HorizontalDirection::Left:

		if (world.map[getY()][getX() - 1] == 'F') {
			wallHits++;
			this->setHorizontalDir(HorizontalDirection::Right);
			if (getY() == 10) {
				wallHits = 123;
			}
		}

		break;
	case HorizontalDirection::Right:
		if (world.map[getY()][getX() + 1] == 'F') {
			wallHits++;
			this->setHorizontalDir(HorizontalDirection::Left);
			if (getY() == 10) {
				wallHits = 123;
			}
		}
		break;

	}


	std::unique_ptr<char> column(new char[world.fila]);

	for (int i = 0; i < world.fila; i++) {
		column.get()[i] = world.map[i][getX()];
	}

	Jumper::update(column.get());

	std::unique_ptr<char> row(new char[world.columna]);

	for (int i = 0; i < world.columna; i++) {
		row.get()[i] = world.map[getY()][i];
	}

	Slider::update(row.get());

	for (Player* plyr : hijackedPlayers) {
		if (plyr->getState() == BeingState::Jumping) {
			releasePlayer(plyr);
			plyr->setCarry(false);
			plyr->setInmune(true);
		}
		else {
			plyr->setX(getX());
			plyr->setY(getY());
		}
	}
}


void SnowBall::setState(SnowBallState state) {

	switch (state)
	{
	case SnowBallState::Carried:
		break;
	case SnowBallState::Rolling:
		this->setHorizontalState(HorizontalState::Moving);
		break;
	case SnowBallState::Still:
		this->setHorizontalState(HorizontalState::Still);
		break;
	default:
		break;
	}
	this->state = state;



}

void SnowBall::releasePlayer(Player * player)
{
	for (int i = (int)hijackedPlayers.size() - 1; i >= 0; i--)
	{
		if(hijackedPlayers[i] == player)
			hijackedPlayers.erase(hijackedPlayers.begin() + i);
	}
}

bool SnowBall::shouldDie()
{
	if (wallHits >= maxHits)
		return true;
	else 
		return false;
}

SnowBall::~SnowBall ()
{
}
