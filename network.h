// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>

#include "neuron.h"
#include "utils.h"

using namespace std; // TEMPX

template<typename T>
class Network
{
public:
    typedef std::vector<Neuron<T>> Layer;
    typedef std::vector<T> Values;

public:
    Network()
    {
        m_learn_rate = 1;
    }

    void add_layers(std::vector<int> neuron_counts)
    {
        for (int i = 0; i < neuron_counts.size(); i++)
        {
            bool add_bias = (i < (neuron_counts.size() - 1));
            add_layer(neuron_counts[i], add_bias);
        }
    }

    void add_layer(int neuron_count, bool add_bias_neuron = true)
    {
        int last_layer_size = (m_layers.size() > 0) ? m_layers[m_layers.size() - 1].size() : 0;
        Layer layer;

        for (int i = 0; i < neuron_count; i++)
        {
            if (last_layer_size > 0)
            {
                srand(m_total_neuron_count);
                layer.push_back(Neuron<T>(last_layer_size));
            }
            else
            {
                layer.push_back(Neuron<T>());
            }

            m_total_neuron_count++;
        };

        if (add_bias_neuron)
        {
            layer.push_back(Neuron<T>());
            m_total_neuron_count++;
        }

        m_layers.push_back(layer);
    }

    void set_learn_rate(T rate)
    {
        m_learn_rate = rate;
    }

    Values compute(Values input_values)
    {
        // Copy the values into the input layer.
        Layer& input_layer = m_layers[0];
        for (int i = 0; i < input_values.size(); i++)
        {
            input_layer[i].reset(input_values[i]);
        }

        // Compute the values in all layers.
        for (int li = 1; li < m_layers.size(); li++)
        {
            for (int ni = 0; ni < m_layers[li].size(); ni++)
            {
                m_layers[li][ni].compute(m_layers[li - 1]);
            }
        }

        // Copy the values from the output layer.
        Values output_values;
        Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int ni = 0; ni < output_layer.size(); ni++)
        {
            if (!output_layer[ni].is_bias())
            {
                output_values.push_back(output_layer[ni].value());
            }
        }

        return output_values;
    }

    void learn(Values input_values, Values target_values)
    {
        compute(input_values);

        // Compute the deltas in the output layer.
        Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int ni = 0; ni < target_values.size(); ni++)
        {
            output_layer[ni].update_delta(target_values[ni]);
        }

        // Compute the deltas in hidden layers, backwards.
        for (int li = m_layers.size() - 2; li >= 1; li--)
        {
            Layer& curr_layer = m_layers[li];
            Layer& next_layer = m_layers[li + 1];

            for (int ni = 0; ni < curr_layer.size(); ni++)
            {
                curr_layer[ni].update_delta(next_layer, ni);
            }
        }

        // Adjust the weights in all layers.
        for (int li = 1; li < m_layers.size(); li++)
        {
            Layer& curr_layer = m_layers[li];
            Layer& prev_layer = m_layers[li - 1];
            
            for (int ni = 0; ni < curr_layer.size(); ni++)
            {
                curr_layer[ni].update_weights(prev_layer, m_learn_rate);
            }
        }
    }

    void log()
    {
        std::cout << std::endl << "Network with " << m_total_neuron_count << " neurons" << std::endl << std::endl;

        for (int li = 0; li < m_layers.size(); li++)
        {
            std::cout << "###" << std::endl << std::endl;

            for (int ni = 0; ni < m_layers[li].size(); ni++)
            {
                std::cout << "Neuron[" << li << "][" << ni << "] Value = " << m_layers[li][ni].value();
                auto& weights = m_layers[li][ni].weights();
                if (weights.size() > 0)
                {
                    std::cout << " Weights = ";
                    utils::log_nl(weights); 
                }
                
                std::cout << std::endl;
            }

            std::cout << std::endl;
        }
    }

private:
    std::vector<Layer> m_layers;
    int m_total_neuron_count;
    T m_learn_rate;
};

#endif // NETWORK_H