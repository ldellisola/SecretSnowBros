#include "AllegroClassV2.h"


AllegroClass::AllegroClass(Allegro::InitMode mode, float width, float height, float fps)
{
	if (al_init())
		this->success = true;

	switch (mode) {
	case Allegro::InitMode::Full:
		if (success)
			initNativeDialogAddon();
		if (success)
			initVideoAddon();
		if (success)
			initAudioAddon();
		if (success)
			initImageAddon();
	case Allegro::InitMode::Events:
		if (success)
			initEventsAddon();
		if (success)
			initMouseAddon();
		if (success && fps == Allegro::NoValue)
			initTimerAddon();
		else if (success)
			initTimerAddon(fps);
	case Allegro::InitMode::Basic:
		if (success)
			initDisplayAddon(width, height);
		if (success)
			initKeyboardAddon();
		if (success)
			initFontAddon();
		if (success)
			initPrimitivesAddon();
	case Allegro::InitMode::Empty:
		break;
	}

	if (success && (mode == Allegro::InitMode::Full || mode == Allegro::InitMode::Events) )
		registerAllAvailableEventsSource();
}

AllegroClass::AllegroClass()
{
	if (al_init())
		this->success = true;
}

void AllegroClass::initImageAddon()
{
	if (imageAddon == nullptr) {
		this->imageAddon = new ImageAddon();
		this->success = imageAddon->getSuccess();
	}
}

void AllegroClass::initAudioAddon()
{
	if (audioAddon == nullptr) {
		this->audioAddon = new AudioAddon();
		this->success = audioAddon->getSuccess();
	}
}

void AllegroClass::initFontAddon()
{
	if (fontAddon == nullptr) {
		this->fontAddon = new FontAddon();
		this->success = fontAddon->getSuccess();
	}
}

void AllegroClass::initKeyboardAddon()
{
	if (keyboardAddon == nullptr) {
		this->keyboardAddon = new KeyboardAddon();
		this->success = keyboardAddon->getSuccess();
	}
}

void AllegroClass::initDisplayAddon(float x, float y)
{
	if (displayAddon == nullptr) {
		this->displayAddon = new DisplayAddon(x, y);
		this->success = displayAddon->getSuccess();
	}
}

void AllegroClass::initMouseAddon()
{
	if (mouseAddon == nullptr) {
		this->mouseAddon = new MouseAddon();
		this->success = mouseAddon->getSuccess();
	}
}

void AllegroClass::initEventsAddon()
{
	if (eventsAddon == nullptr) {
		this->eventsAddon = new EventsAddon();
		this->success = eventsAddon->getSuccess();
	}
}

void AllegroClass::initTimerAddon(float fps)
{
	if (this->timerAddon == nullptr) {
		this->timerAddon = new TimerAddon(fps);
		this->success = timerAddon->getSuccess();
	}
}

void AllegroClass::initTimerAddon()
{
	if (this->timerAddon == nullptr) {
		this->timerAddon = new TimerAddon();
		this->success = timerAddon->getSuccess();
	}
}

void AllegroClass::initPrimitivesAddon()
{
	if (primitivesAddon == nullptr) {
		this->primitivesAddon = new PrimitivesAddon();
		this->success = primitivesAddon->getSuccess();
	}
}

void AllegroClass::initVideoAddon()
{
	if (videoAddon == nullptr) {
		this->videoAddon = new VideoAddon();
		this->success = videoAddon->getSuccess();
	}
}

void AllegroClass::initNativeDialogAddon()
{
	if (nativeDialogAddon == nullptr) {
		this->nativeDialogAddon = new NativeDialogAddon();
		this->success = nativeDialogAddon->getSuccess();
	}
}

void AllegroClass::uninstallImageAddon()
{
	if (imageAddon != nullptr)
		delete imageAddon;
	imageAddon = nullptr;
}

void AllegroClass::uninstallAudioAddon()
{
	if (audioAddon != nullptr)
		delete audioAddon;
	audioAddon = nullptr;
}

void AllegroClass::uninstallFontAddon()
{
	if (fontAddon != nullptr)
		delete fontAddon;
	fontAddon = nullptr;
}

void AllegroClass::uninstallKeyboardAddon()
{
	if (keyboardAddon != nullptr)
		delete keyboardAddon;
	keyboardAddon = nullptr;
}

void AllegroClass::uninstallDisplayAddon()
{
	if (displayAddon != nullptr)
		delete displayAddon;
	displayAddon = nullptr;
}

void AllegroClass::uninstallMouseAddon()
{
	if (mouseAddon != nullptr)
		delete mouseAddon;
	mouseAddon = nullptr;
}

void AllegroClass::uninstallEventsAddon()
{
	if (eventsAddon != nullptr)
		delete eventsAddon;
	eventsAddon = nullptr;
}

void AllegroClass::uninstallTimerAddon()
{
	if (timerAddon != nullptr)
		delete timerAddon;
	timerAddon = nullptr;
}

void AllegroClass::uninstallPrimitivesAddon()
{
	if (primitivesAddon != nullptr)
		delete primitivesAddon;
	primitivesAddon = nullptr;
}

void AllegroClass::uninstallVideoAddon()
{
	if (videoAddon != nullptr)
		delete videoAddon;
	videoAddon = nullptr;
}

void AllegroClass::uninstallNativeDialogAddon()
{
	if (nativeDialogAddon != nullptr)
		delete nativeDialogAddon;
	nativeDialogAddon = nullptr;
}

void AllegroClass::registerAllAvailableEventsSource()
{
	if (eventsAddon != nullptr) {
		if (this->timerAddon != nullptr && this->timerAddon->getRefreshTimer() !=nullptr)
			eventsAddon->registerEventSourceAddon(timerAddon);
		if (this->keyboardAddon != nullptr)
			eventsAddon->registerEventSourceAddon(keyboardAddon);
		if (this->mouseAddon != nullptr)
			eventsAddon->registerEventSourceAddon(mouseAddon);
		if (this->displayAddon != nullptr && this->displayAddon->getDisplay() != nullptr)
			eventsAddon->registerEventSourceAddon(displayAddon);
	}
}

void AllegroClass::registerEventSource(ALLEGRO_VIDEO * video)
{
	if (this->eventsAddon != nullptr)
		eventsAddon->registerEventSource(video);
}

void AllegroClass::registerEventSource(ALLEGRO_DISPLAY * disp)
{
	if (this->eventsAddon != nullptr)
		eventsAddon->registerEventSource(disp);
}

void AllegroClass::registerEventSource(ALLEGRO_TIMER * timer)
{
	if (this->eventsAddon != nullptr)
		eventsAddon->registerEventSource(timer);
}

void AllegroClass::unregisterEventSource(ALLEGRO_VIDEO * video)
{
	if (eventsAddon != nullptr)
		al_unregister_event_source(this->eventsAddon->getEventQueue(), al_get_video_event_source(video));
}

void AllegroClass::unregisterEventSource(ALLEGRO_DISPLAY * disp)
{
	if (eventsAddon != nullptr)
		al_unregister_event_source(this->eventsAddon->getEventQueue(), al_get_display_event_source(disp));
}

void AllegroClass::unregisterEventSource(ALLEGRO_TIMER * timer)
{
	if (eventsAddon != nullptr)
		al_unregister_event_source(this->eventsAddon->getEventQueue(), al_get_timer_event_source(timer));
}

ALLEGRO_EVENT_QUEUE * AllegroClass::getEventQueue()
{
	return this->eventsAddon->getEventQueue();
}

void AllegroClass::setDisplayColor(ALLEGRO_COLOR color)
{
	displayAddon->setDisplayColor(color);
}

void AllegroClass::setDisplayColor(const char * color)
{
	displayAddon->setDisplayColor(al_color_name(color));
}

void AllegroClass::setDisplayName(const char * name)
{
	al_set_window_title(displayAddon->getDisplay(), name);
}

void AllegroClass::setMainDisplay()
{
	al_set_target_backbuffer(this->displayAddon->getDisplay());
}

void AllegroClass::updateDisplay()
{
	displayAddon->updateDisplay();
}

ALLEGRO_DISPLAY * AllegroClass::getDisplay()
{
	return displayAddon->getDisplay();
}


AllegroClass::~AllegroClass()
{
	this->uninstallImageAddon();
	this->uninstallAudioAddon();
	this->uninstallFontAddon();
	this->uninstallKeyboardAddon();
	this->uninstallDisplayAddon();
	this->uninstallMouseAddon();
	this->uninstallEventsAddon();
	this->uninstallTimerAddon();
	this->uninstallPrimitivesAddon();
	this->uninstallVideoAddon();
}

bool AllegroClass::inhibitScreenSaver()
{
	return al_inhibit_screensaver(true);
}

bool AllegroClass::allowScreenSaver()
{
	return al_inhibit_screensaver(false);
}
