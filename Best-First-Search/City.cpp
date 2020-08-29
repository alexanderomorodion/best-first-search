#include "City.h"

City::City() 
{
	visited = false;
	name = "";
	previousCity = "";
	distanceToDest = 0;
	adjacentCities = {};
}

City::City(string cityName)
{
	visited = false;
	name = cityName;
	previousCity = "";
	distanceToDest = 0;
	adjacentCities = {};
}
