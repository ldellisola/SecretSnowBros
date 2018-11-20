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
	StillWalk, StillJump, WalkingLeft, WalkingRight, Jumping, Shooting, Falling, Frozen, Waiting, Carried
};

#ifdef _DEBUG
const std::string _BeingDir[] = { "Left", "Right" };
const std::string _BeingState[] = { "StillWalk","StillJump","Walking","Jumping","Shooting","Falling","Frozen","Waiting","Carried" };
#endif // _DEBUG




class Being :public Slider,public Jumper
{
public:
	Being(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID);
	virtual ~Being(){}

	//uint16_t getX() { return x; }
	//uint16_t getY() { return y; }
	uint16_t getID() { return ID; }
	bool isAlive() { return (lives > 0 ? true:false); }
	virtual void kill();
	//void setMovement(BeingDirection dir);
	virtual void setState(BeingState state);
	
	virtual void update(void * ptr);
	uint16_t getLives() { return lives; }
	virtual void collition(Projectile * proy);

	//BeingDirection getDirection() { return dir; }
	//BeingState getVerticalState() { return verticalState; }
	//BeingState getHorizontalState() { return horizontalState; }


protected:
	//uint16_t x, y;
	
	//void resetVerticalTicks();
	//void resetHorizontalTicks();
	//void updateVerticalTicks();
	//void updateHorizontalTicks();

	//void setHorizontalState(BeingState state);
	//void setVerticalState(BeingState state);
	//uint16_t getVerticalTicks() { return verticalMovementTick; }
	//uint16_t getHorizontalTicks() { return horizontalMovementTick; }

	uint16_t lives;
	const uint16_t ID;
	//const uint16_t maxJumpTick, maxWalkTick, maxFallTicks;




private:
	const uint16_t  xStart;
	const uint16_t yStart;
	//BeingDirection dir;
	//uint16_t verticalMovementTick, horizontalMovementTick ;
	//BeingState verticalState, horizontalState;
};
