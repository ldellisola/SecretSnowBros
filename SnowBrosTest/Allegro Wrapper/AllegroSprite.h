#pragma once
#include <allegro5/allegro.h>
#include "AllegroException.h"
#include <string>


class AllegroSprite
{
public:
	// Constructor:
	//
	//	- std::string file:		Name of the sprite you want to load.
	AllegroSprite(std::string file);

	// Constructor:
	//
	//	- std::string file:		Name of the sprite you want to load.
	//	- float height:			Height of the image you want to draw. It does not have to be the same as the height of the sprite.
	//	- float width:			Width of the image you want to draw. It does not have to be the same as the width of the sprite.
	AllegroSprite(std::string file,float height, float width);

	// Constructor:
	//
	//	- std::string file:		Name of the sprite you want to load.
	//	- float height:			Height of the image you want to draw. It does not have to be the same as the height of the sprite.
	//	- float width:			Width of the image you want to draw. It does not have to be the same as the width of the sprite.
	//	- float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	AllegroSprite(std::string file, float height, float width, float angle);

	// Constructor:
	//
	//	- std::string file:		Name of the sprite you want to load.
	//	- float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	AllegroSprite(std::string file, float angle);

	~AllegroSprite();

	// Draws the sprite to a given position. If values for desired angle, height or width, this function will take them into account.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	void draw(float x, float y);

	// Draws a vertically mirrored version of your sprite (upside down) at a given position.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	void drawVerticallyMirrored(float x, float y);

	// Draws a vertically mirrored version of your sprite (upside down) at a given position. It does this while rotating
	// the image at a given angle.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	void drawVerticallyMirrored(float x, float y, float angle);

	// Draws a vertically mirrored version of your sprite (upside down) at a given position. It does this while scaling the image
	// to a given height and width.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float height:			Height at which the sprite will be drawn.
	// - float width:			Width at which the sprite will be drawn.
	void drawVerticallyMirrored(float x, float y, float height, float width);

	// Draws a horizontally mirrored version of your sprite at a given position
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	void drawHorizontallyMirrored(float x, float y);

	// Draws a horizontally mirrored version of your sprite at a given position. It does this while rotating the image at a 
	// given angle.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	void drawHorizontallyMirrored(float x, float y, float angle);

	// Draws a horizontally mirrored version of your sprite at a given position. It does this while scaling the image
	// to a given height and width.
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float height:			Height at which the sprite will be drawn.
	// - float width:			Width at which the sprite will be drawn.
	void drawHorizontallyMirrored(float x, float y, float height, float width);

	// Draws the sprite at a given position. It does this while rotating the image at a given angle.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	void draw(float x, float y, float angle);

	// Draws the sprite at a given position. It does this while scaling the image to a given height and width.
	//
	// - float x:				X coordinate.
	// - float y:				Y coordinate.
	// - float height:			Height at which the sprite will be drawn.
	// - float width:			Width at which the sprite will be drawn.
	void draw(float x, float y, float height, float width);

	// It sets the height and width at which the sprite will be drawn when the plain draw functions (the ones that only take
	// an x,y value) are called.
	//
	//	- float height:			Height of the image you want to draw. It does not have to be the same as the height of the sprite.
	//	- float width:			Width of the image you want to draw. It does not have to be the same as the width of the sprite.
	void setDimensions(float height, float width);

	// It sets the angle of rotation at which the sprite will be drawn when the plain draw functions (the ones that only take
	// an x,y value) are called.
	//
	//	- float angle:			Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	void setAngle(float angle);

	
private:
	ALLEGRO_BITMAP * bitmap = nullptr;
	float scaledHeight, scaledWidth, height, width, angle;
};

