#include "UI.h"

#define TitleUIBackground "background.jpg"

#define FontPath "font.ttf"
#define FontSize 20

#define ButtonY(w) (w * 0.75)
#define ButtonX(h,pos) (pos * (0.25) * h)
#define ButtonHeight(h) (h * 0.1)
#define ButtonWidth(w) (w * 0.3)
#define ButtonColor "white"

#define SinglePlayerText "Single player"

#define DoublePlayerText "Dual Player"

#define ExitX(w) (w * 0.9)
#define ExitY(h) (h * 0.1)
#define ExitW(w) (w * 0.1)
#define ExitH(h) (h * 0.1)
#define ExitText "Exit"

#define ControlX(w) (w *0.1)
#define ControlY(h) (h *0.1)
#define ControlWidth(w) (w*0.1)
#define ControlHeight(h) (h*0.1)
#define ControlText "Controls"


#define ModeSelectionBackground (TitleUIBackground)
#define LocalText "Local mode"

#define OnlineText "Online"

#define BackX(w) (ControlX(w))
#define BackY(h) (ControlY(h))
#define BackHeight(h) (ControlHeight(h))
#define BackWidth(w) (2 * ControlWidth(w))
//#define BackID (12)
#define BackText "Go back"

#define OnlineConfigBackground (TitleUIBackground)

#define JoinText "Join Game"

#define CreateText "Create Game"

#define InputY(h) (h *0.5)
#define InputWidth(w) (w*0.3)
#define InputHeight(h) (h *0.2)

#define ConnectY(h) (h * 0.8)
#define ConnectWidth(w) (w *0.2)
#define ConnectHeight(h) (h*0.1)
#define ConnectText "Connect to IP" 

#define PlayAgainText "Play Again"

#define LeaveText "Leave"

#define InstructionX(w) (w *0.5)
#define InstructionY(h,pos) (h*0.2*pos)
#define InstructionWidth(w) (w)
#define InstructionHeight(h) (h*0.2)
#define InstructionText1 "El Jugador 1 se mueve con 'A' y 'S', salta con 'W' y ataca con 'C'"
#define Inst1ID 32
#define InstructionText2 "El Jugador 2 se mueve con las flechas y ataca con 'M'"
#define Inst2ID 654






UI::UI(AllegroWindow & window)
	:window(window) {}

UI::~UI()
{
	if (this->font != nullptr)
		delete font;
	if (layout != nullptr)
		delete layout;
}

int UI::run(void * eventH, void * data)
{
	int retValue = 0;
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
	} while (retValue == 0);

	window.deleteLayout();
	if (this->sound != nullptr)
		this->sound->stop();



	return retValue;
}


TitleUI::TitleUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, TitleUIBackground, LayoutDrawMode::Slow);
	// SinglePlayerButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), SinglePlayerText,
		font, colorF.create(ButtonColor), SinglePlayerID));
	this->boxes[SinglePlayerID]->setBackgroundColor(colorF.create("hotpink"));
	// DoublePlayerButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 3) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), DoublePlayerText,
		font, colorF.create(ButtonColor), DoublePlayerID));
	this->boxes[DoublePlayerID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//ControlsButton

	this->boxes.addBox(new AllegroButton(ControlX(w) - (ControlWidth(w) / 2.0), ControlY(h), ControlWidth(w), ControlHeight(h), ControlText,
		font, colorF.create(ButtonColor), ControlID));
	this->boxes[ControlID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[SinglePlayerID]);
	this->layout->addBox(this->boxes[DoublePlayerID]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[ControlID]);

	pertinetIDs = { SinglePlayerID ,DoublePlayerID,ExitID ,ControlID };
}



ModeSelectionUI::ModeSelectionUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), LocalText,
		font, colorF.create(ButtonColor), LocalID));
	this->boxes[LocalID]->setBackgroundColor(colorF.create("hotpink"));
	// OnlineButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 3) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), OnlineText,
		font, colorF.create(ButtonColor), OnlineID));
	this->boxes[OnlineID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//BackButto
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[LocalID]);
	this->layout->addBox(this->boxes[OnlineID]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[BackID]);

	pertinetIDs = { LocalID ,OnlineID,ExitID ,BackID };
}



OnlineConfigUI::OnlineConfigUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), JoinText,
		font, colorF.create(ButtonColor), JoinID));
	this->boxes[JoinID]->setBackgroundColor(colorF.create("hotpink"));
	// OnlineButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 3) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), CreateText,
		font, colorF.create(ButtonColor), CreateID));
	this->boxes[CreateID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//BackButto
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[JoinID]);
	this->layout->addBox(this->boxes[CreateID]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[BackID]);

	pertinetIDs = { JoinID ,CreateID,ExitID ,BackID };
}

WaitingToJoinUI::WaitingToJoinUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//BackButton
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[BackID]);

	pertinetIDs = { ExitID ,BackID };
}

WaitingToCreateUI::WaitingToCreateUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);

	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//BackButton
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[BackID]);

	pertinetIDs = { ExitID ,BackID };
}

JoinMenuUI::JoinMenuUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);

	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	//BackButton
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("hotpink"));
	// input
	this->boxes.addBox(new AllegroWritableBox(KeyboardMode::Alphanumeric,ButtonX(w,2) - (InputWidth(w) / 2.0),InputY(h),InputWidth(w),
		InputHeight(h),font,colorF.create(ButtonColor),InputID));
	this->boxes[InputID]->setBackgroundColor(colorF.create("hotpink"));
	// connect
	this->boxes.addBox(new AllegroButton(ButtonX(w, 2) - (ConnectWidth(w) / 2.0), ConnectY(h), ConnectWidth(w), ConnectHeight(h), ConnectText,
		font, colorF.create(ButtonColor), ConnectID));
	this->boxes[ConnectID]->setBackgroundColor(colorF.create("hotpink"));

	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[BackID]);
	this->layout->addBox(this->boxes[ConnectID]);
	this->layout->addBox(this->boxes[InputID]);

	pertinetIDs = { ExitID ,BackID ,InputID ,ConnectID };
}

int JoinMenuUI::run(void * eventH,void * data)
{
	int retValue = 0;
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
				retValue = -1;	break;
			case EventType::MouseDown:
				for (unsigned int id : pertinetIDs)
					if ( this->boxes[id]->getType() == BoxType::Button && this->boxes[id]->click(ev.getX(), ev.getY(), ev.getTimestamp()))
						retValue = id;
				if (retValue == ConnectID && this->isIPValid(this->boxes[InputID]->getText())) {
					this->ip = this->boxes[InputID]->getText();
				}
				else if(retValue == ConnectID){
					retValue = 0;
					this->boxes[InputID]->clearText();
				}

			case EventType::Timer:
				this->window.update();
				break;
			}
		}
	} while (retValue == 0);

	window.deleteLayout();
	if (this->sound != nullptr)
		this->sound->stop();
	return retValue;
}

bool JoinMenuUI::isIPValid(std::string ip)
{
	return true;
}

GameOverUI::GameOverUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), PlayAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("hotpink"));
	// OnlineButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 3) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), LeaveText,
		font, colorF.create(ButtonColor), LeaveID));
	this->boxes[LeaveID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));


	this->layout->addBox(this->boxes[PlayAgainID]);
	this->layout->addBox(this->boxes[LeaveID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { PlayAgainID ,LeaveID,ExitID  };
}

WonUI::WonUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), PlayAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("hotpink"));
	// OnlineButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 3) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), LeaveText,
		font, colorF.create(ButtonColor), LeaveID));
	this->boxes[LeaveID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));


	this->layout->addBox(this->boxes[PlayAgainID]);
	this->layout->addBox(this->boxes[LeaveID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { PlayAgainID ,LeaveID,ExitID };
}

InstructionsUI::InstructionsUI(AllegroSoundFactory & soundF, AllegroWindow & window)
	:UI(window)
{
	this->font = new AllegroFont(FontPath, FontSize, 0);

	//this->sound = soundF.create("", PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, ModeSelectionBackground, LayoutDrawMode::Slow);
	// Button
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), BackText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[LeaveID]->setBackgroundColor(colorF.create("hotpink"));
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), ExitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("hotpink"));
	// Controles P1

	this->boxes.addBox(new AllegroWrittenBox(InstructionX(w) - (InstructionWidth(w) / 2.0), InstructionY(h, 2), InstructionWidth(w), InstructionHeight(h),
		InstructionText1, font, colorF.create("white"), Inst1ID));
	this->boxes.addBox(new AllegroWrittenBox(InstructionX(w) - (InstructionWidth(w) / 2.0), InstructionY(h, 2), InstructionWidth(w), InstructionHeight(h),
		InstructionText1, font, colorF.create("white"), Inst2ID));


	this->layout->addBox(this->boxes[BackID]);
	this->layout->addBox(this->boxes[ExitID]);
	this->layout->addBox(this->boxes[Inst1ID]);
	this->layout->addBox(this->boxes[Inst2ID]);

	pertinetIDs = { BackID,ExitID };
}
