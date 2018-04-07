// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class Neuron
{
public:
    Neuron(int input_size)
    {
        m_weights = std::vector<double>(input_size, 1.0);
    }

    void compute(std::vector<double>& input_values)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += input_values[i] * m_weights[i];
        }
        
        auto ex = std::exp(sum);
        m_value = ex / (ex + 1);
    }

    double get_value() const
    {
        return m_value;
    }

private:
    double m_value;
    std::vector<double> m_weights;
};

#endif // NEURON_H