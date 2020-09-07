#include "City.h"

City::City() 
{
	visited = false;
	name = "";
	previousCity = "";
	xCoord = 100000;
	yCoord = 100000;
	distanceToDest = 100000;
}

City::City(string cityName)
{
	visited = false;
	name = cityName;
	previousCity = "";
	xCoord = 100000;
	yCoord = 100000;
	distanceToDest = 100000;
}

