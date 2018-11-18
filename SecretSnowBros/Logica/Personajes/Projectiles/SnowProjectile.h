#pragma once
#include "Projectile.h"
#include <stdint.h>

class SnowProjectile
	:public Projectile
{
public:
	SnowProjectile(uint16_t x, uint16_t y, ProjectileDirection dir, Score* score)
		:Projectile(x,y,dir,3,6,(Score*)score)
	{
	}

	~SnowProjectile()
	{
	}


};
