#pragma once
#include <cstdint>
#include "Logica/Personajes/Score.h"
#include "Logica/Personajes/Base Classes/Slider.h"



class Projectile: public Slider
{
public:
	Projectile(uint16_t x, uint16_t y, HorizontalDirection dir, uint16_t reach, uint16_t maxTick, Score* score)
		:Slider(x,maxTick),reach(reach), startX(x), startY(y), scoreboard(score)
	{
		this->y = startY;
		this->setHorizontalDir(dir);
		this->setHorizontalState(HorizontalState::Moving);
	}
	~Projectile(){}

	uint16_t getY() { return y; }

	// it returns true if the projectile has to die duw to a collision or just going out of range
	bool hasToDie() { 
		uint16_t mod = (getX() - startX > 0 ? getX() - startX : startX - getX());

		if (mod >= reach || !alive)
			return true;
		else
			return false;
	
	}

	Score* getScore() {
		return scoreboard;
	}

	uint16_t getDistanceFromStart() {
		return (getX() - startX > 0 ? getX() - startX : startX - getX());
	}

	void addScore(uint16_t add) {
		if(scoreboard != nullptr)
			*scoreboard += add;
	}

	// It updates the position of the Projectile. It takes a pointes to the World class
	void update(void *ptr) {

			World & map = *(World*)ptr;
			switch (getHorizontalDir())
			{
			case HorizontalDirection::Left:
				if (map.map[y][getX() - 1] == 'F' || map.map[y][getX()] == 'F') 
					this->kill();
				break;
			case HorizontalDirection::Right:
				if (map.map[y][getX() + 1] == 'F' || map.map[y][getX()] == 'F') 
					this->kill();
				break;
			}

			std::unique_ptr<char> row(new char[map.columna]);

			for (int i = 0; i < map.columna; i++) 
				row.get()[i] = map.map[getY()][i];

			Slider::update(row.get());
	}

	void kill() { alive = false; }
private:
	Score* scoreboard;
	uint16_t y;
	bool alive = true;
	const uint16_t reach, startX, startY;
};

