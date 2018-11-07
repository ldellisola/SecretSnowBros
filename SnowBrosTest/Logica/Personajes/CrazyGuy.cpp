#include "CrazyGuy.h"

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*4)	// 200ms
#define FallTicks (ms50*6)	// 300ms
#define StillTicks (ms50*10)	// 500ms

#define PointsAwarded (10)

CrazyGuy::CrazyGuy(uint32_t x, uint32_t y, uint32_t ID)
	:Monster (JumpTicks,WalkTicks,StillTicks,FallTicks,x,y,ID, PointsAwarded)
{
	this->lives = 1;


}

CrazyGuy::~CrazyGuy()
{
}
void CrazyGuy::chooseAction(void * ptr)
{
	if (getHorizontalState() == BeingState::StillWalk && getVerticalState() == BeingState::StillJump) {
		next();
	}
}
void CrazyGuy::next() {
	uint16_t probs = rand()%100;
	if (probs < 75) {
		this->futureDirections.push_back(BeingState::Walking);
		this->futureDirections.push_back(BeingState::StillWalk);
	}
	else if (probs < 83)
	{
		if (getDirection() == BeingDirection::Left) 
			setMovement(BeingDirection::Right);
		else if(getDirection() == BeingDirection::Right)
			setMovement(BeingDirection::Left);

		this->futureDirections.push_back(BeingState::Walking);
		this->futureDirections.push_back(BeingState::StillWalk);
	}
	else if (probs < 91) {
		this->futureDirections.push_back(BeingState::Jumping);
		this->futureDirections.push_back(BeingState::StillJump);
	}
	else {
		this->futureDirections.push_back(BeingState::Waiting);
	}
}

