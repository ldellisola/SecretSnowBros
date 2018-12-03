#pragma once

#include <AllwBasics/AllegroSound.h>
#include "Observer.h"
#include "Logica/juego/Game.h"




class StageSound : public Observer {


public:
	StageSound(AllegroSoundFactory& soundF) {

		backgroundMusic = soundF.create("Music\\Soundtrack\\Day Man.ogg", PlayMode::Loop, 111);

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