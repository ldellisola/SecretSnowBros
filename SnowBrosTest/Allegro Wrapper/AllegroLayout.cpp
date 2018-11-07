#include "AllegroLayout.h"


AllegroLayout::AllegroLayout(float w, float h, ALLEGRO_COLOR color,LayoutDrawMode mode) {
	this->w = w;
	this->h = w;
	this->color = color;
	this->mode = mode;
	this->foreignImage = false;
	this->backgroundImage = false;
	this->layout = al_create_bitmap(w, h);
	
}

AllegroLayout::AllegroLayout(float w, float h,std::string image, LayoutDrawMode mode) {
	this->w = w;
	this->h = h;
	this->color = al_color_name("black");
	this->mode = mode;
	this->foreignImage = false;
	this->backgroundImage = true;
	this->image = al_load_bitmap(image.c_str());
	if (this->image == nullptr)
		throw InvalidLoadException();

	this->layout = al_create_bitmap(w, h);
}

AllegroLayout::AllegroLayout(float w, float h, ALLEGRO_BITMAP * image , LayoutDrawMode mode) {
	this->w = w;
	this->h = h;
	this->color = al_color_name("black");
	this->mode = mode;
	this->foreignImage = true;
	this->backgroundImage = true;
	this->image = image;

	this->layout = al_create_bitmap(w, h);
}

AllegroLayout::~AllegroLayout()
{
	if (image != nullptr && !foreignImage)
		al_destroy_bitmap(image);
	image = nullptr;
}

void AllegroLayout::draw()
{
	if (mode == LayoutDrawMode::Slow)
		this->setUp();

	//al_draw_bitmap(this->layout, 0, 0, 0);


	drawBoxes();

}

void AllegroLayout::setDrawMode(LayoutDrawMode mode)
{
	this->mode = mode;
	this->setUp();
}






void AllegroLayout::addBox(AllegroBox * box)
{
	this->boxes.push_back(box);
	this->setUp();
}




void AllegroLayout::removeBox(AllegroBox & box)
{
	bool kill = false; int i = 0;
	for (i = 0; i < boxes.size() && !kill; i++) {
		if (*boxes[i] == box)
			kill = true;
	}
	i--;
	if (kill) {
		boxes.erase(boxes.begin() + i);
	}
	this->setUp();

}




void AllegroLayout::loadBackground(ALLEGRO_COLOR color)
{
	this->color = color;
}

void AllegroLayout::setImageAsBackground()
{
	if (image != nullptr)
		backgroundImage = true;
	this->setUp();

}

void AllegroLayout::setColorAsBackground()
{
	this->backgroundImage = false;
	this->setUp();

}

void AllegroLayout::loadImageBackground(std::string image)
{
	this->image = al_load_bitmap(image.c_str());
	if (this->image == nullptr)
		throw InvalidLoadException();
}

void AllegroLayout::loadImageBackground(ALLEGRO_BITMAP * image)
{
	this->image = image;
}

void AllegroLayout::loadImageBackground(AllegroBox & image)
{
	this->image = image.getBitmap();
}

void AllegroLayout::setUp()
{
	if (layout != nullptr) {

		//ALLEGRO_DISPLAY *disp = al_get_current_display();
		//al_set_target_bitmap(this->layout);

		if (backgroundImage)
			al_draw_scaled_bitmap(this->image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, this->w, this->h,0);
			//al_draw_scaled_bitmap(this->image, 0, 0, al_get_bitmap_width(image),al_get_bitmap_height(image), 0, 0, 1300, 600, 0);

		else
			al_clear_to_color(color);


		drawBoxes();

		//al_set_target_backbuffer(disp);
		
	}
}

void AllegroLayout::drawBoxes()
{
	for (AllegroBox* box : boxes)
		box->draw();
}


void BoxArray::addBox(AllegroBox * box)
{
	boxes.push_back(box);
}

void BoxArray::deleteBox(unsigned int ID)
{
	auto box = find_if(boxes.begin(), boxes.end(), [&ID](AllegroBox* obj) {return obj->getID() == ID; });

	if (box != boxes.end())
	{
		AllegroBox * temp = *box;
		boxes.erase(box);
		delete temp;
	}

}

unsigned int BoxArray::size()
{
	return boxes.size();
}

AllegroBox * BoxArray::operator[](unsigned int ID)
{
	
	auto box = find_if(boxes.begin(), boxes.end(), [&ID](AllegroBox* obj) {return obj->getID() == ID; });

	if (box == boxes.end())
		return nullptr;
	else
		return *box;
}

BoxArray::~BoxArray()
{
	while (boxes.size() > 0) {
		AllegroBox * temp = *boxes.begin();
		boxes.erase(boxes.begin());
		delete temp;
	}
}


