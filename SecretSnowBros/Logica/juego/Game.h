#pragma once
#include <vector>

#include "MVC/Controllers/Controller.h"
#include "Logica/Personajes/Monster.h"
#include "Logica/Personajes/Player.h"
#include "MVC/Controllers/EventHandler.h"
#include "Logica/Personajes/PurpleGuy.h"
#include "Logica/Personajes/GreenFatty.h"
#include "Logica/Personajes/CrazyGuy.h"
#include "Logica/Personajes/SnowBall.h"
#include "MVC/Controllers/Event.h"
#include "MVC/Observers/Observer.h"
#include "Logica/juego/Cmap.h"


enum class KeepReturn { Start, Exit,PlayersDead,LevelWon };
class Game


{
public:
	Game(uint32_t Player1ID, uint32_t Player2ID = 0);

	bool checkIfPlayersAlive();
	bool checkIfMonstersAlive();
	KeepReturn run(void * ptr);
	void loadEventHandler(EventHandler* eventH);
	void loadObserver(Observer * obs);
	void loadPlayer(Player * player);
	std::vector <Player *>&  getPlayer();
	std::vector <Monster *>&  getMonster();
	std::vector <SnowBall *>&  getSnowballs();
	void loadMap(World map);
	void loadMaps(std::vector<World>maps);
	World * getmap();
	~Game();
private:

	const uint32_t Player1ID, Player2ID;

	void selectNextMap();

	void updateObservers(void * ptr);
	int dispatchEvent(GameEvent *ev);
	std::vector <Player *> players;
	std::vector <Monster   *> Enemies;
	std::vector<SnowBall*> snowballs;
	World *currentMap;
	std::vector<World> allMaps;
	EventHandler * eventH = nullptr;

	std::vector<Observer *> observers;

	void createPlayer(uint32_t id, uint32_t x, uint32_t y);

	void createPurpleGuy(uint32_t x, uint32_t y);

	void createGreenFatty(uint32_t x, uint32_t y);

	void createCrazyGuy(uint32_t x, uint32_t y);

	void createSnowBall(Monster* monster, Score * playerScore);

	void killSnowBalls();

	uint32_t player1lives = 3, player2lives = 3, player1score = 0, player2score = 0;



};