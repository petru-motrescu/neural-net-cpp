#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>

#include "neuron.h"
#include "utils.h"

typedef std::vector<Neuron> Layer;
typedef std::vector<double> Values;

class Network
{
public:
    Network(std::initializer_list<Layer> layers)
    {
        m_layers = layers;
    }
    
    Values compute(Values input_values)
    {
        for (int i = 1; i < m_layers.size(); i++)
        {
            Values layer_values;

            for (auto& neuron : m_layers[i])
            {
                layer_values.push_back(neuron.compute(input_values));
            }

            input_values = layer_values;
            Utils::log_vector_nl(input_values);
        }

        return input_values;
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H