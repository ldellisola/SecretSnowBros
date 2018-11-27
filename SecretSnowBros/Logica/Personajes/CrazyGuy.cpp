#include "CrazyGuy.h"

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*4)	// 200ms
#define FallTicks (ms50*6)	// 300ms
#define StillTicks (ms50*10)	// 500ms

#define PointsAwarded (10)

CrazyGuy::CrazyGuy(uint32_t x, uint32_t y, uint32_t ID)
	:Monster (JumpTicks,WalkTicks,StillTicks,FallTicks,x,y,ID, PointsAwarded)
#ifdef _DEBUG
	,Logger("Logs/Crazy Guy ID -"+ std::to_string(ID),true)
#endif // _DEBUG

{
	this->lives = 1;
}


void CrazyGuy::chooseAction(void * ptr)
{
	if (getHorizontalState() == HorizontalState::Still && getVerticalState() == VerticalState::Still) {

#ifdef _DEBUG
		log("Selecting new state");
#endif // _DEBUG
		next();
	}
}
void CrazyGuy::next() {
	uint16_t probs = rand()%100;
	//if (probs < 100) {
	//	this->futureDirections.push(BeingState::Waiting);//debug
	//}
	/*else */if (probs < 75) {
#ifdef _DEBUG
		log("New state elected: Walking Same Direction");
#endif // _DEBUG
		if (getHorizontalDir() == HorizontalDirection::Left)
			this->futureDirections.push(BeingState::WalkingLeft);
		else if (getHorizontalDir() == HorizontalDirection::Right)
			this->futureDirections.push(BeingState::WalkingRight);
		this->futureDirections.push(BeingState::StillWalk);
	}
	else if (probs < 83)
	{
#ifdef _DEBUG
		log("New state elected: Walking other Direction");
#endif // _DEBUG
		if (getHorizontalDir() == HorizontalDirection::Left) 
			this->futureDirections.push(BeingState::WalkingRight);
		else if(getHorizontalDir() == HorizontalDirection::Right)
			this->futureDirections.push(BeingState::WalkingLeft);
		this->futureDirections.push(BeingState::StillWalk);
	}
	else if (probs < 91) {
#ifdef _DEBUG
		log("New state elected: Jumping");
#endif // _DEBUG
		this->futureDirections.push(BeingState::Jumping);
		this->futureDirections.push(BeingState::StillJump);
	}
	else {
#ifdef _DEBUG
		log("New state elected: Waiting");
#endif // _DEBUG
		this->futureDirections.push(BeingState::Waiting);
	}
}
