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

void populateLocations(map<string, City>& cityMap)
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
        while (locFile >> city >> x >> y)
        {
            cityMap[city].xCoord = x;
            cityMap[city].yCoord = y;
        }
    }

}

void populateMap(map<string, City>& cityMap)
{
    string adjLine;
    ifstream adjFile;
 
    //map<string, pair<double, double>> citiesAndCoords = populateLocations();

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
                keyCity.frontier = restOfVec;
                
                if (cityMap.find(keyCity.name) == cityMap.end())
                {
                    cityMap[keyCity.name] = keyCity;
                }

                else
                {
                    vector<string> copyVector;
                    copyVector.reserve(cityMap[keyCity.name].frontier.size() + restOfVec.size());
                    copyVector.insert(copyVector.end(), cityMap[keyCity.name].frontier.begin(), cityMap[keyCity.name].frontier.end());
                    copyVector.insert(copyVector.end(), restOfVec.begin(), restOfVec.end());
                    cityMap[keyCity.name].frontier = copyVector;                  
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
    map<string, City> cityMap;
    populateMap(cityMap);
    populateLocations(cityMap);

    string startPoint;
    string endPoint;

    cout << "Enter starting point: " << endl;
    cin >> startPoint;
    cout << "Enter ending point: " << endl;
    cin >> endPoint;

    if (cityMap.find(startPoint) != cityMap.end() && cityMap.find(endPoint) != cityMap.end())
    {
        bestFirstSearch(cityMap, startPoint, endPoint);
    }
    return 0;
}