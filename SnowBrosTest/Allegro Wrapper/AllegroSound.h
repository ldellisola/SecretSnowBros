#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include "AllegroException.h"
#include <string>
#include <vector>

enum class PlayMode
{
	Once = ALLEGRO_PLAYMODE_ONCE,Loop = ALLEGRO_PLAYMODE_LOOP, Bidir = ALLEGRO_PLAYMODE_BIDIR
};

class AllegroSound;

class AllegroSoundFactory
{
public:
	AllegroSoundFactory();
	~AllegroSoundFactory();

	AllegroSound * create(std::string fileName, PlayMode playMode, unsigned int ID, float speed = 1, float gain = 1.0, float pan = 0.0);
	AllegroSound * recover(unsigned int ID);
	bool destroy(unsigned int ID);
	bool destroy(AllegroSound * sound);

private:
	std::vector<AllegroSound *> sounds;

};


class AllegroSound
{
public:
	AllegroSound(std::string fileName, PlayMode playMode, unsigned int ID, float speed = 1, float gain = 1.0, float pan = 0.0);
	
	void play();
	void playAtSpeed(float speed);
	void playAtPan(float pan);
	void playAtGain(float gain);
	void stop();

	void setSpeed(float speed) { this->speed = speed; }
	float getSpeed() { return speed; }
	void setGain(float gain) { this->gain = gain; }
	float getGain() { return gain; }
	void setPan(float pan) { this->pan = pan; }
	float getPan() { return pan; }

	unsigned int getID() { return this->ID; }

	friend bool AllegroSoundFactory::destroy(unsigned int ID);
	friend bool AllegroSoundFactory::destroy(AllegroSound * sound);

private:
	ALLEGRO_SAMPLE * sample = nullptr;
	ALLEGRO_SAMPLE_ID playID;
	unsigned int ID = NAN;
	float gain,pan,speed;
	ALLEGRO_PLAYMODE playMode;

	~AllegroSound();
};




