#include <AllwInit/Allw.h>
#include <AllwBasics/AllegroWindow.h>
#include <AllwBasics/AllegroEvent.h>

#include "MVC/AllegroController.h"
#include "MVC/StageObserver.h"
#include "MVC/PlayerDrawer.h"
#include "MVC/ProyectileDrawer.h"
#include "MVC/EnemyDrawer.h"
#include "MVC/WindowUpdater.h"
#include "MVC/FattyLogger.h"
#include "MVC/FireBallProjectile.h"
#include "MVC/SnowBallObserver.h"
#include "MVC/PlayerInfoObserver.h"

#include "Logica/Personajes/Being.h"

#include "Logica/juego/Game.h"

#define WindowTitle "SnowBros!"
#define WindowImage ""
std::vector<World> setUpMaps(std::string path, std::string ext);
#undef ShittyComputer

#ifdef ShittyComputer
	#define Block (50)
#else
	#define Block (100)
#endif

#define Player1ID (123)

int main(void) {
	Allw allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 50);

	AllegroWindow window(16 * Block, 12 * Block +400, allegro.getEventQueue(), WindowTitle, WindowImage);
	window.open();
	//	window.setFullScreen();
	AllegroEventHandler eventHandler(allegro.getEventQueue());


	Game snowbros(Player1ID);
	EventHandler eventH;



	Local1PlayerController controller(allegro.getEventQueue(), Player1ID);
	eventH.loadController(&controller);

	snowbros.loadEventHandler(&eventH);

	StageObserver stageObserver((window.getHeight() - 400), window.getWidth(), 'F');
	snowbros.loadObserver(&stageObserver);


	PlayerDrawer  playerDrawer("PlayerSprite.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	ProyectileDrawer projDrawer("ProjectileSprite.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	PlayerInfoObserver playerInfo("font.ttf", window.getWidth(), 400, 12 * Block);
	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);


	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadCrazyGuySprite("CrazyGuySprite.png");
	enemyDrawer.loadGreenFattySprite("GreenFattySprite.png");
	enemyDrawer.loadPurpleGuySprite("PurpleGuySprite.png");
	enemyDrawer.loadFrozenSprites({ "FrozenState1.png","FrozenState2.png","FrozenState3.png","FrozenState4.png" });

	FireBallProjectile test("ProjectileSprite.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadObserver(test);

	snowbros.loadObserver(&enemyDrawer);

	FattyLogger fatlog;

	snowbros.loadObserver(&fatlog);

	SnowBallObserver snowBallObs("FrozenState4.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);

	snowbros.loadObserver(&snowBallObs);

	WindowUpdater win(window);
	snowbros.loadObserver(&win);
	
	snowbros.loadMaps(setUpMaps("map",".csv"));
	snowbros.run(nullptr);

	return 0;
}


std::vector<World> setUpMaps(std::string path, std::string ext)
{
	std::vector<std::string> names(10, " ");
	std::vector<World> maps;
	for (int i = 0; i < 10; i++) {
		names[i] = path + std::to_string(i + 1) + ext;
		World map(names[i]);
		maps.push_back(map);
	}
	return maps;
}
