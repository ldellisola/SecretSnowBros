#include "WritableBox.h"






AllegroWritableBox::~AllegroWritableBox()
{
}

std::string AllegroWritableBox::getText()
{
	return this->text;
}

void AllegroWritableBox::input(AllegroEvent ev)
{
	int character = ev.getValue();
	if (timeStamp == 0) {
		if (this->width > this->font->previewTextWidth(text)) {
			switch (mode) {
			case KeyboardMode::Alphabetic:
				addLetter(character, ev.getModifier());
				break;
			case KeyboardMode::Alphanumeric:
				addLetter(character, ev.getModifier());
				addNumber(character);
				break;
			case KeyboardMode::Numeric:
				addNumber(character);
				break;
			}
		}
		deleteLetter(character);
		timeStamp = ev.getTimestamp();
		this->setUp();
	}
	else if (ev.getTimestamp() - timeStamp >= KeyPressedTimeThreshold)
		timeStamp = 0;
}

void AllegroWritableBox::clearText()
{
	this->text = "";
	this->setUp();
}



void AllegroWritableBox::setUp()
{
	AllegroBox::setUp();
	ALLEGRO_BITMAP * c = al_get_backbuffer(al_get_current_display());
	al_set_target_bitmap(this->bitmap);

	this->font->drawCentredText(this->text, this->fontColor, this->width, this->height);

	al_set_target_bitmap(c);
	
}

void AllegroWritableBox::addNumber(int num)
{
	if (num >= ALLEGRO_KEY_0 && num <= ALLEGRO_KEY_9)
		this->text += '0' + (num -ALLEGRO_KEY_0);
}

void AllegroWritableBox::addLetter(int let, unsigned int modifiers)
{
	char initial;
	if (modifiers & ALLEGRO_KEYMOD_CAPSLOCK || modifiers & ALLEGRO_KEYMOD_SHIFT)
		initial = 'A';
	else
		initial = 'a';

	if (ALLEGRO_KEY_A <= let && let <= ALLEGRO_KEY_Z)
		this->text += initial + (let - ALLEGRO_KEY_A);

}




void AllegroWritableBox::deleteLetter(int let)
{
	if (let == ALLEGRO_KEY_BACKSPACE && text.size()>0)
		text.pop_back();
}
