#include "AllegroV2/AllegroClassV2.h"
#include "Allegro Wrapper/AllegroWindow.h"
#include "Allegro Wrapper/AllegroEvent.h"


#include "MVC/AllegroController.h"
#include "MVC/StageObserver.h"
#include "MVC/PlayerDrawer.h"
#include "MVC/ProyectileDrawer.h"
#include "MVC/EnemyDrawer.h"
#include "../SnowBrosTest/Logica/Personajes/Being.h"
#include "Logica/juego/Game.h"

#define WindowTitle "SnowBros!"
#define WindowImage ""


#define Player1ID (123)

int main(void) {
	AllegroClass allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 50);

	AllegroWindow window(16 * 100, 12 * 100, allegro.getEventQueue(), WindowTitle, WindowImage);
	window.open();
//	window.setFullScreen();
	AllegroEventHandler eventHandler(allegro.getEventQueue());

	
	Game snowbros(Player1ID);
	EventHandler eventH;

	AllegroAnimation()ggfdafsdfadgsfdgnhfdgsafsgshdgjkhfjdhgsaefwd
	
	
	Local1PlayerController controller(allegro.getEventQueue(), Player1ID);
	eventH.loadController(&controller);

	snowbros.loadEventHandler(&eventH);

	StageObserver stageObserver(window.getHeight(), window.getWidth(),'F');
	snowbros.loadObserver(&stageObserver);


	PlayerDrawer  playerDrawer("PlayerSprite.png", window.getWidth() / 16, window.getHeight() /12);
	ProyectileDrawer projDrawer("ProjectileSprite.png", window.getWidth() / 16, window.getHeight() / 12);
	playerDrawer.loadObserver(projDrawer);


	snowbros.loadObserver(&playerDrawer);

	EnemyDrawer enemyDrawer(window.getWidth() / 16, window.getHeight() / 12);
	enemyDrawer.loadCrazyGuySprite("CrazyGuySprite.png");
	enemyDrawer.loadFrozenSprites({ "FrozenState1.png","FrozenState2.png","FrozenState3.png","FrozenState4.png" });

	snowbros.loadObserver(&enemyDrawer);
	

	World world("map.csv");
	
	snowbros.loadMap(world);

	snowbros.run(nullptr);

	






	return 0;
}