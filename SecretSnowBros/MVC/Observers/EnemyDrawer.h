#pragma once
#include <stdint.h>
#include <vector>
#include "Observer.h"

#include <AllwAnimation/AllegroSprite.h>

#include "Logica/Personajes/CrazyGuy.h"
#include "Logica/Personajes/PurpleGuy.h"
#include "Logica/Personajes/GreenFatty.h"
#include "Logica/juego/Game.h"

//Clase dedicada al dibujo en pantalla de los enemigos
class EnemyDrawer : public Observer
{
public:
	EnemyDrawer(uint16_t blockWidth, uint16_t blockHeight)
		: BlockHeight(blockHeight), BlockWidth(blockWidth)
	{
		loadCrazyGuySprite();
		loadFrozenSprites();
		loadGreenFattySprite();
		loadPurpleGuySprite();
	}

	~EnemyDrawer()
	{
		for (auto sprite : this->frozenSprites)
			delete sprite;

		for (auto sprite : this->crazyGuy)
			delete sprite;

		for (auto sprite : this->greenFatty)
			delete sprite;
		
		for (auto sprite : this->purpleGuy)
			delete sprite;
	}


	void loadObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void loadObserver(Observer&obs) {
		loadObserver(&obs);
	}

	void loadCrazyGuySprite() { 

		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		int quantinty = std::atoi(al_get_config_value(config, "CrazyGuySprite", "Files"));
		std::string path = al_get_config_value(config, "CrazyGuySprite", "Path");
		std::string ext = al_get_config_value(config, "CrazyGuySprite", "Extension");

		std::vector<std::string> names;

		for (int i = 0; i < quantinty; i++)
			names.push_back(path + std::to_string(i + 1) + ext);


		for (std::string str : names) 
			crazyGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		
		al_destroy_config(config);
	}

	void loadPurpleGuySprite() {

		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		int quantinty = std::atoi(al_get_config_value(config, "PurpleGuySprite", "Files"));
		std::string path = al_get_config_value(config, "PurpleGuySprite", "Path");
		std::string ext = al_get_config_value(config, "PurpleGuySprite", "Extension");

		std::vector<std::string> names;

		for (int i = 0; i < quantinty; i++)
			names.push_back(path + std::to_string(i + 1) + ext);


		for (std::string str : names)
			purpleGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));

		al_destroy_config(config);

	}

	void loadGreenFattySprite() {

		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		int quantinty = std::atoi(al_get_config_value(config, "GreenFattySprite", "Files"));
		std::string path = al_get_config_value(config, "GreenFattySprite", "Path");
		std::string ext = al_get_config_value(config, "GreenFattySprite", "Extension");

		std::vector<std::string> names;

		for (int i = 0; i < quantinty; i++)
			names.push_back(path + std::to_string(i + 1) + ext);


		for (std::string str : names)
			greenFatty.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));

		al_destroy_config(config);

	}

	void loadFrozenSprites() {

		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		int quantinty = std::atoi(al_get_config_value(config, "FrozenStagesSprite", "Files"));
		std::string path = al_get_config_value(config, "FrozenStagesSprite", "Path");
		std::string ext = al_get_config_value(config, "FrozenStagesSprite", "Extension");

		std::vector<std::string> names;

		for (int i = 0; i < quantinty; i++)
			names.push_back(path + std::to_string(i + 1) + ext);


		for (std::string str : names)
			frozenSprites.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));

		al_destroy_config(config);

	}


	void draw(void * ptr) {

		auto enemies = ((Game*)ptr)->getMonster();

		for (Monster * enemy : enemies) {

			if (enemy->isAlive()) {

				/*Cambia la imagen cada 5 ticks dependiendo que esta haciendo*/

				if (dynamic_cast<GreenFatty*>(enemy)) {
					GreenFatty * guy = dynamic_cast<GreenFatty*>(enemy);
					if (enemy->getState() == BeingState::WalkingRight && enemy->getHorizontalDir()== HorizontalDirection::Right) {
						static int i = 0;
						greenFatty[(i / 5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::WalkingLeft && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						static int i = 0;
						greenFatty[(i / 5)]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Right) {
						greenFatty[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						greenFatty[0]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::Jumping) {
						static int i = 30;
						greenFatty[i / 5]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 44) i = 0;
					}
					else if (enemy->getState() == BeingState::Shooting &&  enemy->getHorizontalDir() == HorizontalDirection::Right) {
						static int i = 45;
						greenFatty[i / 5]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 59) i = 0;
					}
					else if (enemy->getState() == BeingState::Shooting &&  enemy->getHorizontalDir() == HorizontalDirection::Left) {
						static int i = 45;
						greenFatty[i / 5]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 59) i = 0;
					}
					else {
						greenFatty[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}

				}
				else if (dynamic_cast<PurpleGuy*>(enemy)) {
					PurpleGuy * guy = dynamic_cast<PurpleGuy*>(enemy);
					if (enemy->getState() == BeingState::WalkingRight && enemy->getHorizontalDir() == HorizontalDirection::Right) {
						static int i = 0;
						purpleGuy[(i / 5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::WalkingLeft && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						static int i = 0;
						purpleGuy[(i / 5)]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Right) {
						purpleGuy[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						purpleGuy[0]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::Jumping) {
						static int i = 30;
						purpleGuy[i / 5]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 44) i = 0;
					}
					else {
						purpleGuy[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}

				}
				else if (dynamic_cast<CrazyGuy*>(enemy)) {
					CrazyGuy * guy = dynamic_cast<CrazyGuy*> (enemy);

					if (enemy->getState() == BeingState::WalkingRight && enemy->getHorizontalDir() == HorizontalDirection::Right) {
						static int i = 0;
						crazyGuy[(i / 5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::WalkingLeft && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						static int i = 0;
						crazyGuy[(i / 5)]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 29) i = 0;
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Right) {
						crazyGuy[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::StillWalk && enemy->getHorizontalDir() == HorizontalDirection::Left) {
						crazyGuy[0]->drawHorizontallyMirrored(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}
					else if (enemy->getState() == BeingState::Jumping) {
						static int i = 30;
						crazyGuy[i / 5]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
						if (i++ == 44) i = 0;
					}
					else {
						crazyGuy[0]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					}

				}

				if (enemy->isFrozen()) {
					frozenSprites[enemy->getFreezeState() - 1]->draw(enemy->getX() * BlockWidth, enemy->getY() * BlockHeight);
				}

				for (Observer * obs : observers) {
					obs->draw(enemy);
				}
			}

		}






	}

private:
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;

	std::vector<Observer*> observers;

	std::vector<AllegroSprite*> crazyGuy, purpleGuy, greenFatty;
	std::vector<AllegroSprite*>frozenSprites;

};





