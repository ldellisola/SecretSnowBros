#pragma once

#include "Logica/Personajes/Projectiles/Projectile.h"
#include <stdint.h>
#include <vector>
//class with the abulity to shoot
template  <typename T>class Shooter
{
public:
	Shooter(uint16_t maxShootTicks_)
		:maxShootTicks(maxShootTicks_){}

	// It shoots a projectile in a given direction
	void shoot(uint16_t x, uint16_t y, HorizontalDirection dir,void* score = nullptr) {
		Projectile * temp = new T(x, y, dir,(Score*)score);
		projectiles.push_back(temp);
	}


	std::vector<Projectile*>& getProjectiles() {
		return projectiles;
	}

	// It updates all the projectiles fired from a Shooter every tick
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

	bool isShooting() {
		return shooting;
	}

	bool isCoolingDown() {		// Cuando pasan los ticks me dice que ya puedo disparar de vuelta
		return cooldown;
	}

	virtual ~Shooter()
	{
		for (Projectile * proj : projectiles)
			delete proj;
	}

	uint16_t getShootingTicks() {
		return shootingTicks;
	}

protected:
	std::vector<Projectile*> projectiles;

	void resetShootingTicks() {
		shootingTicks = 0;
	}

	void updateShootingTicks() {
		this->shootingTicks = (this->shootingTicks + 1) % maxShootTicks;
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
