#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/Personajes/Monster.h"
#include "Logica/Personajes/GreenFatty.h"

#include "Logica/juego/Game.h"


//Clase que implementa los sonidos de los mosntruos

class MonsterSound : public Observer {


public:
	MonsterSound(AllegroSoundFactory& soundF) {

		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		shootST = soundF.create(al_get_config_value(config, "MonsterMusic", "ShootMusicPath"), PlayMode::Once, 12312);

		soundF.reserveMoreSamples(15);


	}

	inline void draw(void * ptr) {

		for (Monster * enemy : ((Game*)ptr)->getMonster()) {

			if (enemy->isAlive()) 
				if(dynamic_cast<GreenFatty *>(enemy))
					if (((GreenFatty *)enemy)->isCoolingDown() && ((GreenFatty *)enemy)->getShootingTicks() == 1) 
						shootST->play();

		}
	}
	


private:
	bool jumpTimeOff = false;
	AllegroSound * shootST = nullptr;
};