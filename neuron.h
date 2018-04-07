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

    double compute(std::vector<double>& input_values)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += input_values[i] * m_weights[i];
        }
        
        auto ex = std::exp(sum);
        return ex / (ex + 1);
    }

private:
    std::vector<double> m_weights;
};

#endif // NEURON_H