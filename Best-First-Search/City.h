#pragma once
#include <string>
#include <vector>

using namespace std;

class City 
{
	public:
		bool visited;
		string name;
		string previousCity;
		double distanceToDest;
		vector<string> adjacentCities;
		City();
		City(string cityName);

};