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
        Layer layer;

        for (int i = 0; i < neuron_count; i++)
        {
            if (m_layers.size() > 0)
            {
                layer.push_back(Neuron<T>(m_layers[m_layers.size() - 1]));
            }
            else
            {
                layer.push_back(Neuron<T>());
            }
        };

        if (add_bias_neuron)
        {
            layer.push_back(Neuron<T>());
        }

        m_layers.push_back(layer);
    }

    void set_learn_rate(T rate)
    {
        m_learn_rate = rate;
    }

    Values compute(Values input_values)
    {
        set_input(input_values);

        for (int i = 1; i < m_layers.size(); i++)
        {
            compute(m_layers[i], m_layers[i - 1]);
        }

        return get_output();
    }

    void learn(Values input_values, Values target_values)
    {
        compute(input_values);
        update_output_deltas(target_values);
        update_hidden_deltas();
        update_weights();
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
        Values output_values;
        Layer& output_layer = m_layers[m_layers.size() - 1];

        for (int i = 0; i < output_layer.size(); i++)
        {
            if (!output_layer[i].is_bias())
            {
                output_values.push_back(output_layer[i].value());
            }
        }

        return output_values;
    }

    void compute(Layer& curr_layer, Layer& prev_layer)
    {
        for (int i = 0; i < curr_layer.size(); i++)
        {
            curr_layer[i].compute(prev_layer);
        }
    }

    void update_hidden_deltas()
    {
        for (int i = m_layers.size() - 2; i >= 0; i--)
        {
            update_hidden_deltas(m_layers[i], m_layers[i + 1]);
        }
    }

    void update_hidden_deltas(Layer& curr_layer, Layer& next_layer)
    {
        for (int i = 0; i < curr_layer.size(); i++)
        {
            curr_layer[i].update_delta(next_layer, i);
        }
    }

    void update_output_deltas(Values target_values)
    {
        Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int i = 0; i < target_values.size(); i++)
        {
            output_layer[i].update_delta(target_values[i]);
        }
    }

    void update_weights()
    {
        for (int i = 1; i < m_layers.size(); i++)
        {
            update_weights(m_layers[i], m_layers[i - 1]);
        }
    }

    void update_weights(Layer& curr_layer, Layer& prev_layer)
    {
        for (int i = 0; i < curr_layer.size(); i++)
        {
            curr_layer[i].update_weights(prev_layer, m_learn_rate);
        }
    }

private:
    std::vector<Layer> m_layers;
    T m_learn_rate;
};

#endif // NETWORK_H