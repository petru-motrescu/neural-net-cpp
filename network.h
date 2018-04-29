// Petru Motrescu <petru.motrescu@gmail.com>, 2018

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
public:
    typedef std::vector<Neuron<T>> Layer;
    typedef std::vector<T> Values;

public:
    Network(std::initializer_list<Layer> layers)
    {
        m_layers = layers;
    }
    
    Values compute(Values input_values)
    {
        set_input(input_values);

        for (int li = 1; li < m_layers.size(); li++)
        {
            for (auto& neuron : m_layers[li])
            {
                neuron.compute(m_layers[li - 1]);
            }
        }

        return get_output();
    }

    void learn(Values input_values, Values target_values)
    {
        compute(input_values);

        Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int ni = 0; ni < output_layer.size(); ni++)
        {
            output_layer[ni].update_delta(target_values[ni]);
        }

        for (int li = m_layers.size() - 2; li >= 0; li--)
        {
            Layer& curr_layer = m_layers[li];
            Layer& next_layer = m_layers[li + 1];
            for (int ni = 0; ni < curr_layer.size(); ni++)
            {
                curr_layer[ni].update_delta(next_layer, ni);
            }
        }

        for (int li = 1; li < m_layers.size(); li++)
        {
            for (auto& neuron : m_layers[li])
            {
                neuron.update_weights(m_layers[li - 1]);
            }
        }
    }

private:
    void set_input(Values input_values)
    {
        Layer& input_layer = m_layers[0];
        for (int i = 0; i < input_values.size(); i++)
        {
            input_layer[i].reset(input_values[i]);
        }
    }

    Values get_output()
    {
        Layer& output_layer = m_layers[m_layers.size() - 1];
        Values output_values;

        for (int ni = 0; ni < output_layer.size(); ni++)
        {
            output_values.push_back(output_layer[ni].value());
        }

        return output_values;
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H