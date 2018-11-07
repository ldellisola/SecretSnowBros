#include "AllegroAnimation.h"

AllegroAnimation::~AllegroAnimation()
{
	if (!foreignAnimation)
		for (int i = 0; i < sprites.size(); i++)
			delete sprites[i];
}

void AllegroAnimation::updateCounter()
{
	this->counter = this->counter++ % this->sprites.size();
}

AllegroAnimation::AllegroAnimation(std::vector<std::string> files)
{
	for (int i = 0; i < files.size(); i++)
		sprites.push_back(new AllegroSprite(files[i]));
}

AllegroAnimation::AllegroAnimation(std::vector<std::string> files, float angle)
{
	for (int i = 0; i < files.size(); i++)
		sprites.push_back(new AllegroSprite(files[i],angle));
}

AllegroAnimation::AllegroAnimation(std::vector<std::string> files, float height, float width)
{
	for (int i = 0; i < files.size(); i++)
		sprites.push_back(new AllegroSprite(files[i], height, width));
}

AllegroAnimation::AllegroAnimation(std::vector<std::string> files, float height, float width, float angle)
{
	for (int i = 0; i < files.size(); i++)
		sprites.push_back(new AllegroSprite(files[i], height, width,angle));
}


AllegroAnimation::AllegroAnimation(std::vector<AllegroSprite *> animation)
{
	for (int i = 0; i < animation.size(); i++)
		sprites.push_back(animation[i]);
}

bool AllegroAnimation::insert(std::string file, unsigned int position)
{
	if (this->foreignAnimation)
		return false;
	else {
		if (position >= this->sprites.size())
			this->append(file);
		else
			this->sprites.insert(this->sprites.begin() + position, new AllegroSprite(file));
		return true;
	}
}

bool AllegroAnimation::append(std::string file)
{
	if (this->foreignAnimation)
		return false;
	else {
		this->sprites.push_back(new AllegroSprite(file));
		return true;
	}
}

bool AllegroAnimation::insert(AllegroSprite * sprite, unsigned int position)
{
	if (this->foreignAnimation) {
		if (position >= this->sprites.size())
			this->append(sprite);
		else
			this->sprites.insert(this->sprites.begin() + position, sprite);
		return true;
	}
	else 
		return false;
	
}

bool AllegroAnimation::append(AllegroSprite * sprite)
{
	if (this->foreignAnimation) {
		this->sprites.push_back( sprite);
		return true;
	}
	else
		return false;
}

bool AllegroAnimation::remove(unsigned int position)
{
	if (this->foreignAnimation) {
		if (position < this->sprites.size()) {
			this->sprites.erase(sprites.begin() + position);
			return true;
		}
		else
			return false;
	}
	else {
		if (position < this->sprites.size()) {
			delete this->sprites[position];
			this->sprites.erase(sprites.begin() + position);
			return true;
		}
		else
			return false;
	}
}

AllegroSprite * AllegroAnimation::recover(unsigned int position)
{
	if (position < this->sprites.size())
		return sprites[position];
	else
		return nullptr;
}

bool AllegroAnimation::swap(unsigned int spriteA, unsigned int spriteB)
{
	if (spriteA >= this->sprites.size() || spriteB >= this->sprites.size())
		return false;
	else {
		AllegroSprite * temp = this->sprites[spriteA];
		this->sprites[spriteA] = this->sprites[spriteB];
		this->sprites[spriteB] = temp;
		return true;
	}
}

unsigned int AllegroAnimation::draw(float x, float y, FlipSprite mode)
{
	switch (mode){
	case FlipSprite::None:	this->sprites[counter]->draw(x, y);		break;
	case FlipSprite::Vertically:	this->sprites[counter]->drawVerticallyMirrored(x, y);	break;
	case FlipSprite::Horizontally:	this->sprites[counter]->drawHorizontallyMirrored(x, y); break;
	}
	unsigned int retCounter = counter;
	this->updateCounter();
	return retCounter;
}

unsigned int AllegroAnimation::draw(float x, float y, float angle, FlipSprite mode)
{
	switch (mode) {
	case FlipSprite::None:	this->sprites[counter]->draw(x, y, angle);		break;
	case FlipSprite::Vertically:	this->sprites[counter]->drawVerticallyMirrored(x, y, angle);	break;
	case FlipSprite::Horizontally:	this->sprites[counter]->drawHorizontallyMirrored(x, y, angle); break;
	}
	unsigned int retCounter = counter;
	this->updateCounter();
	return counter;
}

unsigned int AllegroAnimation::draw(float x, float y, float height, float width, FlipSprite mode)
{
	switch (mode) {
	case FlipSprite::None:	this->sprites[counter]->draw(x, y, height, width);		break;
	case FlipSprite::Vertically:	this->sprites[counter]->drawVerticallyMirrored(x, y, height, width);	break;
	case FlipSprite::Horizontally:	this->sprites[counter]->drawHorizontallyMirrored(x, y, height, width); break;
	}
	unsigned int retCounter = counter;
	this->updateCounter();
	return counter;
}

bool AllegroAnimation::draw(float x, float y, unsigned int pos, FlipSprite mode)
{
	if (pos >= this->sprites.size())
		return false;
	else{
		switch (mode) {
		case FlipSprite::None:	this->sprites[pos]->draw(x, y);		break;
		case FlipSprite::Vertically:	this->sprites[pos]->drawVerticallyMirrored(x, y);	break;
		case FlipSprite::Horizontally:	this->sprites[pos]->drawHorizontallyMirrored(x, y); break;
		}
		this->counter = pos;
		this->updateCounter();
		return true;
	}
}

bool AllegroAnimation::draw(float x, float y, float angle, unsigned int pos, FlipSprite mode)
{
	if (pos >= this->sprites.size())
		return false;
	else {
		switch (mode) {
		case FlipSprite::None:	this->sprites[pos]->draw(x, y, angle);		break;
		case FlipSprite::Vertically:	this->sprites[pos]->drawVerticallyMirrored(x, y, angle);	break;
		case FlipSprite::Horizontally:	this->sprites[pos]->drawHorizontallyMirrored(x, y, angle); break;
		}
		this->counter = pos;
		this->updateCounter();
		return true;
	}
}

bool AllegroAnimation::draw(float x, float y, float height, float width, unsigned int pos, FlipSprite mode)
{
	if (pos >= this->sprites.size())
		return false;
	else {
		switch (mode) {
		case FlipSprite::None:	this->sprites[pos]->draw(x, y, height, width);		break;
		case FlipSprite::Vertically:	this->sprites[pos]->drawVerticallyMirrored(x, y, height, width);	break;
		case FlipSprite::Horizontally:	this->sprites[pos]->drawHorizontallyMirrored(x, y, height, width); break;
		}
		this->counter = pos;
		this->updateCounter();
		return true;
	}
}
