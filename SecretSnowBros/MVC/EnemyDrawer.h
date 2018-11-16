#pragma once
#include <stdint.h>
#include <vector>
#include "Observer.h"

#include "AllwAnimation/AllegroSprite.h"

#include "../Logica/Personajes/CrazyGuy.h"
#include "../Logica/Personajes/PurpleGuy.h"
#include "../Logica/Personajes/GreenFatty.h"
#include "../Logica/juego/Game.h"


class EnemyDrawer : public Observer
{
public:
	EnemyDrawer(uint16_t blockWidth, uint16_t blockHeight)
		: BlockHeight(blockHeight), BlockWidth(blockWidth)
	{
	}

	~EnemyDrawer()
	{
		if (greenFatty) {
			delete greenFatty;
		}
		if (purpleGuy) {
			delete purpleGuy;
		}
		if (crazyGuy)
			delete crazyGuy;
	}
	void loadObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void loadObserver(Observer&obs) {
		loadObserver(&obs);
	}

	void loadCrazyGuySprite(std::string sprite) {
		this->crazyGuy = new AllegroSprite(sprite, BlockHeight, BlockWidth);
	}

	void loadPurpleGuySprite(std::string sprite) {
		this->purpleGuy = new AllegroSprite(sprite, BlockHeight, BlockWidth);
	}

	void loadGreenFattySprite(std::string sprite) {
		this->greenFatty = new AllegroSprite(sprite, BlockHeight, BlockWidth);
	}

	void loadFrozenSprites(std::initializer_list<std::string>list) {
		for (std::string str : list) {
			frozenSprites.push_back(new AllegroSprite(str,BlockHeight,BlockWidth));
		}
	}


	void draw(void * ptr) {

		auto enemies = ((Game*)ptr)->getMonster();

		for (Monster * enemy : enemies) {

			if (dynamic_cast<GreenFatty*>(enemy)) {
				GreenFatty * guy = dynamic_cast<GreenFatty*>(enemy);

				greenFatty->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
			}
			else if (dynamic_cast<PurpleGuy*>(enemy)) {
				PurpleGuy * guy = dynamic_cast<PurpleGuy*>(enemy);

				purpleGuy->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
			}
			else if (dynamic_cast<CrazyGuy*>(enemy)) {
				CrazyGuy * guy = dynamic_cast<CrazyGuy*> (enemy);

				crazyGuy->draw(guy->getX() * BlockWidth, guy->getY() * BlockHeight);
			}

			if (enemy->isFrozen()) {
				frozenSprites[enemy->getFreezeState() - 1]->draw(enemy->getX() * BlockWidth, enemy->getY() * BlockHeight);
			}

			for (Observer * obs : observers) {
				obs->draw(enemy);
			}

		}


		



	}

private:
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;

	std::vector<Observer*> observers;

	AllegroSprite* crazyGuy = nullptr,*purpleGuy = nullptr,* greenFatty = nullptr;
	std::vector<AllegroSprite*>frozenSprites;

};





	