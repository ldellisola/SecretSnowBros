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
#include "MVC/Observers/StageSound.h"

#include "Logica/Personajes/Being.h"

#include "Logica/juego/Game.h"

#include "UI/FSM.h"

#define WindowTitle "SnowBros!"
#define WindowImage ""

#define Block (50)


#define Player1ID (123)

int main(void) {
	Allw allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 50);
	ALLEGRO_DISPLAY_MODE disp;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp);

	AllegroWindow window(disp.width, disp.height, allegro.getEventQueue(), WindowTitle, WindowImage);

	window.open();
	//window.setFullScreen();

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


	PlayerDrawer  playerDrawer(BlockWidth, BlockHeight); //Create player and load it
	std::vector<std::string> a = getNames("Images/Player/Normal/PS", ".png", 12);
	std::vector<std::string> b = getNames("Images/Player/Golden/PS", ".png", 12);
	a.insert(std::end(a), std::begin(b), std::end(b));
	playerDrawer.loadPlayerSprite(a);

	StageObserver stageObserver(BlockHeight * 12, BlockWidth * 16, 'F'); //creating observers and loading them
	ProyectileDrawer projDrawer("Images/Projectiles/IceProj.png", BlockWidth, BlockHeight);
	PlayerInfoObserver playerInfo("Font\\GameFont.ttf", BlockWidth * 16, InfoSpaceWidth, 0, InfoSpaceHeight);
	FireBallProjectile test("Images/Projectiles/FireProj.png", BlockWidth, BlockHeight);
	PlayerSound playerSoundObs(soundF);
	Monsteround monsterSoundObs(soundF);
	EnemyDrawer enemyDrawer(BlockWidth, BlockHeight);
	SnowBallObserver snowBallObs("Images/Frozen/FSS4.png", BlockWidth, BlockHeight);
	WindowUpdater win(window);
	enemyDrawer.loadCrazyGuySprite(getNames("Images/CrazyGuy/CGS", ".png", 9));
	enemyDrawer.loadGreenFattySprite(getNames("Images/GreenFatty/GFS", ".png", 12));
	enemyDrawer.loadPurpleGuySprite(getNames("Images/PurpleGuy/PGS", ".png", 9));
	enemyDrawer.loadFrozenSprites(getNames("Images/Frozen/FSS", ".png", 4));


	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(projDrawer);
	snowbros.loadObserver(&stageObserver);
	enemyDrawer.loadObserver(&test);
	snowbros.loadObserver(&enemyDrawer);
	snowbros.loadObserver(&playerSoundObs);
	snowbros.loadObserver(&monsterSoundObs);
	snowbros.loadObserver(&playerDrawer);
	snowbros.loadObserver(&snowBallObs);
	snowbros.loadObserver(&win);


	int ev = BackID;
	void * ptr = nullptr;

	do {
		ev = menu.cycle(ev, ptr);
	} while (ev != ExitID);


	return 0;
}

