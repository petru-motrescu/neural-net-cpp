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
    Neuron<double> o1{0.40, 0.45, 0.60};
    log_nl(o1.weights());
    o1.learn({0.59327, 0.596884, 1.0}, 0.01);
    log_nl(o1.weights());
}
