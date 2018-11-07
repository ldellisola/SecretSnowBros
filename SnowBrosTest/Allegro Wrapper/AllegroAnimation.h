#pragma once
#include <vector>
#include <string>

#include <allegro5/allegro.h>


#include "AllegroSprite.h"

enum class FlipSprite
{
	None,Vertically,Horizontally
};

class AllegroAnimation
{
public:
	// Constructor: It will load and destroy all sprites.
	//
	//	- std::vector<std::string> files:		Path to the sprites to be loaded.
	AllegroAnimation(std::vector<std::string> files);

	// Constructor: It will load and destroy all sprites.
	//
	//	- std::vector<std::string> files:		Path to the sprites to be loaded.
	//	- float angle:							Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	AllegroAnimation(std::vector<std::string> files, float angle);

	// Constructor: It will load and destroy all sprites.
	//
	//	- std::vector<std::string> files:		Path to the sprites to be loaded.
	//	- float height:							Height of the image you want to draw. It does not have to be the same as the height of the sprite.
	//	- float width:							Width of the image you want to draw. It does not have to be the same as the width of the sprite.
	AllegroAnimation(std::vector<std::string> files,float height, float width);

	// Constructor: It will load and destroy all sprites.
	//
	//	- std::vector<std::string> files:		Path to the sprites to be loaded.
	//	- float height:							Height of the image you want to draw. It does not have to be the same as the height of the sprite.
	//	- float width:							Width of the image you want to draw. It does not have to be the same as the width of the sprite.
	//	- float angle:							Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	AllegroAnimation(std::vector<std::string> files, float height, float width, float angle);

	// Constructor: It loads existing sprites and it does not destroy them.
	//
	// - std::vector<AllegroSprite *> animation:All the sprites for your animation already loaded in memory.	
	AllegroAnimation(std::vector<AllegroSprite *> animation);

	// It inserts a sprite at a given part of the animation. IT SHOULD ONLY BE USED IF ALL YOUR SPRITES WERE CREATED FROM WITHIN THE ANIMATION.
	// IF YOU LOADED A VECTOR OF AllegroSprite * YOU CAN ONLY LOAD MORE AllegroSprites *. It returnS true if it was loaded correctly.
	//
	// - std::string file:						Path to the sprite to be loaded.
	// - unsigned int position:					Position to insert the sprite. If the position is bigger than the ammount of sprites, it will append it.
	bool insert(std::string file, unsigned int position);

	// It appends a sprite to the existing animation. IT SHOULD ONLY BE USED IF ALL YOUR SPRITES WERE CREATED FROM WITHIN THE ANIMATION.
	// IF YOU LOADED A VECTOR OF AllegroSprite * YOU CAN ONLY LOAD MORE AllegroSprites *. It returnS true if it was loaded correctly.
	//
	// - std::string file:						Path to the sprite to be loaded.
	bool append(std::string file);


	// It inserts a sprite at a given part of the animation. IT SHOULD ONLY BE USED IF ALL YOUR SPRITES WERE LOADED FROM OUTSIDE THE ANIMATION.
	// IF YOU LOADED A VECTOR OF STRING* YOU CAN ONLY LOAD MORE STRING*. It returns true if it was loaded correctly.
	//
	// - std::string file:						Path to the sprite to be loaded.
	// - unsigned int position:					Position to insert the sprite. If the position is bigger than the ammount of sprites, it will append it.
	bool insert(AllegroSprite * sprite, unsigned int position);

	// It appends a sprite to the existing animation. IT SHOULD ONLY BE USED IF ALL YOUR SPRITES WERE LOADED FROM OUTSIDE THE ANIMATION.
	// IF YOU LOADED A VECTOR OF STRING* YOU CAN ONLY LOAD MORE STRING*. It returnS true if it was loaded correctly.
	//
	// - std::string file:						Path to the sprite to be loaded.
	bool append(AllegroSprite * sprite);

	// It removes a given sprite from the animation. If the position is bigger than the ammount of sprites it will return false.
	//
	// - unsigned int position:					Position of the sprite to be removed. 
	bool remove(unsigned int position);

	// It recovers a given sprites from within the animation. it return a pointer to it. If the position is bigger than the ammount of
	// sprites it will return false.
	//
	// - unsigned int position:					Position of the sprite to be removed.
	AllegroSprite * recover(unsigned int position);

	// It swaps 2 sprites in the animation. It returns false if it wasn't possible.
	//
	// - unsigned int spriteA:					Position of the 1st sprite.
	// - unsigned int spriteB:					Position of the 2nd sprite.
	bool swap(unsigned int spriteA, unsigned int spriteB);

	// It draws one frame of the animation and then updates an inner counter (so the next time is called it will show the next frame). 
	// It return the number of the frame it displayed.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	unsigned int draw(float x, float y, FlipSprite mode = FlipSprite::None);

	// It draws one frame of the animation (at a given angle) and then updates an inner counter (so the next time is called it will show the next frame). 
	// It return the number of the frame it displayed.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - float angle:						Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	unsigned int draw(float x, float y, float angle, FlipSprite mode = FlipSprite::None);

	// It draws one frame of the animation (at a given width and height) and then updates an inner counter (so the next time is called it will 
	// show the next frame). It return the number of the frame it displayed.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - float height:						Height at which the sprite will be drawn.
	// - float width:						Width at which the sprite will be drawn.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	unsigned int draw(float x, float y, float height, float width, FlipSprite mode = FlipSprite::None);

	// It draws a given frame of the animation and then the inner counter is moved to the position given as a parameter. if the position excedes
	// the ammount of frames in the animation, it will not draw anything and it will return false.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - unsigned int position:				Frame of the animation to be drawn.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	bool draw(float x, float y,unsigned int pos, FlipSprite mode = FlipSprite::None);

	// It draws a given frame of the animation (rotated at a given angle) and then the inner counter is moved to the position 
	// given as a parameter. if the position excedesthe ammount of frames in the animation, it will not draw anything and it 
	// will return false.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - float angle:						Angle at which the image will be rotated. ONLY DEGREES. DO NOT USE RADIANS.
	// - unsigned int position:				Frame of the animation to be drawn.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	bool draw(float x, float y, float angle, unsigned int pos, FlipSprite mode = FlipSprite::None);

	// It draws a given frame of the animation (at a given width and height) and then the inner counter is moved to the position 
	// given as a parameter. if the position excedesthe ammount of frames in the animation, it will not draw anything and it 
	// will return false.
	//
	// - float x:							X coordinate.
	// - float y:							Y coordinate.
	// - float height:						Height at which the sprite will be drawn.
	// - float width:						Width at which the sprite will be drawn.
	// - unsigned int position:				Frame of the animation to be drawn.
	// - FlipSprite mode:					To choose if the image will be vertically mirrored, horizontally mirrored or it won't be mirrored.
	bool draw(float x, float y, float height, float width, unsigned int pos, FlipSprite mode = FlipSprite::None);

	~AllegroAnimation();

private:
	void updateCounter();

	unsigned int counter = 0;

	bool foreignAnimation;

	std::vector<AllegroSprite *> sprites;
};

