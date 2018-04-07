// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

int main()
{
    Layer input_layer;
    input_layer.push_back(Neuron());
    input_layer.push_back(Neuron());

    Layer hidden_layer;
    hidden_layer.push_back(Neuron{0.8, 0.2});
    hidden_layer.push_back(Neuron{0.4, 0.9});
    hidden_layer.push_back(Neuron{0.3, 0.5});

    Layer output_layer;
    output_layer.push_back(Neuron{0.3, 0.5, 0.9});

    Network net{input_layer, hidden_layer, output_layer};
    net.compute({1, 1});
}
