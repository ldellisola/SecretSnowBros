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

	void loadCrazyGuySprite(std::vector<std::string>list) {
		for (std::string str : list) {
			crazyGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}
	void loadPurpleGuySprite(std::vector<std::string>list) {
		for (std::string str : list) {
			purpleGuy.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}
	void loadGreenFattySprite(std::vector<std::string>list) {
		for (std::string str : list) {
			greenFatty.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
	}

	void loadFrozenSprites(std::vector<std::string>list) {
		for (std::string str : list) {
			frozenSprites.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
		}
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





