#include "City.h"

City::City() 
{
	visited = false;
	name = "";
	previousCity = "";
	xCoord = 0;
	yCoord = 0;
	distanceToDest = 0;
}

City::City(string cityName)
{
	visited = false;
	name = cityName;
	previousCity = "";
	distanceToDest = 0;
}

