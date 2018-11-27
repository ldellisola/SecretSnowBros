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
	playerDrawer.loadPlayerSprite({"Images/Player/Normal/PS1.png","Images/Player/Normal/PS2.png","Images/Player/Normal/PS3.png","Images/Player/Normal/PS4.png","Images/Player/Normal/PS5.png","Images/Player/Normal/PS6.png","Images/Player/Normal/PS7.png","Images/Player/Normal/PS8.png","Images/Player/Normal/PS9.png","Images/Player/Normal/PS10.png","Images/Player/Normal/PS11.png","Images/Player/Normal/PS12.png", "Images/Player/Golden/PS1.png","Images/Player/Golden/PS2.png","Images/Player/Golden/PS3.png","Images/Player/Golden/PS4.png","Images/Player/Golden/PS5.png","Images/Player/Golden/PS6.png","Images/Player/Golden/PS7.png","Images/Player/Golden/PS8.png","Images/Player/Golden/PS9.png","Images/Player/Golden/PS10.png","Images/Player/Golden/PS11.png","Images/Player/Golden/PS12.png" });
	ProyectileDrawer projDrawer("Images/Projectiles/IceProj.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	PlayerInfoObserver playerInfo("font.ttf", window.getWidth(), 400, 12 * Block);
	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);

	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadCrazyGuySprite({ "Images/CrazyGuy/CGS1.png" ,"Images/CrazyGuy/CGS2.png" ,"Images/CrazyGuy/CGS3.png" ,"Images/CrazyGuy/CGS4.png" ,"Images/CrazyGuy/CGS5.png" ,"Images/CrazyGuy/CGS6.png" ,"Images/CrazyGuy/CGS7.png" ,"Images/CrazyGuy/CGS8.png" ,"Images/CrazyGuy/CGS9.png" });
	enemyDrawer.loadGreenFattySprite({ "Images/GreenFatty/GFS1.png","Images/GreenFatty/GFS2.png","Images/GreenFatty/GFS3.png","Images/GreenFatty/GFS4.png","Images/GreenFatty/GFS5.png","Images/GreenFatty/GFS6.png","Images/GreenFatty/GFS7.png","Images/GreenFatty/GFS8.png","Images/GreenFatty/GFS9.png","Images/GreenFatty/GFS10.png","Images/GreenFatty/GFS11.png","Images/GreenFatty/GFS12.png", });
	enemyDrawer.loadPurpleGuySprite({ "Images/PurpleGuy/PGS1.png","Images/PurpleGuy/PGS2.png","Images/PurpleGuy/PGS3.png","Images/PurpleGuy/PGS4.png","Images/PurpleGuy/PGS5.png","Images/PurpleGuy/PGS6.png","Images/PurpleGuy/PGS7.png","Images/PurpleGuy/PGS8.png","Images/PurpleGuy/PGS9.png", });
	enemyDrawer.loadFrozenSprites({ "Images/Frozen/FSS1.png","Images/Frozen/FSS2.png","Images/Frozen/FSS3.png","Images/Frozen/FSS4.png"});

	FireBallProjectile test("Images/Projectiles/FireProj.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadObserver(test);

	snowbros.loadObserver(&enemyDrawer);

	FattyLogger fatlog;

	snowbros.loadObserver(&fatlog);

	SnowBallObserver snowBallObs("Images/Frozen/FSS4.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);

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
