#include "StageObserver.h"


#define BACKGROUNDIMG "Images/BackgroundSprite.png"
#define GROUNDIMG "Images/GroundSprite.png"

StageObserver::StageObserver(float screenH, float screenW, uint16_t groundID)
	:groundID(groundID)
{
	AllegroColorFactory colorF;

	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	this->screenHeigth = screenH;
	this->screenWidth = screenW;
	this->background = new AllegroSprite(al_get_config_value(config,"GameSprite","BackgroundImagePath"), screenH, screenW);
	this->ground = new AllegroSprite(al_get_config_value(config, "GameSprite", "GroundImagePath"), this->screenHeigth/12, this->screenWidth/16);

	al_destroy_config(config);
}


StageObserver::~StageObserver()
{
	delete background;
	delete ground;
}

void StageObserver::draw(void * ptr){
	World * map = ((Game *)ptr)->getmap();

	
	background->draw(0, 0);
	for (int i = 0; i < map->fila; i++) {
		for (int j = 0; j < map->columna; j++) {
			if (map->map[i][j] == this->groundID) {

				int indexY = i * this->screenHeigth / 12;
				int indexX = j * this->screenWidth / 16;


				ground->draw(indexX,indexY);
			}
		}
	}

}