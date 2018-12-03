#pragma once
#include <stdint.h>
#include <AllwUI/WrittenBox.h>
#include <AllwBasics/AllegroFont.h>
#include <AllwInit/AllegroFactory.h>

#include "Observer.h"
#include "Logica/Personajes/Player.h"
 //Puntaje
class PlayerInfoObserver
	: public Observer {
public:

	PlayerInfoObserver(std::string fontPath, float startX, float width, float startY, float height) {

		AllegroColorFactory colorF;

		scoreBox = new AllegroWrittenBox(startX, startY, width, height / 2, "Score = 0", fontF.create(fontPath, height / 16, 1), colorF.create("white"), 1);
		lifeBox = new AllegroWrittenBox(startX, startY + height / 2, width, height / 2, "Score = 0", fontF.create(fontPath, height / 16, 2), colorF.create("white"), 2);
		background = new AllegroBox(startX, startY, width, height, 93);
		background->setBackgroundColor(colorF.create("black"));
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