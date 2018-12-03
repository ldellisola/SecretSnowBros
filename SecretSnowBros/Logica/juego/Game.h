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

	// It returns true if any player is alive
	bool checkIfPlayersAlive();

	// It returns true if any monster is alive
	bool checkIfMonstersAlive();

	// This is the main loop of the game, it runs the whole event system and calls all the observers
	KeepReturn run(void * ptr);

	// It loads a foreign event Handler. If there was already an event handler loaded it will override it
	void loadEventHandler(EventHandler* eventH);

	// It loads an observer to be called once every tick
	void loadObserver(Observer * obs);

	// It returns a reference to a vector with all the players in the map
	std::vector <Player *>&  getPlayer();

	// It returns a reference to all the monsters in the map
	std::vector <Monster *>&  getMonster();

	// It returns a reference to all the snowballs in the map at the moment
	std::vector <SnowBall *>&  getSnowballs();

	// It loads a single map to the game
	void loadMap(World map);

	// It loads any given ammount of maps to the game
	void loadMaps(std::vector<World>maps);

	// It returns a pointer to the current map
	World * getmap();

	// Destructor
	~Game();

private:

	// Updates all the monsters in a tick
	void updateMonsters();

	// Updates all the snowballs in a tick
	void updateSnowBalls();

	//Updates all the Players in a tick
	void updatePlayers();

	// It loads the next map to the game, creates all the entities and purges the map
	void selectNextMap();

	// It calls all the observers and updates them
	void updateObservers(void * ptr);

	// It dispaches a given event
	int dispatchEvent(GameEvent *ev);

	// It creates a player in a given position with a given ID
	void createPlayer(uint32_t id, uint32_t x, uint32_t y);

	// It creates a Purple Guy in a given position 
	void createPurpleGuy(uint32_t x, uint32_t y);

	// It creates a GreenFatty in a given position
	void createGreenFatty(uint32_t x, uint32_t y);

	// It creates a Crazy Guy in a given position
	void createCrazyGuy(uint32_t x, uint32_t y);

	// It creates a Snowball in the position of the monster that got frozen
	void createSnowBall(Monster* monster, Score * playerScore);

	// It checks all the snowballs to see if they should die and if the should, it kills them
	void killSnowBalls();


	std::vector <Player *> players;
	std::vector <Monster   *> Enemies;
	std::vector<SnowBall*> snowballs;
	World *currentMap;
	std::vector<World> allMaps;
	EventHandler * eventH = nullptr;
	const uint32_t Player1ID, Player2ID;

	std::vector<Observer *> observers;


	uint32_t player1lives = 3, player2lives = 3, player1score = 0, player2score = 0;



};