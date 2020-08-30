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
		City();
		City(string cityName);

};