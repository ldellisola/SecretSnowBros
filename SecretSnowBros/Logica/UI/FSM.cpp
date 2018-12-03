#include "FSM.h"

void FSM::setUp(AllegroWindow& window, AllegroSoundFactory& soundF) {

}

int FSM::runTitleMenu(void* data){
	titleMenu->run;
	return 0;
}

int FSM::runInstructionMenu(void * data) {
	instructionMenu->run;
	return 0;
}

int FSM::runGameOverMenu(void * data) {
	gameOverMenu->run;
	return 0;
}

int FSM::runWonMenu(void * data) {
	wonMenu->run;
	return 0;
}

int FSM::runGame(void*data) {
	return 0;
}

int FSM::runExit(void*data) {
	return 0;
}
