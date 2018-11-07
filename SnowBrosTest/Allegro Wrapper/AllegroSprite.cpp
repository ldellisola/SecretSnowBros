#include "AllegroSprite.h"
#include <math.h>

#define PI (3.14159265359)

float degreesToRadians(float deg) {
	return deg * (PI/180.0);
}




AllegroSprite::AllegroSprite(std::string file)
{
	this->bitmap = al_load_bitmap(file.c_str());
	if (this->bitmap == nullptr)
		throw InvalidLoadException();
	this->angle = 0;
	this->height = al_get_bitmap_height(this->bitmap);
	this->width = al_get_bitmap_width(this->bitmap);
	this->scaledHeight = height;
	this->scaledWidth = width;
}

AllegroSprite::AllegroSprite(std::string file, float height, float width)
{
	this->bitmap = al_load_bitmap(file.c_str());
	if (this->bitmap == nullptr)
		throw InvalidLoadException();
	this->angle = 0;
	this->height = al_get_bitmap_height(this->bitmap);
	this->width = al_get_bitmap_width(this->bitmap);
	this->scaledHeight = height;
	this->scaledWidth = width;
}

AllegroSprite::AllegroSprite(std::string file, float height, float width, float angle)
{
	this->bitmap = al_load_bitmap(file.c_str());
	if (this->bitmap == nullptr)
		throw InvalidLoadException();
	this->angle = degreesToRadians(angle);
	this->height = al_get_bitmap_height(this->bitmap);
	this->width = al_get_bitmap_width(this->bitmap);
	this->scaledHeight = height;
	this->scaledWidth = width;
}

AllegroSprite::AllegroSprite(std::string file, float angle)
{
	this->bitmap = al_load_bitmap(file.c_str());
	if (this->bitmap == nullptr)
		throw InvalidLoadException();
	this->angle = degreesToRadians(angle);
	this->height = al_get_bitmap_height(this->bitmap);
	this->width = al_get_bitmap_width(this->bitmap);
	this->scaledHeight = height;
	this->scaledWidth = width;
}

AllegroSprite::~AllegroSprite()
{
	if (this->bitmap != nullptr)
		al_destroy_bitmap(this->bitmap);
}

void AllegroSprite::draw(float x, float y)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0,x+ (this->scaledWidth/2.0), y + (this->scaledHeight/2.0)
		,this->scaledWidth/ float(this->width),this->scaledHeight/ float(this->height), this->angle,0);
		//, float(this->width)/ this->scaledWidth , float(this->height)/ this->scaledHeight , this->angle, 0);
}

void AllegroSprite::drawVerticallyMirrored(float x, float y)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 this->scaledWidth / this->width, this->scaledHeight / this->height, this->angle, ALLEGRO_FLIP_VERTICAL);
}

void AllegroSprite::drawVerticallyMirrored(float x, float y, float angle)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0,
		x, y, this->scaledWidth / this->width, this->scaledHeight / this->height, degreesToRadians(angle), ALLEGRO_FLIP_VERTICAL);
}

void AllegroSprite::drawVerticallyMirrored(float x, float y, float height, float width)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 width / this->width, height / this->height, this->angle, ALLEGRO_FLIP_VERTICAL);
}

void AllegroSprite::drawHorizontallyMirrored(float x, float y)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 this->scaledWidth / this->width, this->scaledHeight / this->height, this->angle, ALLEGRO_FLIP_HORIZONTAL);
}

void AllegroSprite::drawHorizontallyMirrored(float x, float y, float angle)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 this->scaledWidth / this->width, this->scaledHeight / this->height, degreesToRadians(angle), ALLEGRO_FLIP_HORIZONTAL);
}

void AllegroSprite::drawHorizontallyMirrored(float x, float y, float height, float width)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		width / this->width, height / this->height, this->angle, ALLEGRO_FLIP_HORIZONTAL);
}

void AllegroSprite::draw(float x, float y, float angle)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 this->scaledWidth / this->width, this->scaledHeight / this->height, degreesToRadians(angle) , 0);
}

void AllegroSprite::draw(float x, float y, float height, float width)
{
	al_draw_scaled_rotated_bitmap(this->bitmap, this->width / 2.0, this->height / 2.0, x + (this->scaledWidth / 2.0), y + (this->scaledHeight / 2.0),
		 width / this->width, height / this->height, this->angle, 0);
}

void AllegroSprite::setDimensions(float height, float width)
{
	this->scaledHeight = height;
	this->scaledWidth = width;
}

void AllegroSprite::setAngle(float angle)
{
	this->angle = degreesToRadians(angle);
}



