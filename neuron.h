// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

class Neuron;

struct Dendrite
{
    std::shared_ptr<Neuron> source;
    double weight;
};

class Neuron
{
public:
    void add_dendrite(std::shared_ptr<Neuron> source)
    {
        Dendrite dendrite;
        dendrite.source = source;
        dendrite.weight = 1.0;
        m_dendrites.push_back(dendrite);
    }

    void add_dendrites(std::vector<std::shared_ptr<Neuron>>& sources)
    {
        for (auto source : sources)
        {
            add_dendrite(source);
        }
    }

    void set_value(double value)
    {
        m_value = value;
    }

    double get_value()
    {
        return m_value;
    }

private:
    double m_value;
    std::vector<Dendrite> m_dendrites;
};

#endif // NEURON_H