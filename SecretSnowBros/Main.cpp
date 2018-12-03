#include <AllwInit/Allw.h>
#include <AllwBasics/AllegroWindow.h>
#include <AllwBasics/AllegroEvent.h>
#include "MVC/Controllers/AllegroController.h"
#include "MVC/Observers/StageObserver.h"
#include "MVC/Observers/PlayerDrawer.h"
#include "MVC/Observers/ProyectileDrawer.h"
#include "MVC/Observers/EnemyDrawer.h"
#include "MVC/Observers/WindowUpdater.h"
#include "MVC/Observers/FireBallProjectile.h"
#include "MVC/Observers/SnowBallObserver.h"
#include "MVC/Observers/PlayerInfoObserver.h"
#include "MVC/Observers/PlayerSound.h"
#include "MVC/Observers/MonsterSound.h"

#include "Logica/Personajes/Being.h"

#include "Logica/juego/Game.h"

#include "UI/FSM.h"

#define WindowTitle "SnowBros!"
#define WindowImage ""
std::vector<std::string> getNames(std::string path, std::string ext, int quantinty);
std::vector<World> stringtoworld(std::vector<std::string> files);

#define Player1ID (123)

int main(void) {
	Allw allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 50);

	ALLEGRO_DISPLAY_MODE disp;

	al_get_display_mode(al_get_num_display_modes() - 1, &disp);

	AllegroWindow window(disp.width, disp.height, allegro.getEventQueue(), WindowTitle, WindowImage);

	window.open();
	window.setFullScreen();

	const float BlockWidth = ((window.getWidth() * 0.7) / 16);
	const float BlockHeight((window.getHeight()) / 12);
	const float InfoSpaceWidth(window.getWidth() * 0.3);
	const float InfoSpaceHeight(window.getHeight());


	AllegroEventHandler eventHandler(allegro.getEventQueue());

	Game snowbros(Player1ID);
	EventHandler eventH;

	AllegroSoundFactory soundF;

	FSM menu(&eventHandler);

	menu.setUp(window, soundF, snowbros);



	Local1PlayerController controller(allegro.getEventQueue(), Player1ID);
	eventH.loadController(&controller);

	snowbros.loadEventHandler(&eventH);

	StageObserver stageObserver(BlockHeight * 12, BlockWidth * 16, 'F');
	snowbros.loadObserver(&stageObserver);


	PlayerDrawer  playerDrawer(BlockWidth, BlockHeight);

	std::vector<std::string> a = getNames("Images/Player/Normal/PS", ".png", 12);
	std::vector<std::string> b = getNames("Images/Player/Golden/PS", ".png", 12);
	a.insert(std::end(a), std::begin(b), std::end(b));
	playerDrawer.loadPlayerSprite(a);


	ProyectileDrawer projDrawer("Images/Projectiles/IceProj.png", BlockWidth, BlockHeight);
	PlayerInfoObserver playerInfo("Font\\GameFont.ttf", BlockWidth * 16, InfoSpaceWidth, 0, InfoSpaceHeight);
	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);

	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(BlockWidth, BlockHeight);
	enemyDrawer.loadCrazyGuySprite(getNames("Images/CrazyGuy/CGS", ".png", 9));
	enemyDrawer.loadGreenFattySprite(getNames("Images/GreenFatty/GFS", ".png", 12));
	enemyDrawer.loadPurpleGuySprite(getNames("Images/PurpleGuy/PGS", ".png", 9));
	enemyDrawer.loadFrozenSprites(getNames("Images/Frozen/FSS", ".png", 4));

	FireBallProjectile test("Images/Projectiles/FireProj.png", BlockWidth, BlockHeight);
	enemyDrawer.loadObserver(test);

	snowbros.loadObserver(&enemyDrawer);

	PlayerSound playerSoundObs(soundF);

	snowbros.loadObserver(&playerSoundObs);

	Monsteround monsterSoundObs(soundF);
	snowbros.loadObserver(&monsterSoundObs);




	SnowBallObserver snowBallObs("Images/Frozen/FSS4.png", BlockWidth, BlockHeight);

	snowbros.loadObserver(&snowBallObs);

	WindowUpdater win(window);
	snowbros.loadObserver(&win);

	snowbros.loadMaps(stringtoworld(getNames("Maps/map", ".csv", 10)));

	int ev = BackID;
	void * ptr = nullptr;

	do {
		ev = menu.cycle(ev, ptr);
	} while (ev != ExitID);


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