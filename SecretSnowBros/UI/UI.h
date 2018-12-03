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
	TitleUI(AllegroSoundFactory & soundF,AllegroWindow& window);
	~TitleUI() {}
};

class ModeSelectionUI : public UI {
public:
	ModeSelectionUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~ModeSelectionUI() {}
};

class OnlineConfigUI : public UI {
public:
	OnlineConfigUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~OnlineConfigUI() {}
};

class WaitingToJoinUI : public UI {
public:
	WaitingToJoinUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~WaitingToJoinUI() {}
	int run(void * eventH,void *data) {
		window.setDifferentSystemMouseCursor(CursorSprite::Busy);
		int temp = UI::run(eventH, data);
		window.setDifferentSystemMouseCursor(CursorSprite::Default);
		return temp;
	}
};

class WaitingToCreateUI : public UI {
public:
	WaitingToCreateUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~WaitingToCreateUI() {}
	int run(void * eventH,void * data) {
		window.setDifferentSystemMouseCursor(CursorSprite::Busy);
		int temp = UI::run(eventH,data );
		window.setDifferentSystemMouseCursor(CursorSprite::Default);
		return temp;
	}
};

class JoinMenuUI : public UI {
public:
	JoinMenuUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~JoinMenuUI() {}
	int run(void * eventH, void* data);
private:
	std::string ip;
	bool isIPValid(std::string ip);
};

class GameOverUI : public UI {
public:
	GameOverUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~GameOverUI() {}
};

class WonUI : public UI {
public:
	WonUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~WonUI() {}
};

class InstructionsUI : public UI {
public:
	InstructionsUI(AllegroSoundFactory & soundF, AllegroWindow& window);
	~InstructionsUI() {}
};