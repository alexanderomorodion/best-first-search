#include <iostream>
#include <cmath>

using namespace std;

double calculateDistance(double initX, double initY, double finalX, double finalY)
{
    double xTerm = pow((finalX - initX), 2);
    double yTerm = pow((finalY - initY), 2);
    return sqrt(xTerm + yTerm);
}

int main()
{
    cout << calculateDistance(-7, -4, 17, 6.5);
}

