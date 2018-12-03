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

	game->loadMaps(stringtoworld(getNames("Maps/map", ".csv", 10)));
	switch (game->run(data)){
	case KeepReturn::Exit:
		return ExitID;
	case KeepReturn::PlayersDead:
		return LostGameID;
	case KeepReturn::LevelWon:
		return WonGameID;
	}
	return 0;
	
}

int FSM::runExit(void*data) {
	return 0;
}


std::vector<std::string> getNames(std::string path, std::string ext, int quantinty)
{
	std::vector<std::string> names(quantinty, " ");
	std::vector<World> maps;
	for (int i = 0; i < quantinty; i++) {
		names[i] = path + std::to_string(i + 1) + ext;

	}
	return names;
}

std::vector<World> stringtoworld(std::vector<std::string> files) {
	std::vector<World> maps;
	for (int i = 0; i < 10; i++) {
		World map(files[i]);
		maps.push_back(map);
	}
	return maps;
}