// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

class Neuron
{
public:
    double get_value()
    {
        return m_value;
    }

private:
    double m_value;
};

#endif // NEURON_H