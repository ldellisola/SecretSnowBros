#pragma once
#include <string>

#include "AllwMisc/AllegroLog.h"

class Logger
{
public:
	Logger(std::string file, bool saveToFile = true) :_logger(file, saveToFile){}
	virtual ~Logger(){}


	void log(std::string data) {
		_logger << (data+"\n");
	}

private:
	AllegroLog _logger;
};



