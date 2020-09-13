#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "City.h"
#include <unordered_set>

using namespace std;

//removes duplicate elements from vector
void remove(vector<string>& v)
{
    vector<string>::iterator itr = v.begin();
    unordered_set<string> s;

    for (auto curr = v.begin(); curr != v.end(); ++curr) {
        if (s.insert(*curr).second)
            *itr++ = *curr;
    }

    v.erase(itr, v.end());
}
//calculates distance between two 2d points
double calculateDistance(double initX, double initY, double finalX, double finalY)
{
    double xTerm = pow((finalX - initX), 2);
    double yTerm = pow((finalY - initY), 2);
    return sqrt(xTerm + yTerm);
}

//reads from location file and assigns x and y coordinates to each city obj
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

//reads from adjacencies file and assigns adjacent cities to each city obj
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
                    remove(copyVector);
                    cityMap[keyCity.name].frontier = copyVector;                  
                }
                
            }

            currLine.clear();
            
        }
        adjFile.close();
    }
}

//finds path between origin and goal using best first search
vector<string> bestFirstSearch(map<string, City> cityMap, string startPoint, string endPoint)
{
    vector<string> path;
    City* start = &cityMap[startPoint];
    City* end = &cityMap[endPoint];

    City* tracker = start;
    
    path.push_back(start->name);
    while (tracker->distanceToDest != 0)
    {
        int frontierCount = tracker->frontier.size();
        int numVisited = 0;
        double minDistance = 100000000;
        string closestCity = tracker->name;
        tracker->visited = true;
        for (int i = 0; i < frontierCount; i++)
        {
            City nextCity = cityMap[tracker->frontier[i]];
            if (nextCity.visited == false)
            {
                double distanceToDest = calculateDistance(nextCity.xCoord, nextCity.yCoord, end->xCoord, end->yCoord);
                cityMap[nextCity.name].distanceToDest = distanceToDest;

                if (distanceToDest < minDistance)
                {
                    closestCity = nextCity.name;
                    minDistance = distanceToDest;
                }
            }
            
        }

             
        if (closestCity == tracker->name)
        {
            if (tracker->previousCity != "")
                tracker = &cityMap[tracker->previousCity];

            else
                return vector<string>();
        }

        else
        {
            path.push_back(closestCity);
            cityMap[closestCity].visited = true;
            cityMap[closestCity].previousCity = tracker->name;
            tracker = &cityMap[closestCity];
        }
        
    }

    return path;

}



int main()
{
    vector<string> path;
    map<string, City> cityMap;
    populateMap(cityMap);
    populateLocations(cityMap);
    char ans = 'Y';

    string startPoint;
    string endPoint;

    while (ans == 'Y')
    {
        cout << "Enter starting point: " << endl;
        cin >> startPoint;
        cout << "Enter ending point: " << endl;
        cin >> endPoint;


        if (cityMap.find(startPoint) != cityMap.end() && cityMap.find(endPoint) != cityMap.end())
        {
            if (startPoint == endPoint)
                path.push_back(startPoint);
            else
                path = bestFirstSearch(cityMap, startPoint, endPoint);
        }

        if (path.size() != 0)
        {
            cout << "Path: " << path[0];
            for (int i = 1; i < path.size(); i++)
                cout << " -> " << path[i];
        }

        else
            cout << "No path found";
        cout << endl << endl << endl;

        cout << "Again? (Y/N)" << endl;
        cin >> ans;
        ans = toupper(ans);
    }
    
    return 0;
}