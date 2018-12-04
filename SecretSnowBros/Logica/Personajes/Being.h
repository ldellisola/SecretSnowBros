#pragma once
#include <stdint.h>
#include <memory>
#include "Logica/juego/Cmap.h"
#include "Logica/Personajes/Base Classes/Jumper.h"
#include "Logica/Personajes/Base Classes/Slider.h"
#include "Logica/Personajes/Projectiles/Projectile.h"

enum class BeingDirection
{
   Left, Right
};

enum class BeingState
{
	StillWalk, StillJump, WalkingLeft, WalkingRight, Jumping, Shooting, Falling, Frozen, Waiting, Inmune
};


/*
	This is the Base class for almost all moving classes.It allows its child to live and die, to move in all directions and
	to have an unique ID. It also allows the child to collide with projectiles
*/

class Being :public Slider,public Jumper
{
public:

	Being(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID);
	virtual ~Being(){}

	uint16_t getID() { return ID; }
	bool isAlive() { return (lives > 0 ? true:false); }

	// It kills the Being
	virtual void kill();

	// It revives the Being
	virtual void revive();

	// It sets the Slider and Jumper states according to the BeingState
	virtual void setState(BeingState state);

	// It returns the current state of the Being
	virtual BeingState getState();
	
	// It updates the position of the being. It takes a pinter to the World class
	virtual void update(void * ptr);

	uint16_t getLives() { return lives; }

	virtual void collition(Projectile * proy);

	virtual bool isInmune() { return false; }
	virtual bool isCarried() { return false; }
	virtual void setCarry(bool){ }
	virtual void setInmune(bool) {}
	virtual void updateScore(uint16_t value){}


protected:

	uint16_t lives;
	const uint16_t ID;


	BeingState beingState;
	const uint16_t xStart;
	const uint16_t yStart;
};
