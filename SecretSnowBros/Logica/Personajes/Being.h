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

#ifdef _DEBUG
const std::string _BeingDir[] = { "Left", "Right" };
const std::string _BeingState[] = { "StillWalk","StillJump","Walking","Jumping","Shooting","Falling","Frozen","Waiting","Inmune" };
#endif // _DEBUG




class Being :public Slider,public Jumper
{
public:

	Being(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID);
	virtual ~Being(){}

	uint16_t getID() { return ID; }
	bool isAlive() { return (lives > 0 ? true:false); }
	virtual void kill();
	virtual void revive();
	virtual void setState(BeingState state);
	virtual BeingState getState();
	
	virtual void update(void * ptr);
	uint16_t getLives() { return lives; }
	virtual void collition(Projectile * proy);

	//CAncer
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
