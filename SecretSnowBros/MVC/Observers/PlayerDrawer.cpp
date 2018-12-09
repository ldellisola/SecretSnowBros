#include "PlayerDrawer.h"




PlayerDrawer::PlayerDrawer(uint16_t blockWidth, uint16_t blockHeight)
	:BlockHeight(blockHeight),BlockWidth(blockWidth)
{
	
	loadPlayerSprite();

}

PlayerDrawer::~PlayerDrawer()
{
	for (auto sprite : sprites)
		delete sprite;
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

void PlayerDrawer::loadPlayerSprite()
{
	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	int quantinty = std::atoi(al_get_config_value(config, "RegularPlayerSprite", "Files"));
	std::string path = al_get_config_value(config, "RegularPlayerSprite", "Path");
	std::string ext = al_get_config_value(config, "RegularPlayerSprite", "Extension");

	std::vector<std::string> names;

	for (int i = 0; i < quantinty; i++) 
		names.push_back(path + std::to_string(i + 1) + ext);
	
	quantinty = std::atoi(al_get_config_value(config, "InmunePlayerSprite", "Files"));
	path = al_get_config_value(config, "InmunePlayerSprite", "Path");
	ext = al_get_config_value(config, "InmunePlayerSprite", "Extension");


	al_destroy_config(config);

	for (int i = 0; i < quantinty; i++)
		names.push_back(path + std::to_string(i + 1) + ext);




	for (std::string str : names) {
		sprites.push_back(new AllegroSprite(str, BlockHeight, BlockWidth));
	}
}



void PlayerDrawer::draw(void * data)
{

	for (Player * being : ((Game*)data)->getPlayer()) {

		/*Si es inmune tiene las mismas animaciones pero doradas, dependiendo la accion va a ser una animacion o la otra a 5 ticks por animacion*/
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

