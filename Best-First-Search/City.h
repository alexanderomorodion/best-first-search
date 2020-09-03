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
		double xCoord;
		double yCoord;
		double distanceToDest;
		City();
		City(string cityName);

		bool operator < (const City& cityObj) const
		{
			if (cityObj.name < this->name)
				return true;
		}

};