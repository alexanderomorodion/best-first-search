#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "City.h"

using namespace std;

double calculateDistance(double initX, double initY, double finalX, double finalY)
{
    double xTerm = pow((finalX - initX), 2);
    double yTerm = pow((finalY - initY), 2);
    return sqrt(xTerm + yTerm);
}

map<string, pair<double, double>> populateLocations()
{
    string locLine;
    ifstream locFile;

    string city;
    double x;
    double y;
    map<string, pair<double, double>> citiesAndCoords;

    locFile.open("coordinates.txt");

    if (locFile.is_open())
    {
        while (getline(locFile, locLine))
        {
            locFile >> city >> x >> y;
            citiesAndCoords[city] = { x, y };
        }
    }

    return citiesAndCoords;

}

void populateMap(map<City, vector<string>>& cityMap)
{
    string adjLine;
    ifstream adjFile;
 
    map<string, pair<double, double>> citiesAndCoords = populateLocations();

    adjFile.open("Adjacencies.txt");

    vector<string> currLine;
    
    if (adjFile.is_open())
    {
        while (getline(adjFile, adjLine))
        {
            string city = "";
            
            for (int i = 0; i < adjLine.length(); i++)
            {
                if (adjLine[i] == ' ' && city.length() == 0)
                {
                    continue;
                }

                else if (adjLine[i] == ' ')
                {
                    currLine.push_back(city);
                    city = "";
                    continue;
                }

                else
                    city += adjLine[i];
            }

            if (city.find_first_not_of(' ') != string::npos)
            {
                currLine.push_back(city);
            }   
            
            for (int i = 0; i < currLine.size(); i++) 
            {
                vector<string> restOfVecBefore = vector<string>(currLine.begin(), currLine.end() - currLine.size() + i);
                vector<string> restOfVecAfter = vector<string>(currLine.begin() + i + 1, currLine.end());
                vector<string> restOfVec;
                restOfVec.reserve(restOfVecBefore.size() + restOfVecAfter.size());
                restOfVec.insert(restOfVec.end(), restOfVecAfter.begin(), restOfVecAfter.end());
                restOfVec.insert(restOfVec.end(), restOfVecBefore.begin(), restOfVecBefore.end());

                City keyCity = City(currLine[i]);

                map<string, pair<double, double>>::iterator it;
                it = citiesAndCoords.find(keyCity.name);
                if (it != citiesAndCoords.end())
                {
                    keyCity.xCoord = it->second.first;
                    keyCity.yCoord = it->second.second;
                }
                    
                
                if (cityMap.find(keyCity.name) == cityMap.end())
                {
                    cityMap[keyCity] = restOfVec;
                }

                else
                {
                    vector<string> copyVector;
                    copyVector.reserve(cityMap[keyCity].size() + restOfVec.size());
                    copyVector.insert(copyVector.end(), cityMap[keyCity].begin(), cityMap[keyCity].end());
                    copyVector.insert(copyVector.end(), restOfVec.begin(), restOfVec.end());
                    cityMap[keyCity] = copyVector;
                    break;                   
                }
                
            }

            currLine.clear();
            
        }
        adjFile.close();
    }
}

bool sameName(City cityObj, string cityName)
{
    return cityObj.name == cityName;
}



int main()
{
    map<City, vector<string>> cityMap;
    populateMap(cityMap);

    return 0;
}