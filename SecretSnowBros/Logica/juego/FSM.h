#pragma once

#include <functional>


using namespace std::placeholders;

class FSM;
using tempType = int (FSM::*)(void *);




#define TX(x) (static_cast<tempType>(&FSM::x))


enum class stateTypes {
	MenuTitleState, ControlState, ModeSelectionState, OnlineConfigState, WaitingToJoinState, WatingToCreateState, JoinMenuState, GameState, GameOverState, WonState, Exit
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
//
//	UI * titleMenu = nullptr;
//	UI * modeSelectionMenu = nullptr;
//	UI * onlineConfigMenu = nullptr;
//	UI * waitingToJoinMenu = nullptr;
//	UI * waitingToCreateMenu = nullptr;
//	UI * instructionMenu = nullptr;
//	UI * joinMenu = nullptr;
//	UI * gameOverMenu = nullptr;
//	UI * wonMenu = nullptr;
//	Game  * game = nullptr;
//
//	int runTitleMenu(void* data);
//	int runModeSelectionMenu(void * data);
//	int runOnlineConfigMenu(void * data);
//	int runWaitingToJoinMenu(void * data);
//	int runWaitingToCreateMenu(void* data);
//	int runInstructionMenu(void * data);
//	int runJoinMenu(void * data);
//	int runGameOverMenu(void * data);
//	int runWonMenu(void * data);
//	int runGame(void*data);
//
//	AllegroEventHandler * eventH = nullptr;
//
//
//
//
//	const fsmCell fsmTable[11][15] = { //       SinglePlayerID										ExitID											BackID								PlayAgainID											LeaveID														WonGameID											LostGameID
//		/*MenuTitleState*/{ { stateTypes::ModeSelectionState,TX(runGame) },{ stateTypes::Exit,nullptr },{ stateTypes::MenuTitleState,nullptr },{ stateTypes::MenuTitleState,nullptr },{ stateTypes::MenuTitleState ,nullptr },{ stateTypes::MenuTitleState ,nullptr },{ stateTypes::MenuTitleState ,nullptr } },				//MenuTitleState
//		/*GameState*/{ { stateTypes::GameState ,nullptr },{ stateTypes::GameState,nullptr },{ stateTypes::GameState,nullptr },{ stateTypes::GameState,nullptr },{ stateTypes::GameState ,nullptr },{ stateTypes::WonState ,TX(runWonMenu) } ,{ stateTypes::GameOverState ,TX(runGameOverMenu) } },		//GameState 
//		/*GameOverState*/{ { stateTypes::GameOverState,nullptr },{ stateTypes::Exit,nullptr },{ stateTypes::GameOverState,nullptr },{ stateTypes::GameState,TX(runGame) },{ stateTypes::MenuTitleState ,TX(runTitleMenu) },{ stateTypes::GameOverState ,nullptr },{ stateTypes::GameOverState ,nullptr } },					//GameOverState
//		/*WonState*/{ { stateTypes::WonState,nullptr },{ stateTypes::Exit,nullptr },{ stateTypes::WonState,nullptr },{ stateTypes::GameState,TX(runGame) },{ stateTypes::MenuTitleState ,TX(runTitleMenu) },{ stateTypes::WonState ,nullptr },{ stateTypes::WonState ,nullptr } },						//WonState
//		/*Exit*/{ { stateTypes::Exit,nullptr },{ stateTypes::Exit,nullptr },{ stateTypes::Exit, nullptr },{ stateTypes::Exit ,nullptr },{ stateTypes::Exit ,nullptr },{ stateTypes::Exit ,nullptr },{ stateTypes::Exit ,nullptr } }							//Exit
//	};
//};
//
