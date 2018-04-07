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
    Network(std::initializer_list<int> neurons_per_layer)
    {
        int weight_count = 1;

        for (int count : neurons_per_layer)
        {
            Layer layer;

            for (int i = 0; i < count; i++)
            {
                Neuron neuron(weight_count);
                layer.push_back(neuron);
                weight_count = count;
            }

            m_layers.push_back(layer);
        }
    }

    void learn(Values input_values, Values expected_values)
    {
        for (auto& layer : m_layers)
        {
            for (auto& neuron : layer)
            {
                neuron.compute(input_values);
            }
        }

        Utils::log_vector_nl(output_values());

        // TODO back propagation
    }
    
    Values compute(Values input_values)
    {
        for (auto& layer : m_layers)
        {
            for (auto& neuron : layer)
            {
                neuron.compute(input_values);
            }
        }

        return output_values();
    }

private:
    Values output_values()
    {
        Values output_values;
        
        for (auto& neuron : output_layer())
        {
            output_values.push_back(neuron.get_value());
        }

        return output_values;
    }

    Layer& output_layer()
    {
        return m_layers[m_layers.size() - 1];
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H