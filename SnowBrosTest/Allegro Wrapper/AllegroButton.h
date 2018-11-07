#pragma once
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "AllegroFont.h"

#include "WrittenBox.h"

#define MinClickThreshold (0.001)
#define MaxClickThreshold (0.2)


struct AllegroButtonData
{
	float x, y, width, height;
	std::string text;
	AllegroFont* font;
	ALLEGRO_COLOR fontColor;
};

/*
		This button has a single click and a double click option. This should not be used at the same time as they can cause issues.
*/

class AllegroButton :
	public AllegroWrittenBox
{
public:
	// Constructor:
	//
	//		- float x:					initial X coordinate.
	//		- float y:					initial Y coordinate.
	//		- float width:				width of the button.
	//		- float height:				height of the button.
	//		- string text:				text of the button.
	//		- AllegroFont * font:		Font to be loaded
	//		- ALLEGRO_COLOR fontColor:	color of the font
	AllegroButton(float x, float y, float width, float height, std::string text, AllegroFont * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroWrittenBox(x,y,width,height,text,font,fontColor, boxID){
		this->setBoxType(BoxType::Button);
	}



	// Constructor: It will take an existing font. This is a good option for when you have to create a lot of identical Boxes or you need to 
	//				create a box inside another function and you need all of this information from outside of it.
	//
	//		- AllegroWrittenBoxData& data: a structure with all the data of a box
	AllegroButton(AllegroButtonData& data, unsigned int boxID = DefaultID)
		:AllegroWrittenBox(data.x, data.y, data.width, data.height, data.text,data.font,data.fontColor, boxID) {
		this->setBoxType(BoxType::Button);
	}

	// Destructor
	~AllegroButton();

	// This function will return true if the user clicked on the button.
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	virtual bool click(float mouseX, float mouseY, double timeStamp);


	// This function will return true if there was a double click within the given time thresholds.
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	virtual bool doubleClick(float mouseX, float mouseY, double timeStamp);



	// It draws the button to the active display
	virtual void draw();
protected:
	void press();
	void unpress();
	double clickTimeStamp = 0;
	bool pressed = false;

	
};


class AllegroToggle :public AllegroButton {
public:
	// Constructor: 
	//
	//		- float x:					initial X coordinate.
	//		- float y:					initial Y coordinate.
	//		- float width:				width of the button.
	//		- float height:				height of the button.
	//		- string text:				text of the button.
	//		- AllegroFont * font:		Font to be loaded
	//		- ALLEGRO_COLOR fontColor:	color of the font
	AllegroToggle(float x, float y, float width, float height,std::string text, AllegroFont * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		:AllegroButton(x, y, width, height,text, font, fontColor, boxID) {
		this->setBoxType(BoxType::Toggle);
		pressedColor = al_map_rgb(100, 100, 100);
	}

	// Constructor: It will take an existing font. This is a good option for when you have to create a lot of identical Boxes or you need to 
	//				create a box inside another function and you need all of this information from outside of it.
	//
	//		- AllegroWrittenBoxData& data: a structure with all the data of a box
	AllegroToggle(AllegroButtonData& data, unsigned int boxID = DefaultID) 
		:AllegroButton(data, boxID) {
		this->setBoxType(BoxType::Toggle);
		pressedColor = al_map_rgb(100, 100, 100);
	}


	// This function will set the button as clicked if the mouse coordinates coincide with the button and the click was made a given number 
	// of seconds after the last click
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	void toggle(float mouseX, float mouseY, double timeStamp);


	// this function will return true if the button is pressed. IT ONLY WORKS WITH A SINGLE CLICK
	bool isPressed();

	// It draws the button to the active display
	void draw();
	
private:
	ALLEGRO_COLOR pressedColor;
};





