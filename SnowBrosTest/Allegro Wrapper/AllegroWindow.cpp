#include "AllegroWindow.h"



AllegroWindow::AllegroWindow(float w, float h, ALLEGRO_EVENT_QUEUE *evQueue ,std::string name,std::string icon)
{
	width = w;
	height = h;

	if (name.size() > 0)
		setName(name);
	if (icon.size() > 0)
		setIcon(icon);

	this->layout = new AllegroLayout(w,h,al_color_name("black"),LayoutDrawMode::Mid);

	this->queue = evQueue;
}

AllegroWindow::~AllegroWindow()
{
	deleteMenu();
	close();
	if (icon != nullptr)
		al_destroy_bitmap(icon);
	if (customCursorSprite != nullptr)
		al_destroy_bitmap(customCursorSprite);

	if (layout != nullptr && !foreignLayout)
		delete layout;

}

void AllegroWindow::setEventQueue(ALLEGRO_EVENT_QUEUE * queue)
{
	this->queue = queue;
}



void AllegroWindow::setAsMain()
{
	if (on)
		al_set_target_backbuffer(this->display);
}

void AllegroWindow::open()
{
	if (!this->on) {
		this->on = true;
		this->display = al_create_display(width, height);
		this->setUp();
		if (queue != nullptr)
			al_register_event_source(queue, getEventSource());
		if (menuOn && menuInitialized) {
			al_set_display_menu(this->display, menu->GetMainMenu());
		}
	}
}

void AllegroWindow::close()
{
	if (this->on) {
		this->on = false;
		if (menuOn)
			al_remove_display_menu(this->display);
		
		if (customMouseCursor != nullptr)
			al_destroy_mouse_cursor(customMouseCursor);

		if (queue != nullptr)
			al_unregister_event_source(queue, getEventSource());

		
		al_destroy_display(this->display);
		this->display = nullptr;
	}
}



void AllegroWindow::update()
{
	if (on) {

		layout->draw();

		al_flip_display();
	}

}

void AllegroWindow::setName(std::string name)
{
	this->name = name;
	this->setUp();
}

void AllegroWindow::setIcon(std::string icon)
{
	this->icon = al_load_bitmap(icon.c_str());
	if (this->icon == nullptr)
		throw InvalidLoadException();
	this->setUp();
}

void AllegroWindow::setPosition(float x, float y)
{
	al_set_window_position(this->display, x, y);
}

void AllegroWindow::setFullScreen()
{
	this->screenMode = ScreenMode::FullScreen;
	if (this->on) {
		al_set_display_flag(this->display, ALLEGRO_FULLSCREEN_WINDOW, true);
		this->width = al_get_display_width(this->display);
		this->height = al_get_display_height(this->display);
	}

}

void AllegroWindow::setFrameless()
{
	this->screenMode = ScreenMode::Frameless;
	if (this->on) 
		al_set_display_flag(this->display, ALLEGRO_FRAMELESS, true);

}

void AllegroWindow::setMaximize()
{
	this->screenMode = ScreenMode::Maximized;
	if (this->on) {
		al_set_display_flag(this->display, ALLEGRO_MAXIMIZED, true);
		this->width = al_get_display_width(this->display);
		this->height = al_get_display_height(this->display);
	}

}

void AllegroWindow::setRegular()
{
	this->clearScreenMode();
	this->screenMode = ScreenMode::Regular;
	this->width = al_get_display_width(this->display);
	this->height = al_get_display_height(this->display);
}

void AllegroWindow::resize(float newW, float newH)
{
	this->width = newW;
	this->height = newH;
	al_resize_display(this->display, newW, newH);
	this->setUp();
}

bool AllegroWindow::isOpen()
{
	return on;
}

float AllegroWindow::getWidth()
{
	return this->width;
}

float AllegroWindow::getHeight()
{
	return this->height;
}

ALLEGRO_EVENT_SOURCE * AllegroWindow::getEventSource()
{
	return al_get_display_event_source(display);
}

void AllegroWindow::insertLayout(AllegroLayout & layout)
{
	if (this->layout != nullptr)
		delete this->layout;
	this->foreignLayout = true;
	this->layout = &layout;
}

void AllegroWindow::deleteLayout()
{
	if (layout != nullptr) {
		if (foreignLayout)
			this->layout = nullptr;
		else
			delete this->layout;
	}

	this->layout = new AllegroLayout(this->width, this->height, al_color_name("black"));
}

void AllegroWindow::setLayoutDrawMode(LayoutDrawMode mode)
{
	if (layout != nullptr)
		layout->setDrawMode(mode);
}

void AllegroWindow::addBox(AllegroBox & box)
{
	if (layout != nullptr)
		layout->addBox(&box);
}

void AllegroWindow::removeBox(AllegroBox & box)
{
	if (layout != nullptr)
		layout->removeBox(box);
}

void AllegroWindow::loadBackground(ALLEGRO_COLOR color)
{
	if (layout != nullptr)
		layout->loadBackground(color);
}

void AllegroWindow::loadImageBackground(std::string image)
{
	if (layout != nullptr)
		layout->loadImageBackground(image);
}

void AllegroWindow::loadImageBackground(ALLEGRO_BITMAP * image)
{
	if (layout != nullptr)
		layout->loadImageBackground(image);
}

void AllegroWindow::loadImageBackground(AllegroBox & image)
{
	if (layout != nullptr)
		layout->loadImageBackground(image);
}

void AllegroWindow::setImageAsBackground()
{
	if (layout != nullptr)
		layout->setImageAsBackground();
}

void AllegroWindow::setColorAsBackground()
{
	if (layout != nullptr)
		layout->setColorAsBackground();
}

ALLEGRO_DISPLAY * AllegroWindow::getDisplay()
{
	return display;
}

bool AllegroWindow::operator==(ALLEGRO_DISPLAY * disp)
{
	if (this->display == disp)
		return true;
	else
		return false;
}

bool AllegroWindow::operator==(AllegroWindow& window)
{
	if (this->display == window.display)
		return true;
	else
		return false;
}

void AllegroWindow::setCustomMouseCursor(std::string iconPath, float xFocus , float yFocus )
{
	this->customCursorSprite = al_load_bitmap(iconPath.c_str());
	if (this->customCursorSprite == nullptr)
		throw InvalidLoadException();
	this->customMouseCursor = al_create_mouse_cursor(customCursorSprite, xFocus, yFocus);
}

void AllegroWindow::useCustomMouseCursor()
{
	useCustomCursor = true;
	this->setUp();
}

void AllegroWindow::useSystemMouseCursor()
{
	useCustomCursor = false;
	this->setUp();
}

void AllegroWindow::setDifferentSystemMouseCursor(CursorSprite sprite)
{
	this->systemCursorSprite = sprite;
	this->setUp();
}

void AllegroWindow::hideMouseCursor()
{
	cursorHidden = true;
	this->setUp();
}

void AllegroWindow::showMouseCursor()
{
	cursorHidden = false;
	this->setUp();
}

void AllegroWindow::catchMouseCursor()
{
	cursorCaught = true;
	this->setUp();
}

void AllegroWindow::releaseMouseCursor()
{
	this->cursorCaught = false;
	this->setUp();
}

void AllegroWindow::createMenu()
{
	this->menu = new AllegroMenu();

	if (queue != nullptr)
		al_register_event_source(queue, menu->getEventSource());
}

void AllegroWindow::hideMenu()
{
	if (on)
		al_remove_display_menu(this->display);
	menuOn = false;
}

void AllegroWindow::showMenu()
{
	if (on && menuInitialized)
		al_set_display_menu(this->display, menu->GetMainMenu());
	menuOn = true;
}

void AllegroWindow::insertMenuItem(std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos)
{
	if (menu != nullptr) {
		menu->insertItem(title, uniqueID, flag, pos);
		menuInitialized = true;
	}
}

void AllegroWindow::insertMenuSubItemp(uint16_t parentID,std::string title, uint16_t uniqueID, MenuFlags flag, unsigned int pos)
{
	if (menu != nullptr)
		this->menu->insertSubItem(parentID, title, uniqueID, flag, pos);
}

void AllegroWindow::appendMenuItem(std::string title, uint16_t uniqueID, MenuFlags flag)
{

	if (menu != nullptr) {
		menu->appendItem(title, uniqueID, flag);
		menuInitialized = true;
	}
}

void AllegroWindow::appendMenuSubItem(uint16_t parentID,std::string title, uint16_t uniqueID, MenuFlags flag)
{
	if (menu != nullptr)
		menu->appendSubItem(parentID, title, uniqueID, flag);
}

void AllegroWindow::setMenuItemFlag(uint16_t uniqueID, MenuFlags flag)
{
	if (menu != nullptr)
		menu->setItemFlag(uniqueID, flag);
}

void AllegroWindow::setMenuItemTitle(std::string title, uint16_t uniqueID)
{
	if (menu != nullptr)
		menu->setItemTitle(title.c_str(), uniqueID);
}

MenuFlags AllegroWindow::getMenuItemFlag(uint16_t uniqueID)
{
	if (menu != nullptr)
		return menu->getItemFlag(uniqueID);
	else
		return MenuFlags::Error;
}

std::string AllegroWindow::getMenuItemTitle(uint16_t uniqueID)
{
	if (menu != nullptr)
		return menu->getItemTitle(uniqueID);
	else
		return std::string();
}

void AllegroWindow::deleteMenu()
{
	if (menu != nullptr)
		delete menu;
	menu = nullptr;
	menuInitialized = false;

}

void AllegroWindow::setUp()
{
	if (on) {
		if (customMouseCursor != nullptr && useCustomCursor)
			al_set_mouse_cursor(this->display, this->customMouseCursor);
		else
			al_set_system_mouse_cursor(this->display, (ALLEGRO_SYSTEM_MOUSE_CURSOR)systemCursorSprite);

		if (cursorHidden)
			al_hide_mouse_cursor(this->display);
		else
			al_show_mouse_cursor(this->display);

		if (cursorCaught)
			al_grab_mouse(this->display);
		else
			al_ungrab_mouse();

		if (name.size() > 0)
			al_set_window_title(display, name.c_str());
		if (icon != nullptr)
			al_set_display_icon(display, icon);

		switch (this->screenMode) {
		case ScreenMode::Frameless:
			this->setFrameless(); break;
		case ScreenMode::FullScreen:
			this->setFullScreen(); break;
		case ScreenMode::Maximized:
			this->setMaximize(); break;
		case ScreenMode::Regular:
			this->setRegular(); break;
		}
		this->update();
	}
}

void AllegroWindow::clearScreenMode()
{
	if (on) {
		al_set_display_flag(this->display, ALLEGRO_FULLSCREEN_WINDOW, false);
		al_set_display_flag(this->display, ALLEGRO_MAXIMIZED, false);
		al_set_display_flag(this->display, ALLEGRO_FRAMELESS, false);
	}

	screenMode = ScreenMode::Regular;
}
