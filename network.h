#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <iostream>
#include <initializer_list>
#include "neuron.h"

typedef std::vector<Neuron> Layer;
typedef std::vector<double> Input;
typedef std::vector<double> Output;

class Network
{
public:
    // Constructs a network given the list of layers.
    //
    // For example, Network net{2, 3, 1}; creates a network that:
    // - 2 neurons in the input layer
    // - 3 neurons in the hidden layer
    // - 1 neuron in the output layer
    Network(std::initializer_list<int> layers)
    {
        for (int count : layers)
        {
            Layer layer;

            for (int i = 0; i < count; i++)
            {
                Neuron neuron;
                layer.push_back(neuron);
            }

            m_layers.push_back(layer);
        }
    }

    void learn(Input input, Output output)
    {
        
    }

    Output compute(Input input)
    {
        return Output();
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H