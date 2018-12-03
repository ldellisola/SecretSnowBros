#pragma once

#include "AllwUI\AllegroLayout.h"
#include "AllwUI\WrittenBox.h"
#include "AllwUI\WritableBox.h"
#include "AllwUI\AllegroButton.h"
#include "AllwBasics\AllegroSound.h"
#include "AllwBasics\AllegroEvent.h"
#include "AllwBasics\AllegroWindow.h"
#include "AllwInit\AllegroFactory.h"

enum UIIDs
{
	ControlID, SinglePlayerID, ExitID,   BackID, WonGameID, LostGameID, PlayAgainID, 
};

class UI
{
public:
	UI(AllegroWindow& window);
	~UI();
	virtual int run(void * eventH, void * data);
protected:

	
	AllegroLayout * layout = nullptr;
	BoxArray boxes;
	AllegroFont * font = nullptr;
	AllegroSound * sound = nullptr;
	AllegroWindow& window;
	std::vector<unsigned int> pertinetIDs;

};

class TitleUI :public UI {
public:
	TitleUI(AllegroSoundFactory & soundF,AllegroWindow& window, AllegroFontFactory& fontF);
	~TitleUI() {}
};


class GameOverUI : public UI {
public:
	GameOverUI(AllegroSoundFactory & soundF, AllegroWindow& window, AllegroFontFactory& fontF);
	~GameOverUI() {}
};

class WonUI : public UI {
public:
	WonUI(AllegroSoundFactory & soundF, AllegroWindow& window, AllegroFontFactory& fontF);
	~WonUI() {}
};

class InstructionsUI : public UI {
public:
	InstructionsUI(AllegroSoundFactory & soundF, AllegroWindow& window, AllegroFontFactory& fontF);
	~InstructionsUI() {}
};