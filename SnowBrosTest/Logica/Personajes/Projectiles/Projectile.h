#pragma once
#include <cstdint>
#include "../Score.h"

enum class ProjectileDirection
{
	Left,Right
};
#ifdef _DEBUG
const std::string _ProjDir[] = { "Left", "Right" };
#endif // _DEBUG

class Projectile
{
public:
	Projectile(uint16_t x, uint16_t y, ProjectileDirection dir, uint16_t reach, uint16_t maxTick, Score& score)
		:reach(reach), startX(x), startY(y), maxTick(maxTick), scoreboard(score)
	{
		this->x = startX;
		this->y = startY;
		this->dir = dir;
		this->tick = 0;
	}
	~Projectile(){}

	uint16_t getX() { return x; }
	uint16_t getY() { return y; }

	bool hasToDie() { 
		uint16_t mod = (x - startX > 0 ? x - startX : startX - x);

		if (mod >= reach || !alive)
			return true;
		else
			return false;
	
	}
	uint16_t getTick() { return tick; }
	ProjectileDirection getDir() { return dir; }

	void addScore(uint16_t add) {
		this->scoreboard += add;
	}

	void update(void *ptr) {
		this->tick++;
		if (this->tick == maxTick) {

			World * map = (World*)ptr;


			this->tick = 0;
			if (this->dir == ProjectileDirection::Left) {
				if (map->map[y][this->x - 1] == 'E')
					this->x--;
				else {
					this->alive = false;
				}
			}
			else if( this->dir == ProjectileDirection::Right){
				if (map->map[y][this->x + 1] == 'E')
					this->x++;
				else {
					this->alive = false;
				}
			}
		}
	}
	void kill() { alive = false; }
private:
	Score& scoreboard;
	uint16_t x, y, tick;
	ProjectileDirection dir;
	bool alive = true;
	const uint16_t reach, startX, startY, maxTick;
};

