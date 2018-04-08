// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

template<typename T>
class Neuron
{
public:
    Neuron()
    {
        m_weights.push_back(1);
    }

    Neuron(std::initializer_list<T> weigths)
    {
        m_weights = weigths;
    }

    T compute(std::vector<T> inputs)
    {
        if (inputs.size() != m_weights.size())
        {
            throw std::length_error("Neuron got input of wrong size");
        }

        return sigmoid(weigthed_sum(inputs));
    }

    void learn(std::vector<T> inputs, T target)
    {
        // Based on: https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/

        auto value = compute(inputs);
        auto deriv = value * (1 - value);
        auto delta = (target - value) * deriv;
        auto alpha = 0.5; // learning rate

        for (int i = 0; i < m_weights.size(); i++)
        {
            m_weights[i] += alpha * delta * inputs[i];
        }
    }

private:
    T weigthed_sum(std::vector<T>& inputs)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += inputs[i] * m_weights[i];
        }
        return sum;
    }

    double sigmoid(T val)
    {
        T exp = std::exp(val);
        return exp / (exp + 1);
    }

private:
    std::vector<T> m_weights;
};

#endif // NEURON_H