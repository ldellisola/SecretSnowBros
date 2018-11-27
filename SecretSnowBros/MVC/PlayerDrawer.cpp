#include "PlayerDrawer.h"




PlayerDrawer::PlayerDrawer(uint16_t blockWidth, uint16_t blockHeight)
	:BlockHeight(blockHeight),BlockWidth(blockWidth)
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

	for (Player * being : ((Game*)data)->getPlayer()) {

		if (being->isAlive() && !being->isWaitingToRevive() && !being->isInmune()) {
			if (being->getState()==BeingState::StillWalk && being->getHorizontalDir() == HorizontalDirection::Right) {
				sprites[0]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
			else if (being->getState() == BeingState::StillWalk && being->getHorizontalDir() == HorizontalDirection::Left) {
				sprites[0]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
			else if (being->getState() == BeingState::WalkingRight && being->getHorizontalDir() == HorizontalDirection::Right) {
				static int i = 0;
				sprites[(i / 5)]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 25) i = 0;
			}
			else if (being->getState() == BeingState::WalkingLeft && being->getHorizontalDir() == HorizontalDirection::Left) {
				static int i = 0;
				sprites[(i / 5)]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 25) i = 0;
			}
			else if (being->getState() == BeingState::Jumping) {
				static int i = 30;
				sprites[i/5]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 44) i = 0;
			}
			else if (being->getState() == BeingState::Shooting &&  being->getHorizontalDir() == HorizontalDirection::Right) {
				static int i = 45;
				sprites[i / 5]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 59) i = 0;
			}
			else if (being->getState() == BeingState::Shooting &&  being->getHorizontalDir() == HorizontalDirection::Left) {
				static int i = 45;
				sprites[i / 5]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 59) i = 0;
			}
			else {
				sprites[0]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
		}
		else if (being->isAlive() && !being->isWaitingToRevive() && being->isInmune()) {
			if (being->getState() == BeingState::StillWalk && being->getHorizontalDir() == HorizontalDirection::Right) {
				sprites[12]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
			else if (being->getState() == BeingState::StillWalk && being->getHorizontalDir() == HorizontalDirection::Left) {
				sprites[12]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
			else if (being->getState() == BeingState::WalkingRight && being->getHorizontalDir() == HorizontalDirection::Right) {
				static int i = 60;
				sprites[(i / 5)]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 25+60) i = 60;
			}
			else if (being->getState() == BeingState::WalkingLeft && being->getHorizontalDir() == HorizontalDirection::Left) {
				static int i = 60;
				sprites[(i / 5)]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 25+60) i = 60;
			}
			else if (being->getState() == BeingState::Jumping) {
				static int i = 30+60;
				sprites[i / 5]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 44+60) i = 90;
			}
			else if (being->getState() == BeingState::Shooting &&  being->getHorizontalDir() == HorizontalDirection::Right) {
				static int i = 45+60;
				sprites[i / 5]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 59+60) i = 45 + 60;
			}
			else if (being->getState() == BeingState::Shooting &&  being->getHorizontalDir() == HorizontalDirection::Left) {
				static int i = 45+60;
				sprites[i / 5]->drawHorizontallyMirrored(being->getX() * BlockWidth, being->getY() * BlockHeight);
				if (i++ == 59+60) i = 45 + 60;
			}
			else {
				sprites[12]->draw(being->getX() * BlockWidth, being->getY() * BlockHeight);
			}
		}
		for (Observer * obs : observers) {
			obs->draw(being);
		}
	}


}

