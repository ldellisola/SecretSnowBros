#include "FSM.h"

void FSM::setUp(AllegroWindow& window, AllegroSoundFactory& soundF) {

}

int FSM::runTitleMenu(void* data){
	titleMenu->run(this->eventH,data);
	return 0;
}

int FSM::runInstructionMenu(void * data) {
	instructionMenu->run(this->eventH, data);
	return 0;
}

int FSM::runGameOverMenu(void * data) {
	gameOverMenu->run(this->eventH, data);
	return 0;
}

int FSM::runWonMenu(void * data) {
	wonMenu->run(this->eventH, data);
	return 0;
}

int FSM::runGame(void*data) {
	return 0;
}

int FSM::runExit(void*data) {
	return 0;
}
