// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include "neuron.h"

class Layer
{
public:
    Layer(int neuron_count)
    {
        for (int i = 0; i < neuron_count; i++)
        {
            Neuron neuron;
            m_neurons.push_back(neuron);
        }
    }

    void init_weights(int count)
    {
        for (auto& neuron : m_neurons)
        {
            neuron.init_weights(count);
        }
    }

    std::vector<double> compute(std::vector<double>& inputs)
    {
        std::vector<double> values;

        for (auto& neuron : m_neurons)
        {
            values.push_back(neuron.compute(inputs));
        }

        return values;
    }

    int neuron_count() const
    {
        return m_neurons.size();
    }

private:
    std::vector<Neuron> m_neurons;
};

#endif // LAYER_H