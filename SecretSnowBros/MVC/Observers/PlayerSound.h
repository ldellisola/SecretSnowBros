#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/Personajes/Player.h"
#include "Logica/juego/Game.h"




class PlayerSound : public Observer {


public:
	PlayerSound(AllegroSoundFactory& soundF) {
		

		shootST = soundF.create("Music\\Character\\ShootDM.wav", PlayMode::Once, 12312);
		jumpST = soundF.create("Music\\Character\\Jump.wav", PlayMode::Once, 1232);
		backgroundMusic = soundF.create("Music\\Soundtrack\\Day Man.ogg",PlayMode::Loop,111);

		soundF.reserveMoreSamples(10);
	}


	inline void draw(void * ptr) {

		for (Player * player : ((Game*)ptr)->getPlayer()) {
			if (firstTime) {
				firstTime = false;
				backgroundMusic->play();
			}

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
			else {
				backgroundMusic->stop(); 
				firstTime = true;
			}
			

		}
	}



private:
	bool jumpTimeOff = false;
	bool firstTime = true;
	AllegroSound * shootST = nullptr;
	AllegroSound * jumpST = nullptr;
	AllegroSound * backgroundMusic = nullptr;
};