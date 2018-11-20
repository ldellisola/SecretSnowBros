#include "PlayerDrawer.h"




PlayerDrawer::PlayerDrawer(std::string file, uint16_t blockWidth, uint16_t blockHeight)
	:sprite(file,blockHeight,blockWidth),BlockHeight(blockHeight),BlockWidth(blockWidth)
{
	

}

void PlayerDrawer::loadObserver(Observer * obs)
{
	if(obs !=nullptr)
		this->observers.push_back(obs);
}

void PlayerDrawer::loadObserver(Observer & obs)
{
	this->loadObserver(&obs);
}



void PlayerDrawer::draw(void * data)
{
	Player  * being = ((Game*)data)->getPlayer()[0];

	if (being->isAlive()) {
		if (being->getHorizontalDir() == HorizontalDirection::Right)
			sprite.draw(being->getX() *BlockWidth, being->getY() * BlockHeight);
		else
			sprite.drawHorizontallyMirrored(being->getX() *BlockWidth, being->getY() * BlockHeight);
	}

	for (Observer * obs : observers) {
		obs->draw(being);
	}


}

