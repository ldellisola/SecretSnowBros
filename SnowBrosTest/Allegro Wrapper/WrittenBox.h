#pragma once
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "AllegroFont.h"
#include "AllegroBox.h"



struct AllegroWrittenBoxData
{
	float x, y, width, height;
	std::string text;
	AllegroFont * font;
	ALLEGRO_COLOR fontColor;
};


class AllegroWrittenBox : public AllegroBox
{
public:

	// Constructor:
	//
	//		- float X:					initial X coordinate.
	//		- float Y:					initial Y coordinate.
	//		- float width:				width of the box.
	//		- float height:				height of the box.
	//		- string text:				text to be printed.
	//		- AllegroFont * font:		Font to be loaded
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWrittenBox(float x, float y, float width, float height, std::string text, AllegroFont * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroBox(x, y, width, height, boxID) {
		this->setBoxType(BoxType::Written);
		this->text = text;
		this->font = font;
		this->fontColor = fontColor;
		foreignFont = false;
		this->setUp();
	}

	// Constructor: It will create a box the size of the text.
	//
	//		- float X:					initial X coordinate.
	//		- float Y:					initial Y coordinate.
	//		- string text:				text to be printed.
	//		- AllegroFont * font:		Font to be loaded
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWrittenBox(float x_, float y_, std::string text_, AllegroFont * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroBox(x_, y_, font->previewTextWidth("WW" + text), 3 * font->previewTextHeight(), boxID) {
		this->setBoxType(BoxType::Written);
		this->text = text_;
		this->font = font;
		this->fontColor = fontColor;
		foreignFont = true;
		this->setUp();
	}

	// Constructor: It will take an existing font. This is a good option for when you have to create a lot of identical Boxes or you need to 
	//				create a box inside another function and you need all of this information from outside of it.
	//
	//		- AllegroWrittenBoxData& data: a structure with all the data of a box
	AllegroWrittenBox(AllegroWrittenBoxData& data, unsigned int boxID = DefaultID)
		: AllegroBox(data.x, data.y, data.width, data.height,boxID) {
		this->setBoxType(BoxType::Written);
		this->text = data.text;
		this->font = data.font;
		this->fontColor = data.fontColor;
		foreignFont = true;
		this->setUp();
	}

	~AllegroWrittenBox();

	// It returns a copy of the text in the box.
	std::string getText() { return text; }

	// It sets the text for the box to print. DO NOT USE THIS WITH THE THIRD CONSTRUCTOR.
	void setText(std::string text);

protected:

	// It updates the internal bitmap of the box.
	void setUp();
	
	// It tells you if the font of the box was created within the box or outside of it.
	bool foreignFont;

	std::string text;
	ALLEGRO_COLOR fontColor;
	AllegroFont * font;
	
};

