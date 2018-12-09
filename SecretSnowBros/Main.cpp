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




#define Player1ID (123)

int main(void) {
	Allw allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 50);


	AllegroWindow window(1000, 1000, allegro.getEventQueue());

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


	PlayerDrawer  playerDrawer(BlockWidth, BlockHeight); //Create player and load it
	StageObserver stageObserver(BlockHeight * 12, BlockWidth * 16, 'F'); //creating observers and loading them
	SnowProyectileDrawer snowProjDrawer(BlockWidth, BlockHeight);
	PlayerInfoObserver playerInfo(BlockWidth * 16, InfoSpaceWidth, 0, InfoSpaceHeight);
	FireBallProjectile fireProjDrawer( BlockWidth, BlockHeight);
	PlayerSound playerSoundObs(soundF);
	StageSound stageSoundObs(soundF);
	MonsterSound monsterSoundObs(soundF);

	EnemyDrawer enemyDrawer(BlockWidth, BlockHeight);
	SnowBallObserver snowBallObs(BlockWidth, BlockHeight);
	WindowUpdater win(window);


	playerDrawer.loadObserver(playerInfo);
	playerDrawer.loadObserver(snowProjDrawer);
	snowbros.loadObserver(&stageObserver);
	enemyDrawer.loadObserver(&fireProjDrawer);
	snowbros.loadObserver(&enemyDrawer);
	snowbros.loadObserver(&playerSoundObs);
	snowbros.loadObserver(&monsterSoundObs);
	snowbros.loadObserver(&stageSoundObs);
	snowbros.loadObserver(&playerDrawer);
	snowbros.loadObserver(&snowBallObs);
	snowbros.loadObserver(&win);


	int ev = BackID;
	void * ptr = &window;

	do {
		ev = menu.cycle(ev, ptr); //Main loop in wich the fsm is used.
	} while (ev != ExitID);


	return 0;
}

