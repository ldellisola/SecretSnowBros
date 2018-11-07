#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_native_dialog.h>

#include "../Allegro Wrapper/AllegroException.h"

namespace Allegro {
	// Modos de inicializacion de allegro:
	// Modo Basic: Inicializa display,keyboard, Font, Primitives.
	// Modo Full: Inicializa todos los addons.
	// Modo Events: Inicializa lo mismo que el modo Basic pero agrega eventos, mouse y timer.
	// Modo Empty: Hay que inicializar todo manual luego de que se cree el objeto.
	enum class InitMode
	{
		Basic, Full, Events, Empty
	};

	const unsigned int NoValue = 0;
}

// Clase Padre de todos los addons, define los metodos para verificar que se instalaron con exito
class Addon {
public:
	bool getSuccess() { return success; }
protected:
	void initSuccess() { this->success = true; }
private:
	bool success = false;
};





class ImageAddon : public Addon {
public:
	ImageAddon() {
		if (al_init_image_addon())
			this->initSuccess();
		else
			throw AllegroInitException();
	}
	~ImageAddon() { al_shutdown_image_addon(); }
};


class NativeDialogAddon : public Addon {
public:
	NativeDialogAddon() {
		if (al_init_native_dialog_addon())
			this->initSuccess();
		else
			throw AllegroInitException();
	}
	~NativeDialogAddon() { al_shutdown_native_dialog_addon(); }
};


class AudioAddon : public Addon {
public:
	AudioAddon() { 
		if (al_install_audio() && al_init_acodec_addon()) 
			this->initSuccess(); 
		else
			throw AllegroInitException();
	}
	~AudioAddon() { al_uninstall_audio(); }
	
};





class FontAddon : public Addon {
public:
	FontAddon() {
		if (al_init_font_addon() && al_init_ttf_addon())
			this->initSuccess();
		else
			throw AllegroInitException();
	}
	~FontAddon() { al_shutdown_font_addon(); al_shutdown_ttf_addon(); }
};





class KeyboardAddon : public Addon {
public:
	KeyboardAddon() { 
		if (al_install_keyboard()) 
			this->initSuccess();
		else
			throw AllegroInitException();
	}
	~KeyboardAddon() { al_uninstall_keyboard(); }
};





class DisplayAddon : public Addon {
public:
	DisplayAddon(float x = Allegro::NoValue, float y = Allegro::NoValue) {
		if (x != Allegro::NoValue && y != Allegro::NoValue)	
			display = al_create_display(x, y);	
		else if (x == Allegro::NoValue || y == Allegro::NoValue) {
			this->initSuccess();
			return;
		}
		else 
			throw AllegroInitException();

		if (x != Allegro::NoValue && y != Allegro::NoValue && display != nullptr)	
			this->initSuccess();
		else
			throw AllegroInitException();
	}

	void setDisplayColor(ALLEGRO_COLOR color) { al_clear_to_color(color); }
	void updateDisplay() { al_flip_display(); }

	ALLEGRO_DISPLAY * getDisplay() { return display; }
	~DisplayAddon() { if (display != nullptr) al_destroy_display(display); }
private:
	ALLEGRO_DISPLAY * display = nullptr;
};





class MouseAddon : public Addon {
public:
	MouseAddon() { 
		if (al_install_mouse()) 
			this->initSuccess();
		else
			throw AllegroInitException();
	}
	~MouseAddon() { al_uninstall_mouse(); }
};





class TimerAddon : public Addon {
public:
	TimerAddon() { this->initSuccess(); }
	TimerAddon(float fps) {
		if (refresh = al_create_timer(1 / (double)fps)){
			this->initSuccess(); 
			al_start_timer(this->refresh);
		}
		else
			throw AllegroInitException();
	}
	ALLEGRO_TIMER * getRefreshTimer() { return refresh; }
	~TimerAddon() { if (refresh != nullptr) al_destroy_timer(refresh); }
private:
	ALLEGRO_TIMER * refresh = nullptr;		// Este timer se encarga de los fps de la pantalla
};





class PrimitivesAddon : public Addon {
public:
	PrimitivesAddon() { 
		if (al_init_primitives_addon()) 
			this->initSuccess(); 
		else
			throw AllegroInitException();
	}
	~PrimitivesAddon() { al_shutdown_primitives_addon(); }
};





class EventsAddon : public Addon {
public:
	EventsAddon() {
		if (eventQueue = al_create_event_queue()) 
			this->initSuccess();
		else
			throw AllegroInitException();
	}

	void registerEventSourceAddon(MouseAddon * mouse) { al_register_event_source(eventQueue, al_get_mouse_event_source()); }
	void registerEventSourceAddon(KeyboardAddon * keyboard) { al_register_event_source(eventQueue, al_get_keyboard_event_source()); }
	void registerEventSourceAddon(DisplayAddon * display) { al_register_event_source(eventQueue, al_get_display_event_source(display->getDisplay())); }
	void registerEventSourceAddon(TimerAddon * timer) { al_register_event_source(eventQueue, al_get_timer_event_source(timer->getRefreshTimer())); }
	void registerEventSource(ALLEGRO_VIDEO *video) { al_register_event_source(eventQueue, al_get_video_event_source(video)); }
	void registerEventSource(ALLEGRO_DISPLAY * disp) { al_register_event_source(eventQueue, al_get_display_event_source(disp)); }
	void registerEventSource(ALLEGRO_TIMER * timer) { al_register_event_source(eventQueue, al_get_timer_event_source(timer)); }
	ALLEGRO_EVENT_QUEUE * getEventQueue() { return eventQueue; }

	~EventsAddon() { if (eventQueue != nullptr) al_destroy_event_queue(eventQueue); }
private:
	ALLEGRO_EVENT_QUEUE * eventQueue = nullptr;
};

class VideoAddon : public Addon {
public:
	VideoAddon() {
		if (al_init_video_addon()) 
			this->initSuccess();	
		else
			throw AllegroInitException();
	}

	~VideoAddon() { al_shutdown_video_addon(); }
};