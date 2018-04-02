#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include "neuron.h"

typedef std::vector<double> Input;
typedef std::vector<double> Output;
typedef std::vector<std::shared_ptr<Neuron>> Layer;

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
                auto neuron = std::make_shared<Neuron>();
                layer.push_back(neuron);
            }

            m_layers.push_back(layer);
        }

        for (int i = 1; i < m_layers.size(); i++)
        {
            Layer& previous_layer = m_layers[i - 1];
            Layer& current_layer = m_layers[i];

            for (auto neuron : current_layer)
            {
                neuron->add_dendrites(previous_layer);
            }
        }
    }

    void learn(Input input, Output output)
    {
        Layer& input_layer = get_input_layer();
        for (int i = 0; i < input.size(); i++)
        {
            input_layer[i]->set_value(input[i]);
        }
    }

    Output compute(Input input)
    {
        return Output();
    }

private:
    Layer& get_input_layer()
    {
        return m_layers[0];
    }

    Layer& get_output_layer()
    {
        return m_layers[m_layers.size() - 1];
    }

private:
    std::vector<Layer> m_layers;
};

#endif // NETWORK_H