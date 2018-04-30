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
    Network<float> network;
    network.add_layers({3, 2, 1});

    cout << "First guess (expecting 0): " << endl;
    log_nl(network.compute({0, 0, 0}));

    for (int i = 0; i < 100000; i++)
    {
        network.learn({1, 1, 1}, {1});
        network.learn({1, 1, 0}, {1});
        network.learn({1, 0, 1}, {1});
        network.learn({1, 0, 0}, {1});
        network.learn({0, 1, 1}, {0});
        network.learn({0, 1, 0}, {0});
        network.learn({0, 0, 1}, {0});
    }

    cout << "After learning (expecting 0): " << endl;
    log_nl(network.compute({0, 0, 0}));
}