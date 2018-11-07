#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

enum class MenuFlags
{
	Error = -1 ,Enabled =0 , Disabled = 4, Checkbox = 2, checkedBox = 1
};

/*
		AllegroMenu is a way to create a menu without looking at allegro. For now it only supports the regular menu and not the pop up one
*/
class AllegroMenu
{
public:

	// Constructor
	AllegroMenu();

	// Constructor:
	//
	//		-ALLEGRO_MENU_INFO * completedMenu: Its a hardcoded menu that was created from a array of Allegro_menu_info structures
	AllegroMenu(ALLEGRO_MENU_INFO * completedMenu);

	// Destructor
	~AllegroMenu();

	// It appends an item to the menu
	//
	//		- string title: title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	void appendItem(std::string title, uint16_t uniqueid, MenuFlags flag);

	// It inserts an item to the menu in a given position
	//
	//		- string title: title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	//		- unsigned int pos: the position where the item will be placed.
	void insertItem(std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos);

	// It appends an item into a submenu. If there is no submeno, it will create it.
	//	
	//		- uint16_t parentID: the ID of the item that will be converted into a submenu.
	//		- string title: title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	void appendSubItem(uint16_t parentID, std::string title, uint16_t uniqueID, MenuFlags flag);

	// It inserts an item into a submenu in a given position. If there is no submenu created in that position it will create it.
	//
	//		- uint16_t parentID: the ID of the item that will be converted into a submenu.
	//		- string title: the title of the item.
	//		- uint16_t uniqueID: an unique 16 bit ID for that given item. This ID must be >0. It will be usefull to for events.
	//							 if the user pressed this item, it will return the ID int event.user.data1
	//		- MenuFlags flag: The kind of item it will be. It can be Enabled, Disabled,Checked and checkBox
	void insertSubItem(uint16_t parentID, std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos);

	// It sets a new flag for a given item
	void setItemFlag(uint16_t uniqueID, MenuFlags flag);

	// It returns the flag of a given item
	MenuFlags getItemFlag(uint16_t uniqueID);

	// It sets the title of a given item
	void setItemTitle(std::string title, uint16_t uniqueID);

	// It returns the title of a given item
	std::string getItemTitle(uint16_t uniqueID);

	// It returns the event source
	ALLEGRO_EVENT_SOURCE * getEventSource();

	// It return the menu
	ALLEGRO_MENU * GetMainMenu();
private:
	ALLEGRO_MENU * menu;
};


