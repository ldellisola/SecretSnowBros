#include "ProyectileDrawer.h"

float transformCoord(int coord);



SnowProyectileDrawer::SnowProyectileDrawer( uint16_t blockWidth, uint16_t blockHeight)
	:BlockHeight(blockHeight), BlockWidth(blockWidth)
{
	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	this->bullet = new AllegroSprite(al_get_config_value(config,"SnowProjectileSprite","Path"),blockHeight,blockWidth);

	al_destroy_config(config);
}

SnowProyectileDrawer::~SnowProyectileDrawer()
{
	if(bullet != nullptr)
		delete bullet;
}

void SnowProyectileDrawer::draw(void * ptr)
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