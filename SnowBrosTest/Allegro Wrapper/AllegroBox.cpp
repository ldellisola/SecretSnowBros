#include "AllegroBox.h"


AllegroBox::AllegroBox(float x, float y, float width, float height, unsigned int boxID )
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->bitmap = al_create_bitmap(width, height);
	this->imageBackground = nullptr;
	this->drawImage = false;
	this->ID = boxID;
	this->setBoxType(BoxType::Box);
	this->setUp();
}

AllegroBox::~AllegroBox()
{
	al_destroy_bitmap(this->bitmap);
	if (!this->foreignImage && this->imageBackground != nullptr)
		al_destroy_bitmap(this->imageBackground);
}

void AllegroBox::draw()
{
	al_draw_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, this->x+ this->width/2.0, this->y + this->height/2.0, this->rotationDegree, 0);
}

void AllegroBox::setBackgroundColor(ALLEGRO_COLOR color)
{
	this->backgroundColor = color;
	setUp();
}

void AllegroBox::setBorderColor(ALLEGRO_COLOR color)
{
	this->borderColor = color;
	setUp();
}

void AllegroBox::setBorderThickness(float thickness)
{
	this->borderThickness = thickness;
	setUp();
}

void AllegroBox::setX(float x)
{
	this->x = x;
}

void AllegroBox::setY(float y)
{
	this->y = y;
}

void AllegroBox::setImageAsBackground()
{
	if (imageBackground != nullptr) {
		this->drawImage = true;
		this->setUp();
	}
}

void AllegroBox::setColorAsBackground()
{
	this->drawImage = false;
	this->setUp();
}

void AllegroBox::setRotationDegree(double degree)
{
	this->rotationDegree = degree * (ALLEGRO_PI / 180.0);
}

void AllegroBox::loadImageBackground(std::string imagePath)
{
	this->imageBackground = al_load_bitmap(imagePath.c_str());
	if (this->imageBackground == nullptr)
		throw InvalidLoadException();

	this->foreignImage = false;
}

void AllegroBox::loadImageBackground(ALLEGRO_BITMAP * image)
{
	this->imageBackground = image;
	this->foreignImage = true;
}

void AllegroBox::resize(float width, float height)
{
	al_destroy_bitmap(this->bitmap);
	this->bitmap = al_create_bitmap(width, height);
	this->width = width;
	this->height = height;
	this->setUp();
}

ALLEGRO_BITMAP * AllegroBox::getBitmap()
{
	return this->bitmap;
}

ALLEGRO_COLOR AllegroBox::getBorderColor()
{
	return this->borderColor;
}

ALLEGRO_COLOR AllegroBox::getBackgroundColor()
{
	return this->backgroundColor;
}

float AllegroBox::getBorderThickness()
{
	return borderThickness;
}

float AllegroBox::getX()
{
	return this->x;
}

float AllegroBox::getY()
{
	return this->y;
}

float AllegroBox::getWidth()
{
	return this->width;
}

float AllegroBox::getHeight()
{
	return this->height;
}

unsigned int AllegroBox::getID()
{
	return this->ID;
}

BoxType AllegroBox::getType()
{
	return this->type;
}

bool AllegroBox::operator==(AllegroBox & box)
{
	if (box.bitmap == this->bitmap)
		return true;
	else
		return false;
}

bool AllegroBox::operator!=(AllegroBox & box)
{
	if (box.bitmap != this->bitmap)
		return true;
	else
		return false;
}

void AllegroBox::setUp()
{
	ALLEGRO_DISPLAY * main = al_get_current_display();
	al_set_target_bitmap(this->bitmap);
	if (drawImage)
		al_draw_scaled_bitmap(this->imageBackground, 0, 0, al_get_bitmap_width(imageBackground), al_get_bitmap_height(imageBackground), 0, 0, width, height, 0);
	else
		al_clear_to_color(backgroundColor);

	if (borderThickness > 0) {
		float x1 = borderThickness;
		float x2 = width - borderThickness;
		float y1 = borderThickness;
		float y2 = height - borderThickness;
		al_draw_rectangle(x1, y1, x2, y2, borderColor, borderThickness);
	}

	al_set_target_backbuffer(main);
}

void AllegroBox::setBoxType(BoxType type)
{
	this->type = type;
}
