#pragma once

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "AllegroException.h"
#include "AllegroEvent.h"

#define DefaultID (0)

enum class BoxType
{
	Box, Button, Toggle, Written, Writable
};


class AllegroBox
{
public:
	// Constructor
	//
	//		- float x:		initial X coordinate.
	//		- float y:		initial Y coordinate.
	//		- float width:	width of the box.
	//		- float height: height of the box.
	//		- BoxType type: Type of the box. It can be a Box, a button, a toggle, a WrittenBox or a WritableBox.
	//		- unsigned int boxID : Unique ID to each box, if the user decides not to assign one, it will be set to DefaultID
	AllegroBox(float x, float y, float width, float height, unsigned int boxID = DefaultID);
	 virtual ~AllegroBox();

	// Draws the bitmap to the actual screen.
	//
	virtual void draw();

	virtual void resize(float width, float height);
	virtual void loadImageBackground(std::string imagePath);
	virtual void loadImageBackground(ALLEGRO_BITMAP * image);

	// Setters: each function set a given variable of the box
	//
	virtual void setBackgroundColor(ALLEGRO_COLOR color);
	virtual void setBorderColor(ALLEGRO_COLOR color);
	virtual void setBorderThickness(float thickness);
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setImageAsBackground();
	virtual void setColorAsBackground();
	virtual void setRotationDegree(double degree); // It does not support radians, because fuck radians
	

	// Getters: each function returns a given variable of the box

	virtual ALLEGRO_BITMAP * getBitmap();
	virtual ALLEGRO_COLOR getBorderColor();
	virtual ALLEGRO_COLOR getBackgroundColor();
	virtual float getBorderThickness();
	virtual float getX();
	virtual float getY();
	virtual float getWidth();
	virtual float getHeight();
	virtual unsigned int getID();
	virtual BoxType getType();

	// Overloaded operators.

	bool operator==(AllegroBox&box);
	bool operator!=(AllegroBox&box);

	// Virtual Methods added to avoid casting. 

	// ONLY WRTITENBOX AND WRITTABLEBOX :It returns a copy of the text in the box.
	virtual std::string getText() { return ""; }

	// ONLY WRTITENBOX : It sets the text for the box to print. DO NOT USE THIS WITH THE THIRD CONSTRUCTOR.
	virtual void setText(std::string text) {}

	// ONLY WrittableBox : It takes a keyboard event and uses the key that was pressed. 
	virtual void input(AllegroEvent ev){}

	// ONLY WrittableBox : It restarts the texts that the user typed
	virtual void clearText(){}


	// ONLY AllegroButton: This function will return true if the user clicked on the button.
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	virtual bool click(float mouseX, float mouseY, double timeStamp) { return false; }

	// ONLY AllegroButton: This function will return true if there was a double click within the given time thresholds.
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	virtual	bool doubleClick(float mouseX, float mouseY, double timeStamp) { return false; }

	// ONLY AllegroToggle : This function will set the button as clicked if the mouse coordinates coincide with the button and the click was made a given number 
	// of seconds after the last click
	//
	//		- float mouseX: X coordinate of the mouse.
	//		- float mouseY: Y coordinate of the mouse.
	//		- double timeStamp: timestamp of the event. this should be under mouse.timestamp .
	virtual void press(float mouseX, float mouseY, double timeStamp) {}

	// ONLY AllegroToggle : this function will return true if the button is pressed. IT ONLY WORKS WITH A SINGLE CLICK
	virtual bool isPressed() { return false; }


protected:
	// This function is called everytime a change is made in the box to reflect that change on the bitmap
	// it should only be called from within the clases.
	virtual void setUp();
	virtual void setBoxType(BoxType type);
	ALLEGRO_BITMAP * bitmap = nullptr;
	ALLEGRO_BITMAP * imageBackground = nullptr;
	ALLEGRO_COLOR borderColor;
	ALLEGRO_COLOR backgroundColor;
	bool drawImage = false;
	bool foreignImage = false;
	float borderThickness;
	double rotationDegree = 0;
	float x;
	float y;
	float width;
	float height;
	BoxType type;
	// ID given to all boxes and derivated classes. This is useful to identify boxes when you have an array of boxes (Duh).
	// All boxes will have 0 as default ID, if the user decides not to assign one to it.
	unsigned int ID;
};

