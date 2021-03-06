#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/Personajes/Player.h"
#include "Logica/juego/Game.h"


  
//Sonidos del jugador.
class PlayerSound : public Observer {


public:
	PlayerSound(AllegroSoundFactory& soundF) {
		
		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		shootST = soundF.create(al_get_config_value(config,"PlayerMusic","ShootMusicPath"), PlayMode::Once, 12312);
		jumpST = soundF.create(al_get_config_value(config, "PlayerMusic", "JumpMusicPath"), PlayMode::Once, 1232);

		soundF.reserveMoreSamples(4);

		al_destroy_config(config);
	}



	inline void draw(void * ptr) {

		for (Player * player : ((Game*)ptr)->getPlayer()) {


			if (player->isAlive()) {
				if (player->isCoolingDown() && player->getShootingTicks() == 0) {
					shootST->play();
				}

					

				if (player->getState() == BeingState::Jumping && !jumpTimeOff) {
					jumpST->play();
					jumpTimeOff = true;
				}

				if (player->getState() == BeingState::StillJump)
					jumpTimeOff = false;
			}

			

		}
	}



private:
	bool jumpTimeOff = false;
	AllegroSound * shootST = nullptr;
	AllegroSound * jumpST = nullptr;
};