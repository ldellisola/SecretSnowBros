#include "AllegroLog.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip> 


AllegroLog::AllegroLog(std::string title, bool logToFile , TextLogFlag flag)
{
	if (this->logWindow == nullptr)
	{
		this->logWindow = al_open_native_text_log(title.c_str(), (int)flag);
	}
	this->title = title;
	this->logToFile = logToFile;
}


AllegroLog::~AllegroLog()
{
	if (this->logWindow != nullptr)
		al_close_native_text_log(this->logWindow);
	if (this->logToFile) {
		std::string fileName = title + ".log";
		std::ofstream output(fileName);
		

		output << this->log << std::endl;
		output.close();
	}
}

void AllegroLog::close()
{
	if (this->logWindow != nullptr) {
		al_close_native_text_log(logWindow);
		logWindow = nullptr;
	}
}

ALLEGRO_EVENT_SOURCE * AllegroLog::getEventSource()
{
	return al_get_native_text_log_event_source(this->logWindow);
}

AllegroLog & AllegroLog::operator<<(std::string text)
{

	std::string form = "At " + std::to_string(al_get_time()) + " seconds: " + text+ "\n";

	if (logWindow != nullptr)
		al_append_native_text_log(this->logWindow, form.c_str());
	if (this->logToFile)
		this->log += form;
	return *this;
}

AllegroLog & AllegroLog::operator<<(char letter)
{
	char text[2] = { letter,0 };

	std::string form = "At " + std::to_string(al_get_time()) + " seconds: " + text + "\n";

	if (logWindow != nullptr)
		al_append_native_text_log(this->logWindow, form.c_str());
	if (this->logToFile)
		this->log += form;

	return *this;

}

AllegroLog & AllegroLog::operator<<(int num)
{
	

	std::string form = "At " + std::to_string(al_get_time()) + " seconds: " + std::to_string(num) + "\n";
	if (logWindow != nullptr)
		al_append_native_text_log(this->logWindow, form.c_str());
	if (this->logToFile)
		this->log += form;
	return *this;

}

AllegroLog & AllegroLog::operator<<(float num)
{

	std::string form = "At " + std::to_string(al_get_time()) + " seconds: " + std::to_string(num) + "\n";

	if (logWindow != nullptr)
		al_append_native_text_log(this->logWindow, form.c_str());
	if (this->logToFile)
		this->log += form;
	return *this;

}

AllegroLog & AllegroLog::operator<<(double num)
{

	std::string form = "At " + std::to_string(al_get_time()) + " seconds: " + std::to_string(num) + "\n";

	if (logWindow != nullptr)
		al_append_native_text_log(this->logWindow, form.c_str());
	if (this->logToFile)
		this->log += form;
	return *this;
}
