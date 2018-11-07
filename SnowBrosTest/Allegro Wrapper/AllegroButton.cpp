#include "AllegroButton.h"






AllegroButton::~AllegroButton()
{
}

bool AllegroButton::click(float mouseX, float mouseY, double timeStamp)
{
	if (!((mouseX < this->x) || (this->x + this->width < mouseX) || (mouseY < this->y ) || (this->y + this->height < mouseY)))
		return true;
	else 
		return false;
}



bool AllegroButton::doubleClick(float mouseX, float mouseY, double timestamp)
{
	if (!((mouseX < this->x) || (this->x + this->width < mouseX) || (mouseY < this->y ) || (this->y + this->height < mouseY)))
		if (pressed) {
			if (MinClickThreshold < timestamp - clickTimeStamp) {
				unpress();
				if (timestamp - clickTimeStamp < MaxClickThreshold) 
					return true;
				else 
					return false;
			}
			else 
				return false;
		}
		else {
			press();
			clickTimeStamp = timestamp;
			return false;
		}
	else {
		unpress();
		clickTimeStamp = 0;
		return false;
	}


}

void AllegroButton::draw()
{
	al_draw_bitmap(this->bitmap, this->x, this->y, 0);
}



void AllegroButton::press()
{
	pressed = true;
}

void AllegroButton::unpress()
{
	pressed = false;
}



/////////////////////////////////////////////////////////////////////////////////////

void AllegroToggle::toggle(float mouseX, float mouseY, double timeStamp)
{

	if (!((mouseX < this->x) || (this->x + this->width < mouseX) || (mouseY < this->y) || (this->y + this->height < mouseY))) {
		if (clickTimeStamp == 0) {
			clickTimeStamp = timeStamp;
			if (pressed)
				pressed = true;
			else
				pressed = false;
		}
	}
	if (timeStamp - clickTimeStamp >= MinClickThreshold) { // && clickTimeStamp !=0
		clickTimeStamp = 0;
	}


}

bool AllegroToggle::isPressed()
{
	return pressed;
}

void AllegroToggle::draw()
{
	if (pressed)
		al_draw_tinted_bitmap(this->bitmap, this->pressedColor, this->x, this->y, 0);
	else
		al_draw_bitmap(this->bitmap, this->x, this->y, 0);
}
