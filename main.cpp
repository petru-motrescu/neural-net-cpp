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
    Network<double>::Layer input_layer = { Neuron<double>(), Neuron<double>() };
    Network<double>::Layer hidden_layer = { Neuron<double>(input_layer), Neuron<double>(input_layer) };
    Network<double>::Layer output_layer = { Neuron<double>(hidden_layer), Neuron<double>(hidden_layer) };
    Network<double> net = { input_layer, hidden_layer, output_layer };
    utils::log_nl(net.compute({ 1, 1 }));
}
