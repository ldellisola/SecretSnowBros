#include "AllegroSound.h"



AllegroSound::AllegroSound(std::string fileName, PlayMode playMode, unsigned int ID, float speed, float gain, float pan)
{
	this->sample = al_load_sample(fileName.c_str());
	if (this->sample == nullptr)
		throw InvalidLoadException();
	this->gain = gain;
	this->pan = pan;
	this->speed = speed;
	this->playMode = (ALLEGRO_PLAYMODE) playMode;
	this->ID = ID;
}

void AllegroSound::play()
{
	al_play_sample(this->sample, this->gain, this->pan, this->speed, this->playMode, &playID);
}

void AllegroSound::playAtSpeed(float speed)
{
	if (this->sample != nullptr) {
		al_play_sample(this->sample, this->gain, this->pan, speed, this->playMode, &playID);
	}
}

void AllegroSound::playAtPan(float pan)
{
	if (this->sample != nullptr) {
		al_play_sample(this->sample, this->gain, pan, this->speed, this->playMode, &playID);
	}
}

void AllegroSound::playAtGain(float gain)
{
	if (this->sample != nullptr) {
		al_play_sample(this->sample, gain, this->pan, this->speed, this->playMode, &playID);
	}
}

void AllegroSound::stop()
{
	al_stop_sample(&this->playID);
}

AllegroSound::~AllegroSound()
{
	if (this->sample != nullptr)
		al_destroy_sample(this->sample);
	
}



AllegroSoundFactory::AllegroSoundFactory()
{
}

AllegroSoundFactory::~AllegroSoundFactory()
{
}

AllegroSound * AllegroSoundFactory::create(std::string fileName, PlayMode playMode, unsigned int ID, float speed , float gain, float pan)
{
	
	AllegroSound * temp = new AllegroSound(fileName, playMode, ID, speed, gain, pan);
	this->sounds.push_back(temp);
	al_reserve_samples(int(this->sounds.size()));
	return temp;
}

AllegroSound * AllegroSoundFactory::recover(unsigned int ID)
{
	for (int i = 0; i < sounds.size(); i++) {
		if (sounds[i]->getID() == ID)
			return sounds[i];
	}
	return nullptr;
}

bool AllegroSoundFactory::destroy(unsigned int ID)
{
	int i;
	AllegroSound * temp = nullptr;
	for (i = 0; i < sounds.size(); i++) {
		if (sounds[i]->getID() == ID)
			temp = sounds[i];
	}
	i--;
	if (temp != nullptr) {
		sounds.erase(sounds.begin() + i);
		delete temp;
		al_reserve_samples(int(this->sounds.size()));
		return true;
	}
	return false;
}

bool AllegroSoundFactory::destroy(AllegroSound * sound)
{
	int i;
	bool kill = false;
	for (i = 0; i < sounds.size(); i++) {
		if (sounds[i] == sound)
			kill = true;
	}
	i--;
	if (kill) {
		sounds.erase(sounds.begin() + i);
		al_reserve_samples(int(this->sounds.size()));
		delete sound;
		return true;
	}
	return false;
}
