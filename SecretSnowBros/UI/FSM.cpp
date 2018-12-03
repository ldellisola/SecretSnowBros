#include "FSM.h"

FSM::~FSM()
{
	if (this->wonMenu != nullptr)
		delete wonMenu;
	if (this->instructionMenu != nullptr)
		delete instructionMenu;
	if (this->gameOverMenu != nullptr)
		delete gameOverMenu;
	if (this->titleMenu != nullptr)
		delete titleMenu;
}

void FSM::setUp(AllegroWindow& window, AllegroSoundFactory& soundF,Game& game) {
	if (this->wonMenu == nullptr)
		wonMenu = new WonUI(soundF, window, fontF);
	if (this->instructionMenu == nullptr)
		instructionMenu = new InstructionsUI(soundF, window, fontF);
	if (this->gameOverMenu == nullptr)
		gameOverMenu = new GameOverUI(soundF, window, fontF);
	if (this->titleMenu == nullptr)
		titleMenu = new TitleUI(soundF, window, fontF);

	this->game = &game;
}

int FSM::runTitleMenu(void* data){
	
	return titleMenu->run(this->eventH, data);
}

int FSM::runInstructionMenu(void * data) {
	
	return instructionMenu->run(this->eventH, data);
}

int FSM::runGameOverMenu(void * data) {
	
	return gameOverMenu->run(this->eventH, data);
}

int FSM::runWonMenu(void * data) {
	
	return wonMenu->run(this->eventH, data);
}

int FSM::runGame(void*data) {


	switch (game->run(data))
	{
	case KeepReturn::Exit:
		return ExitID;
	case KeepReturn::PlayersDead:
		return LostGameID;
	case KeepReturn::LevelWon:
		return WonGameID;
	}

	
}

int FSM::runExit(void*data) {
	return 0;
}
