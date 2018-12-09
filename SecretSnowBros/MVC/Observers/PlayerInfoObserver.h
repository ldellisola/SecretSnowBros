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

	PlayerInfoObserver( float startX, float width, float startY, float height) {

		std::string text;

		ALLEGRO_CONFIG *config = al_load_config_file("config.ini");

		std::string fontPath = al_get_config_value(config, "Font", "GamePath");
		
		text = al_get_config_value(config, "SnowBros", "highscore");
		currentHighScore = std::stoi(text);
			
		al_destroy_config(config);

		highScoreBox = new AllegroWrittenBox(startX, startY, width, height / 3.0, "Highscore = " + text, fontF.create(fontPath, height / 20,0), colorF.create("white"), 234);
		scoreBox = new AllegroWrittenBox(startX, startY+ height / 3.0, width, height / 3, "Score = 0", fontF.create(fontPath, height / 16, 1), colorF.create("white"), 1);
		lifeBox = new AllegroWrittenBox(startX, startY + height *2/ 3.0, width, height / 3, "Score = 0", fontF.create(fontPath, height / 16, 2), colorF.create("white"), 2);
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
		if (highScoreBox)
			delete highScoreBox;
	}

	void draw(void * ptr) {


		Player * player = (Player*)ptr;

		background->draw();

		highScoreBox->setText("HighScore = " + std::to_string(currentHighScore));
		highScoreBox->draw();

		std::string score = std::to_string(player->getScoreCounter()->getActualScore());
		scoreBox->setText("Score = " + score);
		scoreBox->draw();


		std::string lives = std::to_string(player->getLives());
		lifeBox->setText("Lives = " + lives);

		lifeBox->draw();

		if (!player->isAlive()) {
			int currentScore = player->getScoreCounter()->getActualScore();
			if (currentScore > currentHighScore) {
				saveHighScore(currentScore);
				currentHighScore = currentScore;

			}

		}
	}



private:
	bool firstTime = true;
	void saveHighScore(int score) {
		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");
		al_set_config_value(config, "SnowBros", "highscore",std::to_string(score).c_str());
		al_save_config_file("config.ini", config);
		al_destroy_config(config);

	}


	AllegroColorFactory colorF;
	AllegroWrittenBox * scoreBox = nullptr;
	AllegroWrittenBox * lifeBox = nullptr;
	AllegroBox * background = nullptr;
	AllegroWrittenBox * highScoreBox = nullptr;
	AllegroFontFactory fontF;

	int currentHighScore = 0;

};