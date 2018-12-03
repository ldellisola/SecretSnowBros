#pragma once
#include <functional>
#include "Game.h"
#include "AllwBasics\AllegroEvent.h"
#include "AllwBasics\AllegroSound.h"
#include "AllwBasics\AllegroWindow.h"


using namespace std::placeholders;

class FSM;
using tempType = int (FSM::*)(void *);

#define TX(x) (static_cast<tempType>(&FSM::x))

enum class stateTypes {
	PrincipalScreen, InstructionScreen, GameScreen, GameOver, Won , Exit,
};

struct fsmCell
{
	stateTypes nextState;
	int(FSM::*action)(void *);
};

class FSM
{
public:
	FSM(AllegroEventHandler * eventHandler) :state(stateTypes::PrincipalScreen), eventH(eventHandler) {}
	~FSM();

