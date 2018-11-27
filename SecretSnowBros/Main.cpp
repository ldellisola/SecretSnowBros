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
std::vector<std::string> getNames(std::string path, std::string ext, int quantinty);
std::vector<World> stringtoworld(std::vector<std::string> files);
//#undef ShittyComputer

#ifdef ShittyComputer
	#define Block (100)
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

	std::vector<std::string> a = getNames("Images/Player/Normal/PS", ".png", 12);
	std::vector<std::string> b = getNames("Images/Player/Golden/PS", ".png", 12);
	a.insert(std::end(a), std::begin(b), std::end(b));
	playerDrawer.loadPlayerSprite(a);


	ProyectileDrawer projDrawer("Images/Projectiles/IceProj.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	PlayerInfoObserver playerInfo("font.ttf", window.getWidth(), 400, 12 * Block);
	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);

	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadCrazyGuySprite(getNames("Images/CrazyGuy/CGS", ".png", 9) );
	enemyDrawer.loadGreenFattySprite(getNames("Images/GreenFatty/GFS", ".png", 12));
	enemyDrawer.loadPurpleGuySprite(getNames("Images/PurpleGuy/PGS", ".png", 9));
	enemyDrawer.loadFrozenSprites(getNames("Images/Frozen/FSS", ".png", 4));

	FireBallProjectile test("Images/Projectiles/FireProj.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);
	enemyDrawer.loadObserver(test);

	snowbros.loadObserver(&enemyDrawer);

	FattyLogger fatlog;

	snowbros.loadObserver(&fatlog);

	SnowBallObserver snowBallObs("Images/Frozen/FSS4.png", window.getWidth() / 16, (window.getHeight() - 400) / 12);

	snowbros.loadObserver(&snowBallObs);

	WindowUpdater win(window);
	snowbros.loadObserver(&win);
	
	snowbros.loadMaps(stringtoworld(getNames("map",".csv",10)));
	snowbros.run(nullptr);

	return 0;
}


std::vector<std::string> getNames(std::string path, std::string ext ,int quantinty)
{
	std::vector<std::string> names(quantinty, " ");
	std::vector<World> maps;
	for (int i = 0; i < quantinty; i++) {
		names[i] = path + std::to_string(i + 1) + ext;

	}
	return names;
}

std::vector<World> stringtoworld(std::vector<std::string> files) {
	std::vector<World> maps;
	for (int i = 0; i < 10; i++) {
		World map(files[i]);
		maps.push_back(map);
	}
	return maps;
}