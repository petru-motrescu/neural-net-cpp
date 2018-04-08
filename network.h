#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>

#include "neuron.h"
#include "utils.h"

template<typename T>
class Network
{
    typedef std::vector<Neuron<T>> Layer;
    typedef std::vector<T> Values;

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
            utils::log_nl(input_values);
        }

        return input_values;
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H