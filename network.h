#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include "layer.h"
#include "utils.h"

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
            Layer layer(count);
            m_layers.push_back(layer);
        }

        m_layers[0].init_weights(1);

        for (int i = 1; i < m_layers.size(); i++)
        {
            m_layers[i].init_weights(m_layers[i - 1].neuron_count());
        }
    }

    void learn(std::vector<double>& input, std::vector<double>& expected)
    {
        auto values = input;

        for (auto& layer : m_layers)
        {
            values = layer.compute(values);
        }

        Utils::log_vector_nl(expected);
        Utils::log_vector_nl(values);

        // TODO back propagation
    }
    
    std::vector<double> compute(std::vector<double>& input)
    {
        std::vector<double> values = input;

        for (auto& layer : m_layers)
        {
            values = layer.compute(values);
        }

        return values;
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H