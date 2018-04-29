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
    using Neuron = Neuron<double>;
    using Layer = Network<double>::Layer;
    
    Layer input =
    {
        Neuron(),
        Neuron(),
        Neuron() // bias
    };

    Layer hidden =
    {
        Neuron{0.15, 0.20, 0.35},
        Neuron{0.25, 0.30, 0.35},
        Neuron() // bias
    };

    Layer output =
    {
        Neuron{0.40, 0.45, 0.60},
        Neuron{0.50, 0.55, 0.60}
    };

    Network<double> net = { input, hidden, output };
    utils::log_nl(net.compute({ 0.05, 0.10 }));

    net.learn({0.05, 0.10}, {0.01, 0.99});
}
