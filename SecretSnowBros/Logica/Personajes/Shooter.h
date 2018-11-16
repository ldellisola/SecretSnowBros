#pragma once

#include "Projectiles/Projectile.h"
#include <stdint.h>
#include <vector>

template  <typename T>class Shooter
{
public:
	Shooter(uint16_t maxShootTicks_)
		:maxShootTicks(maxShootTicks_)
	{
	}

	void shoot(uint16_t x, uint16_t y, ProjectileDirection dir,void* score) {
		Projectile * temp = new T(x, y, dir,(Score*)score);
		projectiles.push_back(temp);
	}

	std::vector<Projectile*>& getProjectiles() {
		return projectiles;
	}

	void updateProjectiles(void * ptr) {

		for (auto it = projectiles.begin(); it != projectiles.end(); it) {
			if ((*it)->hasToDie()) {
				Projectile*temp = *it;
				delete temp;
				it = projectiles.erase(it);
			}
			else {
				(*it)->update(ptr);
				it++;
			}
		}
	}


	virtual ~Shooter()
	{
		for (Projectile * proj : projectiles)
			delete proj;
	}

protected:
	std::vector<Projectile*> projectiles;

	void resetShootingTicks() {
		shootingTicks = 0;
	}

	void updateShootingTicks() {

		this->shootingTicks = (this->shootingTicks + 1) % maxShootTicks;
	}

	uint16_t getShootingTicks() {
		return shootingTicks;
	}


	bool isCoolingDown() {		// Cuando pasan los ticks me dice que ya puedo disparar de vuelta
		return cooldown;
	}

	bool isShooting() {
		return shooting;
	}

	void startShooting() {
		shooting = true;
	}

	void stopShooting() {
		shooting = false;
	}

	void startCoolDown() {
		cooldown = true;
	}

	void stopCoolDown() {
		cooldown = false;
	}

private:
	uint16_t shootingTicks;
	const uint16_t maxShootTicks;
	bool cooldown;
	bool shooting;

};
