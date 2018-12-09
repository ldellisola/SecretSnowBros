#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/juego/Game.h"


//Sonidos del mapa-

class StageSound : public Observer {


public:
	StageSound(AllegroSoundFactory& soundF) {
		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		backgroundMusic = soundF.create(al_get_config_value(config, "GameMusic", "MusicPath"), PlayMode::Loop, 111);

		al_destroy_config(config);

	}


	inline void draw(void * ptr) {

		Game * game = (Game*)ptr;
		if (firstTime)
		{
			firstTime = false;
			backgroundMusic->play();
		}

		if (!game->checkIfMonstersAlive()) {
			firstTime = true;
			backgroundMusic->stop();
		}
		else if (!game->checkIfPlayersAlive()) {
			firstTime = true;
			backgroundMusic->stop();
		}
	}



private:
	bool firstTime = true;
	AllegroSound * backgroundMusic = nullptr;
};