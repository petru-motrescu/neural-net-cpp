// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class Neuron
{
public:
    Neuron()
    {
        m_weights.push_back(1);
    }

    Neuron(std::initializer_list<double> weigths)
    {
        m_weights = weigths;
    }

    double compute(std::vector<double> input_values)
    {
        return sigmoid(weigthed_sum(input_values));
    }

    void learn(std::vector<double> input_values, double expected_value)
    {
        auto sum = weigthed_sum(input_values);
        auto dif = sigmoid_derivative(sum) * (expected_value - sigmoid(sum));
        for (int i = 0; i < input_values.size(); i++)
        {
            m_weights[i] += dif / input_values[i];
        }
    }

private:
    double weigthed_sum(std::vector<double>& input_values)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += input_values[i] * m_weights[i];
        }
        return sum;
    }

    double sigmoid(double val)
    {
        double exp = std::exp(val);
        return exp / (exp + 1);
    }

    double sigmoid_derivative(double val)
    {
        double sig = sigmoid(val);
        return sig * (1 - sig);
    }

private:
    std::vector<double> m_weights;
};

#endif // NEURON_H