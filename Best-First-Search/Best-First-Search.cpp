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

void populateMap(vector<City>& cityMap)
{
    string adjLine;
    string locLine;
    ifstream adjFile;
    ifstream locFile;
    adjFile.open("Adjacencies.txt.");

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
                bool cityFound = false;
                for (int i = 0; i < cityMap.size(); i++)
                {
                    if (cityMap[i].name == keyCity.name)
                    {
                        vector<string> copyVector;
                        copyVector.reserve(cityMap[i].adjacentCities.size() + restOfVec.size());
                        copyVector.insert(copyVector.end(), cityMap[i].adjacentCities.begin(), cityMap[i].adjacentCities.end());
                        copyVector.insert(copyVector.end(), restOfVec.begin(), restOfVec.end());
                        cityMap[i].adjacentCities = copyVector;
                        cityFound = true;
                        break;
                    }
                }

                if (!cityFound) 
                {
                    //create new entry in vector, and add adjacent cities
                    keyCity.adjacentCities = restOfVec;
                    cityMap.push_back(keyCity);
                }
                
            }

            currLine.clear();
            
        }


        adjFile.close();
    }
}

int main()
{
    
    vector<City> cityMap;
    populateMap(cityMap);
    for (auto city : cityMap)
    {
        cout << city.name << " is adjacent to: ";
        for (int i = 0; i < city.adjacentCities.size(); i++)
        {
            cout << city.adjacentCities[i] << ", ";
        }

        cout << endl << endl << endl;
    }
}

