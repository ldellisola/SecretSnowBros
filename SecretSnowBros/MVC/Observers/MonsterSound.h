#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/Personajes/Monster.h"
#include "Logica/Personajes/GreenFatty.h"

#include "Logica/juego/Game.h"


//Clase que implementa los sonidos de los mosntruos

class Monsteround : public Observer {


public:
	Monsteround(AllegroSoundFactory& soundF) {

		shootST = soundF.create("Music\\Character\\ShootGM.wav", PlayMode::Once, 12312);
		jumpST = soundF.create("Music\\Character\\Jump.wav", PlayMode::Once, 1232);

		soundF.reserveMoreSamples(30);
	}

	inline void draw(void * ptr) {

		for (Monster * enemy : ((Game*)ptr)->getMonster()) {

			if (enemy->isAlive()) {
				if(dynamic_cast<GreenFatty *>(enemy))
					if (((GreenFatty *)enemy)->isCoolingDown() && ((GreenFatty *)enemy)->getShootingTicks() == 1) {
						shootST->play();
					}


				if (enemy->getState() == BeingState::Jumping && !jumpTimeOff) {
					jumpST->play();
					jumpTimeOff = true;
				}

				if (enemy->getState() == BeingState::StillJump)
					jumpTimeOff = false;
			}


		}
	}
	


private:
	bool jumpTimeOff = false;
	AllegroSound * shootST = nullptr;
	AllegroSound * jumpST = nullptr;
};