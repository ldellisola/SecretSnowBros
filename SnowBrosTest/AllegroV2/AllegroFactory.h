#pragma once
#include <string>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_native_dialog.h>


class AllegroDisplayFactory
{
public:
	AllegroDisplayFactory(){}
	~AllegroDisplayFactory() { for (ALLEGRO_DISPLAY * disp : all) destroy(disp); }
	/*
		El modo de destruccion automatico hace que se destruyan todas las pantallas cuando se destruye al objeto. De estar desactivado se tienen que destruir manualemente
	*/
	ALLEGRO_DISPLAY * create(unsigned int w, unsigned int h, bool automaticDestruction = true) {
		ALLEGRO_DISPLAY * temp = al_create_display(w, h);
		if (temp)
			if (automaticDestruction) {
				all.push_back(temp);
			}
		return temp;
	};
	void destroy(ALLEGRO_DISPLAY * display) { 
		int i;
		bool kill = false;
		for (i = 0; i < all.size(); i++) {
			if (all[i] == display)
				kill = true;
		}
		i--;
		if (kill) {
			all.erase(all.begin() + i);
			al_destroy_display(display);
		}
	};

private:
	std::vector<ALLEGRO_DISPLAY *> all;
};

enum class PopUpReturn
{
	Yes, No, Closed
};
enum class PopUpType
{
	Warn = 1, Error = 2, OkCancel = 4, YesNo = 8, Question = 16, 
};

class AllegroPopUpFactory
{
public:
	AllegroPopUpFactory(){}
	~AllegroPopUpFactory(){}

	PopUpReturn create(std::string title, std::string heading, std::string text,PopUpType type ,ALLEGRO_DISPLAY * display = nullptr) {
		return (PopUpReturn) al_show_native_message_box(display, title.c_str(), heading.c_str(), text.c_str(), nullptr, (int)type);
	}

private:

};


/*
	Crea y decodifica colores de allegro
*/
class AllegroColorFactory
{
public:
	AllegroColorFactory(){}

	~AllegroColorFactory(){}

	ALLEGRO_COLOR create(std::string color) { return al_color_name(color.c_str()); }
	ALLEGRO_COLOR create(unsigned char r, unsigned char g, unsigned char b) { return al_map_rgb(r, g, b); }
	ALLEGRO_COLOR create(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { return al_map_rgba(r, g, b, a); }
	void decode(ALLEGRO_COLOR& color, unsigned char&r, unsigned char & g, unsigned char & b) { al_unmap_rgb(color, &r, &g, &b); }
	void decode(ALLEGRO_COLOR& color, unsigned char&r, unsigned char&g,unsigned char&b, unsigned char&a) { al_unmap_rgba(color, &r, &g, &b, &a); }

private:

};

/*
	Crea bitmaps
*/

class AllegroBitmapFactory
{
public:
	AllegroBitmapFactory(){}
	~AllegroBitmapFactory(){ for (ALLEGRO_BITMAP * bmap : all) destroy(bmap); }
	ALLEGRO_BITMAP * create(unsigned int w, unsigned int h, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap(w, h);
		if (temp)
			if (automaticDestruction) {
				all.push_back(temp);
			}
		return temp;
	}
	void destroy(ALLEGRO_BITMAP * bitmap) {
		int i;
		bool kill = false;
		for (i = 0; i < all.size(); i++) {
			if (all[i] == bitmap)
				kill = true;
		}
		i--;
		if (kill) {
			all.erase(all.begin() + i);
			al_destroy_bitmap(bitmap);
		}
	}

private:
	std::vector<ALLEGRO_BITMAP *> all;
};

// Dudo si esto deberia ser una factory o un tipo nuevo de dato
class AllegroEventFactory
{
public:
	AllegroEventFactory(ALLEGRO_EVENT_QUEUE* eventQueue) { this->eventQueue = eventQueue; }

	~AllegroEventFactory() { for (ALLEGRO_EVENT_SOURCE* eventSource : sources) al_unregister_event_source(eventQueue, eventSource); }
	void flushQueue() { al_flush_event_queue(this->eventQueue); }

	bool getEvent() { return al_get_next_event(eventQueue, &ev); }
	ALLEGRO_EVENT_TYPE getEventType() { return ev.type; }
	ALLEGRO_DISPLAY_EVENT getDisplayEvent() { return ev.display; }
	ALLEGRO_KEYBOARD_EVENT getKeyboardEvent() { return ev.keyboard; }
	ALLEGRO_TIMER_EVENT getTimerEvent() { return ev.timer; }
	ALLEGRO_MOUSE_EVENT getMouseEvent() { return ev.mouse; }
	ALLEGRO_USER_EVENT getUserEvent() { return ev.user; }
	void registerEventSource(ALLEGRO_EVENT_SOURCE * eventSource) {
		al_register_event_source(eventQueue, eventSource);
		sources.push_back(eventSource);
	}
	void unregisterEventSource(ALLEGRO_EVENT_SOURCE* eventSource) {
		int i;
		bool kill = false;
		for (i = 0; i < sources.size() && !kill; i++) {
			if (sources[i] == eventSource)
				kill = true;
		}
		i--;
		if (kill) {
			sources.erase(sources.begin() +i);
			al_unregister_event_source(eventQueue, eventSource);
		}
	}
 
private:
	ALLEGRO_EVENT_QUEUE * eventQueue = nullptr;
	ALLEGRO_EVENT ev;
	std::vector<ALLEGRO_EVENT_SOURCE*>sources;
};



class AllegroTimerFactory
{
public:
	AllegroTimerFactory(){}

	~AllegroTimerFactory() { for (ALLEGRO_TIMER * timer : all) al_destroy_timer(timer); }
	ALLEGRO_TIMER * create(float time, bool automaticDestruction = true) {
		ALLEGRO_TIMER * temp = al_create_timer(time);
		if (temp) {
			if (automaticDestruction)
				all.push_back(temp);
			al_start_timer(temp);
		}
		return temp;
	}

	void destroy(ALLEGRO_TIMER * timer) {
		int i;
		bool kill = false;
		for (i = 0; i < all.size(); i++) {
			if (all[i] == timer)
				kill = true;
		}
		i--;
		if (kill) {
			all.erase(all.begin() + i);
			al_destroy_timer(timer);
		}
	}

private:
	std::vector<ALLEGRO_TIMER*>all;
};


class AllegroPrimitivesFactory
{
public:
	AllegroPrimitivesFactory(){}

	~AllegroPrimitivesFactory(){
		for (ALLEGRO_BITMAP * bitmap : all)
			al_destroy_bitmap(bitmap);
	}

	ALLEGRO_BITMAP * createEllipse(float radiusX, float radiusY,ALLEGRO_COLOR color,bool filled = true, float thickness = 0, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap(2* (radiusX+thickness), (radiusY + thickness) * 2);

		if (temp) {
			al_set_target_bitmap(temp);

			if (filled)
				al_draw_filled_ellipse(radiusX, radiusY, radiusX, radiusY, color);
			else
				al_draw_ellipse(radiusX+thickness, radiusY + thickness, radiusX, radiusY, color,thickness);
			al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

			if (automaticDestruction)
				all.push_back(temp);
		}
		return temp;
	}

	ALLEGRO_BITMAP * createRoundedRectangle(float width, float height,float radius, ALLEGRO_COLOR color, bool filled = true, float thickness = 0, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap(width, height);

		if (temp) {
			al_set_target_bitmap(temp);

			if (filled)
				al_draw_filled_rounded_rectangle(0, 0, width, height, radius, radius,color);
			else
				al_draw_rounded_rectangle(0, 0, width, height, radius, radius, color, thickness);
			al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

			if (automaticDestruction)
				all.push_back(temp);
		}
		return temp;
	}

	ALLEGRO_BITMAP * createRectangle(float width, float height, ALLEGRO_COLOR color, bool filled = true, float thickness = 0, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap(width, height);

		if (temp) {
			al_set_target_bitmap(temp);

			if (filled)
				al_draw_filled_rectangle(0, 0, width, height, color);
			else
				al_draw_rectangle(0, 0, width, height, color, thickness);
			al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

			if (automaticDestruction)
				all.push_back(temp);
		}
	}

	ALLEGRO_BITMAP * createCircle(float radius ,ALLEGRO_COLOR color,bool filled = true, float thickness = 0, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap((radius+thickness) * 2, (radius + thickness) * 2);
		if (temp) {
			al_set_target_bitmap(temp);
			if (filled)
				al_draw_filled_circle((radius + thickness), (radius + thickness), radius, color);
			else
				al_draw_circle((radius + thickness), (radius + thickness), radius, color, thickness);
			al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
			if (automaticDestruction)
				all.push_back(temp);
		}
		return temp;
	}


	void destroy(ALLEGRO_BITMAP * bitmap) {
		int i;
		bool kill = false;
		for (i = 0; i < all.size(); i++) {
			if (all[i] == bitmap)
				kill = true;
		}
		i--;
		if (kill) {
			all.erase(all.begin() + i);
			al_destroy_bitmap(bitmap);
		}
	}


private:
	std::vector<ALLEGRO_BITMAP *> all;

};
