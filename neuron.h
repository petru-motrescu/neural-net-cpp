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

    T compute(std::vector<T> input_values)
    {
        if (input_values.size() != m_weights.size())
        {
            throw std::length_error("Neuron got input of wrong size");
        }

        return sigmoid(weigthed_sum(input_values));
    }

    void learn(std::vector<T> input_values, T expected_value)
    {
        auto sum = weigthed_sum(input_values);
        auto dif = sigmoid_derivative(sum) * (expected_value - sigmoid(sum));
        for (int i = 0; i < input_values.size(); i++)
        {
            m_weights[i] += dif / input_values[i];
        }
    }

private:
    T weigthed_sum(std::vector<T>& input_values)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += input_values[i] * m_weights[i];
        }
        return sum;
    }

    double sigmoid(T val)
    {
        T exp = std::exp(val);
        return exp / (exp + 1);
    }

    double sigmoid_derivative(T val)
    {
        T sig = sigmoid(val);
        return sig * (1 - sig);
    }

private:
    std::vector<T> m_weights;
};

#endif // NEURON_H