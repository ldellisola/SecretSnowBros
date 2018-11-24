#include "Game.h"



Game::Game(uint32_t Player1ID, uint32_t Player2ID)
	:Player1ID(Player1ID), Player2ID(Player2ID)
#if _DEBUG
	, Logger("Logs/Game Model", true)
#endif
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

#if _DEBUG
	log("Loaded map number " + std::to_string(i));
#endif


	for (int fil = 0; fil < currentMap->fila; fil++) {
		for (int col = 0; col < currentMap->columna; col++) {

			switch (currentMap->map[fil][col])
			{
			case 'T':	this->createPlayer(Player1ID, col, fil);		break;
			case 'N':	this->createPlayer(Player2ID, col, fil);	break;
			case 'P':	this->createPurpleGuy(col, fil);			break;
			case 'G':	this->createGreenFatty(col, fil);			break;
			case 'C':	this->createCrazyGuy(col, fil);				break;
			default:												break;
			}

		}
	}

	currentMap->purge();
	Enemies[0]->kill();
	createSnowBall(Enemies[0], players[0]->getScoreCounter());
	


#if _DEBUG
	log("Purged map number " + std::to_string(i));
#endif
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
			for (Monster  * monster : this->Enemies) {
				if (monster->isAlive()) {
					monster->chooseAction(getmap());
					monster->update(this->getmap());
					for (Player* player : players) {
						monster->collition(player);
						std::vector<Projectile*> tempProj = player->getProjectiles();
						for (Projectile* proj : tempProj)
							monster->collition(proj);
					}
				}
			}

			// Actualizo la posicion de todos mis chabones
			for (Player * player : this->players) {
				if(player->isAlive())
					player->update(this->getmap());
				player->updateProjectiles(this->getmap());
				for (Monster* mstr : this->Enemies) {
					if (dynamic_cast<GreenFatty*>(mstr)) {
						for (Projectile * proj : ((GreenFatty*)mstr)->getProjectiles())
							player->collition(proj);
					}

				}
			}

			for (SnowBall * snowball : snowballs) {

				for (Monster * monster : this->Enemies)
					snowball->collision(monster);
				for (Player * player : this->players)
					snowball->collision(player);
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
				return (int)KeepReturn::PlayersDead;// salgo del juego //negrada
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

#if _DEBUG
	log("Created Player Id: " + std::to_string(id) + ", at location [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif
}

void Game::createPurpleGuy(uint32_t x, uint32_t y)
{
	auto temp = new PurpleGuy(x, y, Enemies.size());
	this->Enemies.push_back(temp);

#if _DEBUG
	log("Created PurpleGuy at location [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif
}

void Game::createGreenFatty(uint32_t x, uint32_t y)
{
	auto temp = new GreenFatty(x, y, Enemies.size());
	this->Enemies.push_back(temp);

#if _DEBUG
	log("Created GreenFatty at location [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif
}

void Game::createCrazyGuy(uint32_t x, uint32_t y)
{
	auto temp = new CrazyGuy(x, y, Enemies.size());
	this->Enemies.push_back(temp);

#if _DEBUG
	log("Created CrazyGuy at location [" + std::to_string(x) + "," + std::to_string(y) + "]");
#endif
}

void Game::createSnowBall(Monster * monster, Score * playerScore)
{
	this->snowballs.push_back(new SnowBall(monster, playerScore));
}

void Game::killSnowBalls()
{
	for (int i = (int)snowballs.size() - 1; i >= 0; i--)
	{
		if (snowballs[i]->shouldDie()) {
			delete snowballs[i];
			snowballs.erase(snowballs.begin()+i);
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

#if _DEBUG
	log("Loaded 1 map");
#endif
}

void Game::loadMaps(std::vector<World> maps)
{
	for (World& map : maps)
		this->allMaps.push_back(map);

#if _DEBUG
	log("Loaded " + std::to_string(maps.size()) + " maps");
#endif
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
#if _DEBUG
			log("At least one player is alive");
#endif
			return false;								//Me fijo si alguno tiene vida	
		}
	}

#if _DEBUG
	log("All players are dead");
#endif
	return true;										//caso contrario estan muertos
}


bool Game::checkIfMonstersAlive() {
	for (int i = 0; i < this->Enemies.size(); i++) {
		if (this->Enemies[i]->isAlive()) {
#if _DEBUG
			log("At least one enemy is alive");
#endif
			return false;								//Me fijo si alguno tiene vida
		}
	}

#if _DEBUG
	log("All enemies are dead");
#endif

	return true; //caso contrario estan muertos
}
int Game::run(void * ptr)
{
	int keep = (int)KeepReturn::Start;
	int mapCounter = 0;
	bool alive = true;
	while (mapCounter  !=this->allMaps.size() && (keep!= (int)KeepReturn::Exit) ) {//ESA ES LA NEGRADA, HAYQ UE DEFINIR VALORES DE SALIDA DE KEEP, ESE 1 DE AHI SERIA QUE PERDISTE NO GANASTE
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
	return 0;


}

void Game::loadEventHandler(EventHandler * eventH)
{
	this->eventH = eventH;

#if _DEBUG
	log("Loaded event handler");
#endif
}

void Game::loadObserver(Observer * obs)
{
	if (obs != nullptr) {
		this->observers.push_back(obs);
#if _DEBUG
		log("Loaded observer");
#endif
	}
}

void Game::loadPlayer(Player * player)
{
	this->players.push_back(player);
#if _DEBUG
	log("Loaded player");
#endif
}

