// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

using namespace std;
using namespace utils;

int main()
{
    Neuron<double> n{0.15, 0.2, 0.35};
    cout << n.compute({0.05, 0.1, 1.0}) << endl;
}
