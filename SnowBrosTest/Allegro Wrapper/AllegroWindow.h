#pragma once
#include <vector>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "AllegroBox.h"
#include "AllegroMenu.h"
#include "AllegroLayout.h"


enum class CursorSprite
{
	None, Default, Arrow, Busy, Question, Edit, ResizeUp, ResizeLeft, ResizeDown, ResizeRight,
	ResizeUpLeft, ResizeDownLeft, ResizeDownRight, ResizeUpRight, Progress, Precision, Link,
	AltSelect, Unavailable
};

enum class ScreenMode
{
	Regular, FullScreen, Maximized,Frameless
};



/*
		This class was made to simplify and escape from all the allegro functions. From here you can access pretty much everything that has to do with allegro_Display
		although I did not include the more obscure functions as I normaly won't use.

		AllegroWindow needs an eventQueue to facilitate everytime you ahve to open and close it. If you don't want to pass the eventQueue, it will work just by calling
		al_register_event_source() everytime you open the display and al_unregister_event_source() whenever you close it.
*/

class AllegroWindow
{
public:

	// BASIC


	// Constructor: it create a window
	//
	//		- float w: the width of the window.
	//		- float h: the height of the window.
	//		- string name: the name of the window.
	//		- string icon: the path to the icon of the window.
	AllegroWindow(float w, float h, ALLEGRO_EVENT_QUEUE  *evQueue = nullptr, std::string name = "", std::string icon = "");

	// Destructor.
	~AllegroWindow();

	// Overloaded operator to check for equality with allegro displays ( for compatibility)
	bool operator==(ALLEGRO_DISPLAY* disp);

	// Overloaded operator to check for equality with another allegroWindow
	bool operator==(AllegroWindow& window);


	// EVENTS


	// It sets an event queue ONLY TO REGISTER AND UNREGISTER EVENT SOURCES (MAINLY DISPLAY SOURCES)
	void setEventQueue(ALLEGRO_EVENT_QUEUE * queue);

	// It returns the event Source of the window. That event source will change everytime
	ALLEGRO_EVENT_SOURCE * getEventSource();


	// DRAW

	void insertLayout(AllegroLayout& layout);

	void deleteLayout();

	void setLayoutDrawMode(LayoutDrawMode mode);

	// It adds an AllegroBox to the window. It will be printed everytime the window is updatesd by its own draw function
	void addBox(AllegroBox& box);

	// It removes an AllegroBox that was being drawn on the window
	void removeBox(AllegroBox& box);

	// It sets the color of the display.
	void loadBackground(ALLEGRO_COLOR color);

	// It loads the background of the display
	void loadImageBackground(std::string image);
	void loadImageBackground(ALLEGRO_BITMAP * image);
	void loadImageBackground(AllegroBox& image);

	// It sets a previusly loaded image as the background of the window
	void setImageAsBackground();

	// It sets a previusly selected color as the background of the window
	void setColorAsBackground();


	// DISPLAY

	
	// Sets the window as the main window.
	void setAsMain();

	// It opens the window.
	void open();

	// It closes the window.
	void close();

	// It draws all the bitmaps of the display.
	void update();

	// It sets the name of the window.
	void setName(std::string name);

	// It sets the icon for the window.
	void setIcon(std::string icon);

	// It sets the position of the window on the computer's screen.
	void setPosition(float x, float y);

	// It sets the window into fullscreen mode.
	void setFullScreen();

	// It sets the window into frameless mode.
	void setFrameless();

	// It sets the window into maximized mode.
	void setMaximize();
	
	// It returns the window to its regular mode.
	void setRegular();

	// It resizes the window
	void resize(float newW, float newH);

	// It says if the window is open.
	bool isOpen();

	// It returns the width of the window.
	float getWidth();

	// It returns the Height of the window
	float getHeight();

	ALLEGRO_DISPLAY * getDisplay();


	// MOUSE


	// It allows the user to use a custom sprite instead of the regular mouse cursor;
	//
	//		- string iconPath: path to the sprite
	//		- xFocus: X coordinate of the sprite where the mouse will click
	//		- yFocus: Y coordinate of the sprite where the mouse will click
	void setCustomMouseCursor(std::string iconPath, float xFocus = 0, float yFocus = 0);

	// it sets a custom mouse cursor as the main cursor for this window
	void useCustomMouseCursor();

	// It sets the system mouse cursor as the main cursor for this window
	void useSystemMouseCursor();

	// It allows the user to select what kind of system mouse cursor will be used in this window
	void setDifferentSystemMouseCursor(CursorSprite sprite);

	// It hides the mouse cursor in this window
	void hideMouseCursor();

	// It unhides (Yes, it is an actual word) the mouse cursor in this window
	void showMouseCursor();

	// It forces the cursor to stay on this window
	void catchMouseCursor();

	//It allows the cursor to leave the window. THIS WILL RELEASE THE CURSOR FROM ANY OTHER WINDOW
	void releaseMouseCursor();


	// MENU


	// Creates a menu
	void createMenu();

	// It deletes the menu
	void deleteMenu();

	// It shows a previusly created menu. If it was not created or if it wasn't initialized with an item, it will do noting
	void showMenu();

	// Hides a previusly created menu. If it was not created or if it wasn't initialized with an item, it will do noting
	void hideMenu();

	// It inserts an item into menu in a given position.
	//
	//		- string title: the title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	//		- unsigned int pos: the position where the item will be placed.
	void insertMenuItem(std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos);

	// It inserts an item into a submenu in a given position. If there is no submenu created in that position it will create it.
	//
	//		- uint16_t parentID: the ID of the item that will be converted into a submenu.
	//		- string title: the title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	//		- unsigned int pos: the position where the item will be placed.
	void insertMenuSubItemp(uint16_t parentID, std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos);

	// It appends an item into a submenu. If there is no submeno, it will create it.
	//
	//		- uint16_t parentID: the ID of the item that will be converted into a submenu.
	//		- string title: the title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	void appendMenuItem(std::string title, uint16_t uniqueid, MenuFlags flag);

	// It inserts an item into a submenu in a given position. If there is no submenu created in that position it will create it.
	//
	//		- uint16_t parentID: the ID of the item that will be converted into a submenu.
	//		- string title: the title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	void appendMenuSubItem(uint16_t parentID, std::string title, uint16_t uniqueID, MenuFlags flag);

	// It sets a new flag for a given item
	void setMenuItemFlag(uint16_t uniqueID, MenuFlags flag);

	// It sets the title of a given item
	void setMenuItemTitle(std::string title, uint16_t uniqueID);

	// It returns the flag of a given item
	MenuFlags getMenuItemFlag(uint16_t uniqueID);

	// It returns the title of a given item
	std::string getMenuItemTitle(uint16_t uniqueID);

	
private:
	// Display
	ALLEGRO_DISPLAY * display = nullptr;
	float width, height;
	bool on = false;
	void setUp();

	// Draw
	AllegroLayout * layout = nullptr;
	bool foreignLayout = false;

	// Screen
	ALLEGRO_BITMAP * icon = nullptr;
	std::string name;
	ScreenMode screenMode = ScreenMode::Regular;
	void clearScreenMode();
	
	// Cursor
	bool useCustomCursor = false;
	bool cursorHidden = false;
	bool cursorCaught = false;
	CursorSprite systemCursorSprite = CursorSprite::Default;

	ALLEGRO_MOUSE_CURSOR *	customMouseCursor = nullptr;
	ALLEGRO_BITMAP * customCursorSprite = nullptr;

	// Menu
	bool menuOn = false;
	bool menuInitialized = false;
	AllegroMenu *menu = nullptr;

	// EVENTS
	ALLEGRO_EVENT_QUEUE * queue = nullptr;

};

