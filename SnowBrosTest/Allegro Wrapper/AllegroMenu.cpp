#include "AllegroMenu.h"



AllegroMenu::AllegroMenu()
{
	this->menu = al_create_menu();
}

AllegroMenu::AllegroMenu(ALLEGRO_MENU_INFO * completedMenu)
{
	this->menu = al_build_menu(completedMenu);
}

AllegroMenu::~AllegroMenu()
{
	if (menu != nullptr)
		al_destroy_menu(menu);
}

void AllegroMenu::appendItem(std::string title, uint16_t uniqueID, MenuFlags flag)
{
	if (menu != nullptr)
		al_append_menu_item(menu, title.c_str(), uniqueID, (int)flag, nullptr, nullptr);
}

void AllegroMenu::insertItem(std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos)
{
	if (menu != nullptr)
		al_insert_menu_item(menu, (0-pos), title.c_str(), uniqueID, (int)flag, nullptr, nullptr);
}	

void AllegroMenu::appendSubItem(uint16_t parentID,std::string title, uint16_t uniqueID, MenuFlags flag)
{
	ALLEGRO_MENU * father = al_find_menu(menu, parentID);
	if (father != nullptr) {		// Me fijo si es un menu o no

		al_append_menu_item(father, title.c_str(), uniqueID, (int)flag, nullptr, nullptr);
	}
	else {
		ALLEGRO_MENU * parentMenu;
		int parentIndex;
		if (al_find_menu_item(menu, parentID, &parentMenu, &parentIndex)) {
			int parentFlag = al_get_menu_item_flags(parentMenu, -parentIndex);
			std::string parentTitle = al_get_menu_item_caption(parentMenu, -parentIndex);
			al_remove_menu_item(menu, parentIndex);

			ALLEGRO_MENU * temp = al_create_menu();
			al_append_menu_item(temp, title.c_str(), uniqueID, (int)flag, nullptr, nullptr);

			al_insert_menu_item(menu,-parentIndex, parentTitle.c_str(), parentID, parentFlag, nullptr, temp);
		}
	}


	
}

void AllegroMenu::insertSubItem(uint16_t parentID,std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos)
{
	ALLEGRO_MENU * father = al_find_menu(menu, parentID);
	if (father != nullptr) {		// Me fijo si es un menu o no

		al_insert_menu_item(father,(0-pos), title.c_str(), uniqueID, (int)flag, nullptr, nullptr);
	}
	else {
		ALLEGRO_MENU * parentMenu;
		int parentIndex;
		if (al_find_menu_item(menu, parentID, &parentMenu, &parentIndex)) {
			int parentFlag = al_get_menu_item_flags(parentMenu, -parentIndex);
			std::string parentTitle = al_get_menu_item_caption(parentMenu, -parentIndex);
			al_remove_menu_item(menu, parentIndex);

			ALLEGRO_MENU * temp =al_create_menu();
			al_insert_menu_item(temp, (0-pos), title.c_str(), uniqueID, (int)flag, nullptr, nullptr);

			al_insert_menu_item(menu, -parentIndex, parentTitle.c_str(), parentID, parentFlag, nullptr, temp);
		}
	}
}

void AllegroMenu::setItemFlag(uint16_t uniqueID, MenuFlags flag)
{
	if (menu != nullptr)
		al_set_menu_item_flags(menu, uniqueID, (int)flag);
}

MenuFlags AllegroMenu::getItemFlag(uint16_t uniqueID)
{
	if (menu != nullptr)
		return (MenuFlags)al_get_menu_item_flags(menu, uniqueID);
	else
		return MenuFlags::Error;
}

void AllegroMenu::setItemTitle(std::string title, uint16_t uniqueID)
{
	if (menu != nullptr)
		al_set_menu_item_caption(this->menu, uniqueID, title.c_str());
}

std::string AllegroMenu::getItemTitle(uint16_t uniqueID)
{
	if (menu != nullptr)
		return al_get_menu_item_caption(this->menu, uniqueID);
	else
		return std::string();
}

ALLEGRO_EVENT_SOURCE * AllegroMenu::getEventSource()
{
	if (menu != nullptr)
		return al_enable_menu_event_source(menu);
	else
		return nullptr;
}

ALLEGRO_MENU * AllegroMenu::GetMainMenu()
{
	return menu;
}




