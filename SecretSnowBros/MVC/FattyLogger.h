#pragma once
#include "Observer.h"
#include "../Logica/juego/Game.h"
#include "../Logger.h"



class FattyLogger :
	public Observer
{
public:


	void draw(void * ptr) {
		Game& game = *(Game*)ptr;


		std::vector<Monster*> enemies = game.getMonster();
		if (loggers.empty()) {
			for (int i = 0; i < enemies.size(); i++) {
				if (dynamic_cast<GreenFatty*>(enemies[i])) {
					loggers.push_back(new Logger("Logs/Green Fatty ID- " + std::to_string(enemies[i]->getID())));
					fatties.push_back((GreenFatty*)enemies[i]);
				}
			}
		}

		if (tick % 20) {

			for (int i = 0; i < loggers.size(); i++) {

				int x = fatties[i]->getX();
				int y = fatties[i]->getY();



				if(fatties[i]->isShooting())
					loggers[i]->log("Shoot at [" + std::to_string(x) + "," + std::to_string(y) + "]");
				
				else if (fatties[i]->getVerticalState() == VerticalState::Falling && fatties[i]->getVerticalTicks() == 0) {
					loggers[i]->log("Falling at [" + std::to_string(x) + "," + std::to_string(y) + "]");

				}
				else if (fatties[i]->getVerticalState() == VerticalState::Jumping && fatties[i]->getVerticalTicks() == fatties[i]->MaxJumpingTicks / 2)
				{
					loggers[i]->log("Jumping at [" + std::to_string(x) + "," + std::to_string(y) + "], to " + "[" + std::to_string(x) + ", " + std::to_string(y - 1) + "]");

				}
				else if(fatties[i]->getHorizontalState() == HorizontalState::Moving && fatties[i]->getHorizontalTicks() == 0)
					loggers[i]->log("Walked from [" + std::to_string(x) + "," + std::to_string(y) + "]");

				else {
					loggers[i]->log("Standing at [" + std::to_string(x) + "," + std::to_string(y) + "]");

				}

			}


			tick = 0;
		}
		tick++;
	}

private:
	int tick = 0;
	std::vector<Logger*> loggers;
	std::vector<GreenFatty*> fatties;
};




