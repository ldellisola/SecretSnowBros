#include "StageObserver.h"


#define BACKGROUNDIMG "BackgroundSprite.png"
#define GROUNDIMG "GroundSprite.png"

StageObserver::StageObserver(float screenH, float screenW, uint16_t groundID)
	:groundID(groundID)
{
	AllegroColorFactory colorF;

	this->screenHeigth = screenH;
	this->screenWidth = screenW;
	this->background = new AllegroSprite(BACKGROUNDIMG, screenH, screenW);
	this->ground = new AllegroSprite(GROUNDIMG, this->screenHeigth/12, this->screenWidth/16);
}


StageObserver::~StageObserver()
{
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