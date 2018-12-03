#include "UI.h"

#define TitleUIBackground "Images\\BackgroundMenu.png"

#define FontPath "Font\\TitleFont.ttf"

#define FontSize 50

#define ButtonY(w) (w * 0.75)
#define ButtonX(h,pos) (pos * (0.5) * h)
#define ButtonHeight(h) (h * 0.1)
#define ButtonWidth(w) (w * 0.8)
#define ButtonColor "white"

#define SinglePlayerText "Play"

#define ExitX(w) (w * 0.8)
#define ExitY(h) (h * 0.1)
#define ExitW(w) (w * 0.3)
#define ExitH(h) (h * 0.1)
#define ExitText "Exit"

#define ControlX(w) (w *0.2)
#define ControlY(h) (h *0.1)
#define ControlWidth(w) (w*0.3)
#define ControlHeight(h) (h*0.1)
#define ControlText "Controls"


#define ModeSelectionBackground ( "Images\\BackgroundControl.png")
#define GameOverBackground ("Images\\GameOverBackground.png")
#define WonBackground ("Images\\WonBackground.png")

#define BackX(w) (ControlX(w))
#define BackY(h) (ControlY(h))
#define BackHeight(h) (ControlHeight(h))
#define BackWidth(w) (2 * ControlWidth(w))
#define BackText "Go back"


#define InputY(h) (h *0.5)
#define InputWidth(w) (w*0.3)
#define InputHeight(h) (h *0.2)

#define ConnectY(h) (h * 0.8)
#define ConnectWidth(w) (w *0.2)
#define ConnectHeight(h) (h*0.1)

#define PlayAgainText "Play Again"


#define InstructionX(w) (w *0.5)
#define InstructionY(h,pos) (h*0.2*pos)
#define InstructionWidth(w) (w)
#define InstructionHeight(h) (h*0.2)
#define InstructionText1 "El Jugador 1 se mueve con 'A' y 'S', salta con 'W' y ataca con 'C'"
#define Inst1ID 32




///////////////////////////////////////////////////////////////////////////////////7
#define WonSoundtrack "Music\\Soundtrack\\DayManWin.wav"
#define TitleSoundtrack "Music\\Soundtrack\\intro.wav"
#define GameOverSoundTrack "Music\\Soundtrack\\Night Man.ogg"
#define InstructionsSoundtrack "Music\\Soundtrack\\Night Man.ogg"


UI::UI(AllegroWindow & window)
	:window(window) {}

UI::~UI()
{
	if (layout != nullptr)
		delete layout;
}

int UI::run(void * eventH, void * data)
{
	int retValue = -1;
	window.insertLayout(*this->layout);
	if (this->sound != nullptr)
		this->sound->play();

	AllegroEventHandler& eventHandler = *(AllegroEventHandler *)eventH;

	do {
		eventHandler.getEvent();
		if (eventHandler.isThereEvent()) {
			AllegroEvent ev = eventHandler.ObtainEvent();
			switch (ev.getType())
			{
			case EventType::DisplayClose:
				retValue = ExitID;	break;
			case EventType::MouseDown:

				for (unsigned int& id : pertinetIDs)
					if (this->boxes[id]->getType() == BoxType::Button && this->boxes[id]->click(ev.getX(), ev.getY(), ev.getTimestamp()))
						retValue = id;

			case EventType::Timer:
				this->window.update();
				break;
			}
		}
	} while (retValue == -1);

	window.deleteLayout();
	if (this->sound != nullptr)
		this->sound->stop();



	return retValue;
}





TitleUI::TitleUI(AllegroSoundFactory & soundF, AllegroWindow & window, AllegroFontFactory& fontF)
	:UI(window)
{
	
	
	this->font = fontF.create(FontPath, FontSize, 0);

	this->sound = soundF.create(TitleSoundtrack, PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, TitleUIBackground, LayoutDrawMode::Slow);
	this->boxes.addBox(new AllegroWrittenBox(w*0.2, h*0.3,  "", font, colorF.create("white"), 3213));


	// SinglePlayerButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), SinglePlayerText,
		font, colorF.create(ButtonColor), SinglePlayerID));
	this->boxes[SinglePlayerID]->setBackgroundColor(colorF.create("black"));
	this->boxes[SinglePlayerID]->setBorderColor(colorF.create("white"));
	this->boxes[SinglePlayerID]->setBorderThickness(1);

	//// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);

	//ControlsButton

	this->boxes.addBox(new AllegroButton(ControlX(w) - (ControlWidth(w) / 2.0), ControlY(h), ControlWidth(w), ControlHeight(h), ControlText,
		font, colorF.create(ButtonColor), ControlID));
	this->boxes[ControlID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ControlID]->setBorderColor(colorF.create("white"));
	this->boxes[ControlID]->setBorderThickness(1);


	this->layout->addBox(this->boxes[SinglePlayerID]);
	this->layout->addBox(boxes[3213]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[ControlID]);

	pertinetIDs = { SinglePlayerID ,ExitID ,ControlID };
}



GameOverUI::GameOverUI(AllegroSoundFactory & soundF, AllegroWindow & window, AllegroFontFactory& fontF)
	:UI(window)
{
	this->font = fontF.create(FontPath, FontSize, 432);

	this->sound = soundF.create(GameOverSoundTrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, GameOverBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), PlayAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("black"));
	
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));


	this->layout->addBox(this->boxes[PlayAgainID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { PlayAgainID ,ExitID };
}

WonUI::WonUI(AllegroSoundFactory & soundF, AllegroWindow & window, AllegroFontFactory& fontF)
	:UI(window)
{
	this->font = fontF.create(FontPath, FontSize, 4345);


	this->sound = soundF.create(WonSoundtrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, WonBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), PlayAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("black"));
	this->boxes[PlayAgainID]->setBorderColor(colorF.create("white"));
	this->boxes[PlayAgainID]->setBorderThickness(1);
	
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);


	this->layout->addBox(this->boxes[PlayAgainID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { PlayAgainID ,ExitID };
}

InstructionsUI::InstructionsUI(AllegroSoundFactory & soundF, AllegroWindow & window, AllegroFontFactory& fontF)
	:UI(window)
{
	this->font = fontF.create(FontPath, FontSize, 43445);

	this->sound = soundF.create(InstructionsSoundtrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// Button
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("black"));
	this->boxes[BackID]->setBorderColor(colorF.create("white"));
	this->boxes[BackID]->setBorderThickness(1);

	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);

	// Controles P1

	this->boxes.addBox(new AllegroWrittenBox(InstructionX(w) - (InstructionWidth(w) / 2.0), InstructionY(h, 2), InstructionWidth(w), InstructionHeight(h),
		"", font, colorF.create("white"), Inst1ID));



	this->layout->addBox(this->boxes[BackID]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[Inst1ID]);

	pertinetIDs = { BackID,ExitID };
}

