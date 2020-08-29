#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

double calculateDistance(double initX, double initY, double finalX, double finalY)
{
    double xTerm = pow((finalX - initX), 2);
    double yTerm = pow((finalY - initY), 2);
    return sqrt(xTerm + yTerm);
}

void populateMap(map<string, vector<string>>& cityMap)
{
    stringstream ss;
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
            //
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

                if (cityMap.find(currLine[i]) == cityMap.end()) 
                {
                    //create new entry in vector, and add adjacent cities
                    cityMap[currLine[i]] = restOfVec;
                }
                else 
                {
                    //add new adjacent cities of existing entry to vector
                    vector<string> copyVector;
                    copyVector.reserve(cityMap[currLine[i]].size() + restOfVec.size());
                    copyVector.insert(copyVector.end(), cityMap[currLine[i]].begin(), cityMap[currLine[i]].end());
                    copyVector.insert(copyVector.end(), restOfVec.begin(), restOfVec.end());
                    cityMap[currLine[i]] = copyVector;
                }
                
            }

            currLine.clear();
            
        }


        adjFile.close();
    }
}

int main()
{
    
    map<string, vector<string>> cityMap;
    populateMap(cityMap);
    for (auto city : cityMap)
    {
        cout << city.first << " is adjacent to: ";
        for (int i = 0; i < city.second.size(); i++)
        {
            cout << city.second[i] << ", ";
        }

        cout << endl << endl << endl;
    }
}

