#pragma once
#include <string>

#include "AllwMisc/AllegroLog.h"

class Logger
{
public:
	Logger(std::string file, bool saveToFile = true) :_logger(file, saveToFile){}
	virtual ~Logger(){}

protected:
	void log(std::string data) {
		_logger << data;
	}

private:
	AllegroLog _logger;
};



