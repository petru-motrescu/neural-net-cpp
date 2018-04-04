// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class Neuron
{
public:
    void init_weights(int count)
    {
        m_weights = std::vector<double>(count, 1.0);
    }

    double compute(std::vector<double>& inputs)
    {
        double sum = 0;

        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += inputs[i] * m_weights[i];
        }
        
        auto ex = std::exp(sum);
        return ex / (ex + 1);
    }

private:
    std::vector<double> m_weights;
};

#endif // NEURON_H