#pragma once
#include <vector>
#if _DEBUG
#include "../../Logger.h"
#endif
#include "../../MVC/Controller.h"
#include "../Personajes/Monster.h"
#include "../Personajes/Player.h"
#include "../../MVC/EventHandler.h"
#include "../Personajes/PurpleGuy.h"
#include "../Personajes/GreenFatty.h"
#include "../Personajes/CrazyGuy.h"
#include "../../MVC/Event.h"
#include "../../MVC/Observer.h"
#include "Cmap.h"



class Game
#ifdef _DEBUG
	: protected Logger
#endif // _DEBUG

{
public:
	Game(uint32_t Player1ID, uint32_t Player2ID = 0);

	bool checkIfPlayersAlive();
	bool checkIfMonstersAlive();
	int run(void * ptr);
	void loadEventHandler(EventHandler* eventH);
	void loadObserver(Observer * obs);
	void loadPlayer(Player * player);
	std::vector <Player *>&  getPlayer();
	std::vector <Monster *>&  getMonster();
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
	World *currentMap;
	std::vector<World> allMaps;
	EventHandler * eventH = nullptr;

	std::vector<Observer *> observers;

	void createPlayer(uint32_t id, uint32_t x, uint32_t y);

	void createPurpleGuy(uint32_t x, uint32_t y);

	void createGreenFatty(uint32_t x, uint32_t y);

	void createCrazyGuy(uint32_t x, uint32_t y);






	const uint8_t Tabla[16][16] = {
		98, 6, 85,150, 36, 23,112,164,135,207,169, 5, 26, 64,165,219, // 1
		61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, // 2
		90,168,156,203,177,120, 2,190,188, 7,100,185,174,243,162, 10, // 3
		237, 18,253,225, 8,208,172,244,255,126,101, 79,145,235,228,121, // 4
		123,251, 67,250,161, 0,107, 97,241,111,181, 82,249, 33, 69, 55, // 5
		59,153, 29, 9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, // 6
		197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, // 7
		39,158,178,187,131,136, 1, 49, 50, 17,141, 91, 47,129, 60, 99, // 8
		154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, // 9
		133,232,196,144,198,124, 53, 4,108, 74,223,234,134,230,157,139, // 10
		189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
		183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
		221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
		3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
		238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
		43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239 // 16
	};

};