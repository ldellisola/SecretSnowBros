#include "ProyectileDrawer.h"

float transformCoord(int coord);



ProyectileDrawer::ProyectileDrawer(std::string proyectileSprite, uint16_t blockWidth, uint16_t blockHeight)
	:BlockHeight(blockHeight), BlockWidth(blockWidth)
{
	this->bullet = new AllegroSprite(proyectileSprite,blockHeight,blockWidth);
}

ProyectileDrawer::~ProyectileDrawer()
{
	if(bullet != nullptr)
		delete bullet;
}

void ProyectileDrawer::draw(void * ptr)
{
	Player * shooter = (Player*)ptr;


	std::vector<Projectile*> projectiles = shooter->getProjectiles();

	for (Projectile * proj : projectiles) {
		if (proj->getHorizontalDir() == HorizontalDirection::Right) {
			this->bullet->draw(proj->getX()*BlockWidth, proj->getY() * BlockHeight);
		}
		else if (proj->getHorizontalDir() == HorizontalDirection::Left) {
			this->bullet->drawHorizontallyMirrored(proj->getX()*BlockWidth, proj->getY() * BlockHeight);
		}
	}


}


float transformCoord(int coord) {		// DEBUG

	return coord;
}