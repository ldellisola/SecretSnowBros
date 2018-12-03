#pragma once
#include <stdint.h>
#include <AllwUI/WrittenBox.h>
#include <AllwBasics/AllegroFont.h>
#include <AllwInit/AllegroFactory.h>

#include "Observer.h"
#include "Logica/Personajes/Player.h"

class PlayerInfoObserver
	: public Observer {
public:

	PlayerInfoObserver(std::string fontPath, uint16_t totalWidth, uint16_t boxHeight, uint16_t startingHeight) {
		AllegroColorFactory colorF;
		

		scoreBox = new AllegroWrittenBox(0, startingHeight, totalWidth / 2, boxHeight, "Score = 0", fontF.create(fontPath, boxHeight / 4, 1), colorF.create("white"), 1);
		lifeBox = new AllegroWrittenBox(totalWidth / 2, startingHeight, totalWidth / 2, boxHeight, "Score = 0", fontF.create(fontPath, boxHeight / 4, 2), colorF.create("white"), 2);
		background = new AllegroBox(0, startingHeight, totalWidth, boxHeight, 90);
	}
	~PlayerInfoObserver()
	{
		if (scoreBox)
			delete scoreBox;
		if (lifeBox)
			delete lifeBox;
		if (background)
			delete background;
	}

	void draw(void * ptr) {

		Player * player = (Player*)ptr;
		AllegroColorFactory colorF;

		background->setBackgroundColor(colorF.create("black"));
		background->draw();

		std::string score = std::to_string(player->getScoreCounter()->getActualScore());
		scoreBox->setText("Score = " + score);
		scoreBox->draw();


		std::string lives = std::to_string(player->getLives());
		lifeBox->setText("Lives = " + lives);

		lifeBox->draw();


		

	}


private:

	AllegroWrittenBox * scoreBox = nullptr;
	AllegroWrittenBox * lifeBox = nullptr;
	AllegroBox * background = nullptr;
	AllegroFontFactory fontF;


};