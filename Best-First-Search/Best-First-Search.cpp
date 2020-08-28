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

void populateMap(map<string, vector<string>> cityMap)
{
    stringstream ss;
    string adjLine;
    string locLine;
    ifstream adjFile;
    ifstream locFile;
    adjFile.open("Adjacencies.txt.");

    if (adjFile.is_open())
    {
        while (getline(adjFile, adjLine))
        {
            ss << adjLine;
            string keyCity = adjLine[0];
            
        }


        adjFile.close();
    }
}

int main()
{
    
    map<string, vector<string>> cityMap;
    populateMap(cityMap);
}

