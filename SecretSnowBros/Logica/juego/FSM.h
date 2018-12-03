#pragma once
#include <functional>
#include "Game.h"

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

//class FSM
//{
//public:
//	FSM(AllegroEventHandler * eventHandler) :state(stateTypes::MenuTitleState), eventH(eventHandler) {}
//	~FSM();
//
//	void setUp(AllegroWindow& window, AllegroSoundFactory& soundF);
//
//	int cycle(unsigned int ev, void * userData)
//	{
//		fsmCell temp = fsmTable[static_cast<unsigned int>(state)][static_cast<unsigned int>(ev)];
//
//		auto f = std::bind(temp.action, this, userData);
//		int temp2 = f();
//		state = temp.nextState;
//		return temp2;
//	}
//private:
//	stateTypes state;
//
//	UI * titleMenu = nullptr;
//	UI * instructionMenu = nullptr;
//	UI * gameOverMenu = nullptr;
//	UI * wonMenu = nullptr;
//	Game  * game = nullptr;
//
//	int runTitleMenu(void* data);
//	int runInstructionMenu(void * data);
//	int runGameOverMenu(void * data);
//	int runWonMenu(void * data);
//	int runGame(void*data);
//	int runExit(void*data);
//
//
//	AllegroEventHandler * eventH = nullptr;
//
//	const fsmCell fsmTable[6][7] = {	//instructionsButton											//playButton								//exitButton									//backScreenButton											//WonGame									//loseGame										//playAgainButton
//		/*PrincipalScreen*/			{ { stateTypes::InstructionScreen, TX(runInstructionMenu)}, { stateTypes::GameScreen, TX(runGame) },		{ stateTypes::Exit, TX(runExit) },				{ stateTypes::PrincipalScreen, nullptr },				{ stateTypes::PrincipalScreen, nullptr },		{ stateTypes::PrincipalScreen, nullptr },		{ stateTypes::PrincipalScreen, nullptr } },
//		/*InstructionScreen*/		{ { stateTypes::InstructionScreen, nullptr },				{ stateTypes::InstructionScreen, nullptr },		{ stateTypes::InstructionScreen, nullptr },		{ stateTypes::PrincipalScreen, TX(runTitleMenu) },		{ stateTypes::InstructionScreen, nullptr },		{ stateTypes::InstructionScreen, nullptr },		{ stateTypes::InstructionScreen, nullptr } },
//		/*GameScreen*/				{ { stateTypes::GameScreen, nullptr },						{ stateTypes::GameScreen, nullptr },			{ stateTypes::GameScreen, nullptr },			{ stateTypes::GameScreen, nullptr },					{ stateTypes::Won, TX(runWonMenu) },			{ stateTypes::GameOver, TX(runGameOverMenu) },	{ stateTypes::GameScreen, nullptr } },
//		/*GameOver*/				{ { stateTypes::GameOver, nullptr },						{ stateTypes::GameOver, nullptr },				{ stateTypes::Exit, TX(runExit) },				{ stateTypes::GameOver, nullptr },						{ stateTypes::GameOver, nullptr },				{ stateTypes::GameOver, nullptr },				{ stateTypes::GameScreen, TX(runGame) } },
//		/*Won*/						{ { stateTypes::Won, nullptr },								{ stateTypes::Won, nullptr },					{ stateTypes::Exit, TX(runExit) },				{ stateTypes::Won, nullptr },							{ stateTypes::Won, nullptr },					{ stateTypes::Won, nullptr },					{ stateTypes::GameScreen, TX(runGame) } },
//		/*Exit*/					{ { stateTypes::Exit, nullptr },							{ stateTypes::Exit, nullptr },					{ stateTypes::Exit, nullptr },					{ stateTypes::Exit, nullptr },							{ stateTypes::Exit, nullptr },					{ stateTypes::Exit, nullptr },					{ stateTypes::Exit, nullptr } },
//	};
//};

