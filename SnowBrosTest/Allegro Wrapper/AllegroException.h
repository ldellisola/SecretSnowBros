#pragma once
#include <exception>


class InvalidLoadException :
	public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "The file couldn't be loaded";
	}
};

class AllegroInitException :
	public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Allegro could't be initialized";
	}
};

