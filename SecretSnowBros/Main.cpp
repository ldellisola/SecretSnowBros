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
//#undef ShittyComputer

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
	//window.setFullScreen();
	AllegroEventHandler eventHandler(allegro.getEventQueue());

	Game snowbros(Player1ID);
	EventHandler eventH;



	Local1PlayerController controller(allegro.getEventQueue(), Player1ID);
	eventH.loadController(&controller);

	snowbros.loadEventHandler(&eventH);

	StageObserver stageObserver((window.getHeight() - 400), window.getWidth(), 'F');
	snowbros.loadObserver(&stageObserver);


	PlayerDrawer  playerDrawer(window.getWidth() / 16, (window.getHeight() - 400) / 12);
	playerDrawer.loadPlayerSprite({"Images/PlayerSprite.png","Images/PlayerSprite2.png","Images/PlayerSprite3.png","Images/PlayerSprite4.png","Images/PlayerSprite5.png","Images/PlayerSprite6.png","Images/PlayerSprite7.png","Images/PlayerSprite8.png","Images/PlayerSprite9.png","Images/PlayerSprite10.png","Images/PlayerSprite11.png","Images/PlayerSprite12.png" });
	ProyectileDrawer projDrawer("Images/ProjectileSprite.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	PlayerInfoObserver playerInfo("font.ttf", window.getWidth(), 400, 12 * Block);
	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);

	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadCrazyGuySprite({ "Images/CrazyGuySprite.png" ,"Images/CrazyGuySprite2.png" , "Images/CrazyGuySprite3.png" , "Images/CrazyGuySprite4.png" ,"Images/CrazyGuySprite5.png" ,"Images/CrazyGuySprite6.png","Images/CrazyGuySprite7.png","Images/CrazyGuySprite8.png","Images/CrazyGuySprite9.png" });
	enemyDrawer.loadGreenFattySprite({ "Images/GreenFattySprite.png","Images/GreenFattySprite2.png","Images/GreenFattySprite3.png","Images/GreenFattySprite4.png","Images/GreenFattySprite5.png","Images/GreenFattySprite6.png","Images/GreenFattySprite7.png","Images/GreenFattySprite8.png","Images/GreenFattySprite9.png","Images/GreenFattySprite10.png","Images/GreenFattySprite11.png","Images/GreenFattySprite12.png" });
	enemyDrawer.loadPurpleGuySprite({ "Images/PurpleGuySprite.png","Images/PurpleGuySprite2.png","Images/PurpleGuySprite3.png","Images/PurpleGuySprite4.png","Images/PurpleGuySprite5.png","Images/PurpleGuySprite6.png","Images/PurpleGuySprite7.png","Images/PurpleGuySprite8.png","Images/PurpleGuySprite9.png" });
	enemyDrawer.loadFrozenSprites({ "Images/FrozenState1.png","Images/FrozenState2.png","Images/FrozenState3.png","Images/FrozenState4.png" });

	FireBallProjectile test("Images/ProjectileSprite2.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadObserver(test);

	snowbros.loadObserver(&enemyDrawer);

	FattyLogger fatlog;

	snowbros.loadObserver(&fatlog);

	SnowBallObserver snowBallObs("Images/FrozenState4.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);

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
