#include "UI.h"

#define ButtonY(w) (w * 0.75)
#define ButtonX(h,pos) (pos * (0.5) * h)
#define ButtonHeight(h) (h * 0.1)
#define ButtonWidth(w) (w * 0.8)
#define ButtonColor "white"

#define ExitX(w) (w * 0.8)
#define ExitY(h) (h * 0.1)
#define ExitW(w) (w * 0.3)
#define ExitH(h) (h * 0.1)
#define ExitText "Exit"

#define ControlX(w) (w *0.2)
#define ControlY(h) (h *0.1)
#define ControlWidth(w) (w*0.3)
#define ControlHeight(h) (h*0.1)

#define BackX(w) (w *0.2)
#define BackY(h) (ControlY(h))
#define BackHeight(h) (ControlHeight(h))
#define BackWidth(w) ( ControlWidth(w))

#define InstructionX(w) (w *0.5)
#define InstructionY(h,pos) (h*0.2*pos)
#define InstructionWidth(w) (w)
#define InstructionHeight(h) (h*0.2)
#define InstructionText1 "El Jugador 1 se mueve con 'A' y 'S', salta con 'W' y ataca con 'C'"
#define Inst1ID 32




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
	
	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	int fontSize = std::atoi(al_get_config_value(config, "Font", "TitleSize"));
	std::string fontPath = al_get_config_value(config, "Font", "TitlePath");
	std::string titleUIBackground = al_get_config_value(config, "Menu", "TitleImagePath");
	std::string titleSoundtrack = al_get_config_value(config, "Music", "TitlePath");
	std::string playText = al_get_config_value(config, "Menu", "PlayText");
	std::string exitText = al_get_config_value(config, "Menu", "ExitText");
	std::string instructionText = al_get_config_value(config, "Menu", "InstructionText");
	al_destroy_config(config);

	this->font = fontF.create(fontPath, fontSize, 0);

	this->sound = soundF.create(titleSoundtrack, PlayMode::Loop, 0);

	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, titleUIBackground, LayoutDrawMode::Slow);
	this->boxes.addBox(new AllegroWrittenBox(w*0.2, h*0.3,  "", font, colorF.create("white"), 3213));


	// SinglePlayerButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), playText,
		font, colorF.create(ButtonColor), SinglePlayerID));
	this->boxes[SinglePlayerID]->setBackgroundColor(colorF.create("black"));
	this->boxes[SinglePlayerID]->setBorderColor(colorF.create("white"));
	this->boxes[SinglePlayerID]->setBorderThickness(1);

	//// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), exitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);

	//ControlsButton

	this->boxes.addBox(new AllegroButton(ControlX(w) - (ControlWidth(w) / 2.0), ControlY(h), ControlWidth(w), ControlHeight(h), instructionText,
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

	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	int fontSize = std::atoi(al_get_config_value(config, "Font", "TitleSize"));
	std::string fontPath = al_get_config_value(config, "Font", "TitlePath");
	std::string gameOverBackground = al_get_config_value(config, "Menu", "GameOverImagePath");
	std::string gameOverSoundTrack = al_get_config_value(config, "Music", "GameOverPath");
	std::string playAgainText = al_get_config_value(config, "Menu", "PlayAgainText");
	std::string exitText = al_get_config_value(config, "Menu", "ExitText");

	al_destroy_config(config);


	this->font = fontF.create(fontPath, fontSize, 432);

	this->sound = soundF.create(gameOverSoundTrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, gameOverBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), playAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("black"));
	this->boxes[PlayAgainID]->setBorderColor(colorF.create("white"));
	this->boxes[PlayAgainID]->setBorderThickness(1);

	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), exitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);



	this->layout->addBox(this->boxes[PlayAgainID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { PlayAgainID ,ExitID };
}

WonUI::WonUI(AllegroSoundFactory & soundF, AllegroWindow & window, AllegroFontFactory& fontF)
	:UI(window)
{

	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	int fontSize = std::atoi(al_get_config_value(config, "Font", "TitleSize"));
	std::string fontPath = al_get_config_value(config, "Font", "TitlePath");
	std::string playAgainText = al_get_config_value(config, "Menu", "PlayAgainText");
	std::string wonSoundtrack = al_get_config_value(config, "Music", "WonPath");
	std::string wonBackground = al_get_config_value(config, "Menu", "WonImagePath");
	std::string exitText = al_get_config_value(config, "Menu", "ExitText");

	al_destroy_config(config);

	this->font = fontF.create(fontPath, fontSize, 4345);


	this->sound = soundF.create(wonSoundtrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, wonBackground, LayoutDrawMode::Slow);
	// LocalButton
	this->boxes.addBox(new AllegroButton(ButtonX(w, 1) - (ButtonWidth(w) / 2.0), ButtonY(h), ButtonWidth(w), ButtonHeight(h), playAgainText,
		font, colorF.create(ButtonColor), PlayAgainID));
	this->boxes[PlayAgainID]->setBackgroundColor(colorF.create("black"));
	this->boxes[PlayAgainID]->setBorderColor(colorF.create("white"));
	this->boxes[PlayAgainID]->setBorderThickness(1);
	
	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), exitText,
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
	ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

	int fontSize = std::atoi(al_get_config_value(config, "Font", "TitleSize"));
	std::string fontPath = al_get_config_value(config, "Font", "TitlePath");
	std::string instructionsBackground = al_get_config_value(config, "Menu", "InstructionsImagePath");
	std::string instructionsSoundtrack = al_get_config_value(config, "Music", "InstructionsPath");
	std::string backText = al_get_config_value(config, "Menu", "BackText");
	std::string exitText = al_get_config_value(config, "Menu", "ExitText");

	al_destroy_config(config);


	this->font = fontF.create(fontPath, fontSize, 43445);

	this->sound = soundF.create(instructionsSoundtrack, PlayMode::Loop, 0);


	AllegroColorFactory colorF;
	int w = window.getWidth(), h = window.getHeight();
	this->layout = new AllegroLayout(w, h, instructionsBackground, LayoutDrawMode::Slow);
	// Button
	this->boxes.addBox(new AllegroButton(BackX(w) - (BackWidth(w) / 2.0), BackY(h), BackWidth(w), BackHeight(h), backText,
		font, colorF.create(ButtonColor), BackID));
	this->boxes[BackID]->setBackgroundColor(colorF.create("black"));
	this->boxes[BackID]->setBorderColor(colorF.create("white"));
	this->boxes[BackID]->setBorderThickness(1);

	// ExitButton
	this->boxes.addBox(new AllegroButton(ExitX(w) - (ExitW(w) / 2.0), ExitY(h), ExitW(w), ExitH(h), exitText,
		font, colorF.create(ButtonColor), ExitID));
	this->boxes[ExitID]->setBackgroundColor(colorF.create("black"));
	this->boxes[ExitID]->setBorderColor(colorF.create("white"));
	this->boxes[ExitID]->setBorderThickness(1);

	this->layout->addBox(this->boxes[BackID]);
	this->layout->addBox(this->boxes[ExitID]);

	pertinetIDs = { BackID,ExitID };
}

