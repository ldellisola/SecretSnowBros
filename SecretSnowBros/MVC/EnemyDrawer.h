#pragma once
#include <stdint.h>
#include <vector>
#include "Observer.h"

#include <AllwAnimation/AllegroSprite.h>

#include "Logica/Personajes/CrazyGuy.h"
#include "Logica/Personajes/PurpleGuy.h"
#include "Logica/Personajes/GreenFatty.h"
#include "Logica/juego/Game.h"


class EnemyDrawer : public Observer
{
public:
	EnemyDrawer(uint16_t blockWidth, uint16_t blockHeight)
		: BlockHeight(blockHeight), BlockWidth(blockWidth)
	{
	}

	~EnemyDrawer()
	{
	}
	void loadObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void loadObserver(Observer&obs) {
		loadObserver(&obs);
	}

	void loadCrazyGuySprite(std::initializer_list<std::string>list) {
		for (std::string str : list) {
			crazyGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}
	void loadPurpleGuySprite(std::initializer_list<std::string>list) {
		for (std::string str : list) {
			purpleGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}
	void loadGreenFattySprite(std::initializer_list<std::string>list) {
		for (std::string str : list) {
			greenFatty.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}

	void loadFrozenSprites(std::initializer_list<std::string>list) {
		for (std::string str : list) {
			frozenSprites.push_back(new AllegroSprite(str,BlockHeight,BlockWidth));
		}
	}


	void draw(void * ptr) {

		auto enemies = ((Game*)ptr)->getMonster();

		for (Monster * enemy : enemies) {

			if (enemy->isAlive()) {

				if (dynamic_cast<GreenFatty*>(enemy)) {
					GreenFatty * guy = dynamic_cast<GreenFatty*>(enemy);
					static int i = 0;
						greenFatty[(i/5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					if (i++ == 29) i = 0;
					
				}
				else if (dynamic_cast<PurpleGuy*>(enemy)) {
					PurpleGuy * guy = dynamic_cast<PurpleGuy*>(enemy);
					static int i = 0;
						purpleGuy[(i / 5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					if (i++ == 25) i = 0;
				}
				else if (dynamic_cast<CrazyGuy*>(enemy)) {
					CrazyGuy * guy = dynamic_cast<CrazyGuy*> (enemy);
					static int i = 0;
						crazyGuy[(i / 5)]->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
					if (i++ == 25) i = 0;
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

	std::vector<AllegroSprite*> crazyGuy,purpleGuy , greenFatty ;
	std::vector<AllegroSprite*>frozenSprites;

};





	