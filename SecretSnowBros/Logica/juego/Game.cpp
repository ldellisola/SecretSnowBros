#include "Game.h"



Game::Game(uint32_t Player1ID, uint32_t Player2ID)
	:Player1ID(Player1ID), Player2ID(Player2ID)

{
	srand(time(NULL));
}

Game::~Game()
{
	for (int i = (int)players.size() - 1; i >= 0; i--)
	{
		delete players[i];
	}

	for (int i = 0; i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}

	for (int i = 0; i < snowballs.size(); i++)
		delete snowballs[i];
}

void Game::selectNextMap()
{
	int i = 0;
	if (currentMap != nullptr)
		while (this->currentMap != &allMaps[i++]);

	this->currentMap = &allMaps[i];

	for (Monster * monst : this->getMonster())
		delete monst;
	this->Enemies.clear();


	for (Player * player : this->getPlayer()) {
		if (player->getID() == this->Player1ID) {
			player1lives = player->getLives();
			player1score = player->getScoreCounter()->getActualScore();
		}
		else if (player->getID() == this->Player2ID) {
			player2lives = player->getLives();
			player2score = player->getScoreCounter()->getActualScore();
		}
		delete player;
	}
	this->players.clear();

	for (SnowBall* snowBall : getSnowballs())
		delete snowBall;
	this->snowballs.clear();


	for (int fil = 0; fil < currentMap->fila; fil++) {
		for (int col = 0; col < currentMap->columna; col++) {

			switch (currentMap->map[fil][col])
			{
			case 'T': {this->createPlayer(Player1ID, col, fil);
				for (Player* plyr : this->getPlayer()) {
					if (plyr->getID() == this->Player1ID) {
						plyr->setLives(player1lives);
						plyr->getScoreCounter()->setScore(player1score);
					}
				}
			}		break;
			case 'N': {this->createPlayer(Player2ID, col, fil);
				for (Player* plyr : this->getPlayer()) {
					if (plyr->getID() == this->Player2ID) {
						plyr->setLives(player2lives);
						plyr->getScoreCounter()->setScore(player1score);
					}
				}
			}	break;
			case 'P':	this->createPurpleGuy(col, fil);			break;
			case 'G':	this->createGreenFatty(col, fil);			break;
			case 'C':	this->createCrazyGuy(col, fil);				break;
			default:												break;
			}

		}
	}

	currentMap->purge();

}

void Game::updateObservers(void * ptr)
{
	for (Observer * obs : observers)
		obs->draw(ptr);
}

int Game::dispatchEvent(GameEvent * ev)
{
	if (ev != nullptr)
		switch (ev->getEventType())
		{
			break;
		case GameEventType::Jump:
			for (Player * player : this->players)
				if (player->getID() == ev->getID()) {
					if (ev->isItStart())
						player->setState(BeingState::Jumping);
				}
			break;
		case GameEventType::Shoot:
			for (Player * player : this->players)
				if (player->getID() == ev->getID()) {
					if (ev->isItStart())
						player->setState(BeingState::Shooting);
				}
			break;
		case GameEventType::Left:
			for (Player * player : this->players)
				if (player->getID() == ev->getID()) {
					if (ev->isItStart()) {
						player->setState(BeingState::WalkingLeft);
					}
					else {
						player->setState(BeingState::StillWalk);
					}
				}
			break;
		case GameEventType::Right:
			for (Player * player : this->players)
				if (player->getID() == ev->getID()) {
					if (ev->isItStart()) {
						player->setState(BeingState::WalkingRight);
					}
					else {
						player->setState(BeingState::StillWalk);
					}
				}
			break;
		case GameEventType::Timer:

			// Actualizo la posicion de los malos
			for (Monster * monster : this->Enemies) {
				if (monster->isAlive()) {
					monster->chooseAction(getmap());
					monster->update(this->getmap());
					for (Player* player : players) {
						monster->collition(player);
						std::vector<Projectile*> tempProj = player->getProjectiles();
						for (Projectile* proj : tempProj) {
							monster->collition(proj);
							createSnowBall(monster, proj->getScore());
						}
					}

				}
			}

			// Actualizo la posicion de todos mis chabones
			for (Player * player : this->players) {
				if (player->isAlive())
					player->update(this->getmap());
				if (player->shouldRevive())
					player->revive();
				player->updateProjectiles(this->getmap());
				for (Monster* mstr : this->Enemies) {
					if (dynamic_cast<GreenFatty*>(mstr)) {
						for (Projectile * proj : ((GreenFatty*)mstr)->getProjectiles())
							player->collition(proj);
					}

				}
			}

			for (SnowBall * snowball : snowballs) {

				for (SnowBall * snow2 : snowballs) {
					snowball->collision(snow2);
				}

				for (Monster * monster : this->Enemies)
					snowball->collision(monster);
				for (Player * player : this->players) {
					player->MoveSnowBall(snowball, getmap());
					snowball->collision(player);
					auto projs = player->getProjectiles();

					for (Projectile * proj : projs) {
						snowball->collision(proj);
					}
				}
				snowball->update(getmap());

			}

			killSnowBalls();


			if (this->checkIfMonstersAlive())
			{
				return 	(int)KeepReturn::LevelWon;
				// Paso al proximo nivel
			}
			if (this->checkIfPlayersAlive())
			{
				return (int)KeepReturn::PlayersDead;// salgo del juego 
			}

			// Imprimo todo en en pantalla
			this->updateObservers(this);
			break;

		case GameEventType::Exit:
			return (int)KeepReturn::Exit;


		default:
			break;
		}

	return (int)KeepReturn::Start;
}

void Game::createPlayer(uint32_t id, uint32_t x, uint32_t y)
{
	auto temp = new Player(x, y, id);
	this->players.push_back(temp);
}

void Game::createPurpleGuy(uint32_t x, uint32_t y)
{
	auto temp = new PurpleGuy(x, y,(uint32_t) Enemies.size());
	this->Enemies.push_back(temp);
}

void Game::createGreenFatty(uint32_t x, uint32_t y)
{
	auto temp = new GreenFatty(x, y, (uint32_t)Enemies.size());
	this->Enemies.push_back(temp);

}

void Game::createCrazyGuy(uint32_t x, uint32_t y)
{
	auto temp = new CrazyGuy(x, y, (uint32_t)Enemies.size());
	this->Enemies.push_back(temp);

}

void Game::createSnowBall(Monster * monster, Score * playerScore)
{
	if (monster->isAlive() && monster->getFreezeState() == 4) {
		this->snowballs.push_back(new SnowBall(monster, playerScore));
		monster->kill();
	}
}

void Game::killSnowBalls()
{
	for (int i = (int)snowballs.size() - 1; i >= 0; i--)
	{
		if (snowballs[i]->shouldDie()) {
			for (Being * being : snowballs[i]->getHijackedPlayers()) {
				auto player = (Player*)being;
				player->setCarry(false);
				player->setInmune(true);
			}

			delete snowballs[i];
			snowballs.erase(snowballs.begin() + i);
		}
		else if (snowballs[i]->shouldMelt()) {
			snowballs[i]->melt();
			delete snowballs[i];
			snowballs.erase(snowballs.begin() + i);
		}
	}
}


std::vector <Player *>& Game::getPlayer() {

	return this->players;
}

std::vector <Monster   *>& Game::getMonster() {
	return this->Enemies;
}

std::vector<SnowBall*>& Game::getSnowballs()
{
	return snowballs;
}

void Game::loadMap(World map)
{
	this->allMaps.push_back(map);

}

void Game::loadMaps(std::vector<World> maps)
{
	for (World& map : maps)
		this->allMaps.push_back(map);

}

World*  Game::getmap() {
	currentMap->x.clear();
	currentMap->y.clear();
	for (Player* plyr : players) {
		currentMap->x.push_back(plyr->getX());
		currentMap->y.push_back(plyr->getY());
	}
	return (this->currentMap);
}



bool Game::checkIfPlayersAlive() {
	for (int i = 0; i < this->players.size(); i++) {
		if (this->players[i]->isAlive()) {

			return false;								//Me fijo si alguno tiene vida	
		}
	}

	return true;										//caso contrario estan muertos
}


bool Game::checkIfMonstersAlive() {
	for (int i = 0; i < this->Enemies.size(); i++) {
		if (this->Enemies[i]->isAlive() || this->snowballs.size()) {


			return false;								//Me fijo si alguno tiene vida
		}

	}

	return true; //caso contrario estan muertos
}
KeepReturn Game::run(void * ptr)
{
	int keep = (int)KeepReturn::Start;
	int mapCounter = 0;
	mapCounter = 9;
	bool alive = true;
	while (mapCounter != this->allMaps.size() && (keep != (int)KeepReturn::Exit) && (keep != (int)KeepReturn::PlayersDead)) {//ESA ES LA NEGRADA, HAYQ UE DEFINIR VALORES DE SALIDA DE KEEP, ESE 1 DE AHI SERIA QUE PERDISTE NO GANASTE
		this->selectNextMap();
		mapCounter++;
		keep = (int)KeepReturn::Start;
		do {
			this->eventH->getEvent();
			keep = this->dispatchEvent(eventH->returnEvent());
			this->eventH->killEvent();

		} while (keep == (int)KeepReturn::Start);
		//Aca si se quiere se puede poner una pantalla que muestre alguna transicion estilo nivel 2
	}
	currentMap = nullptr;
	return (KeepReturn)keep;

}

void Game::loadEventHandler(EventHandler * eventH)
{
	this->eventH = eventH;

}

void Game::loadObserver(Observer * obs)
{
	if (obs != nullptr) {
		this->observers.push_back(obs);

	}
}

void Game::loadPlayer(Player * player)
{
	this->players.push_back(player);

}

