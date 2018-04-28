// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

template<typename T>
class Neuron
{
    typedef std::vector<Neuron<T>> Layer;
    typedef std::vector<T> Values;

public:
    Neuron()
    {
        m_weights.push_back(1);
    }

    Neuron(Layer& prev_layer)
    {
        m_weights = std::vector<T>(prev_layer.size(), 1);
    }

    Neuron(std::initializer_list<T> weigths)
    {
        m_weights = weigths;
    }

    Neuron(std::initializer_list<T> weigths, double bias)
    {
        m_weights = weigths;
        m_bias = bias;
    }

    T compute(Layer& prev_layer)
    {
        if (prev_layer.size() != m_weights.size())
        {
            throw std::length_error("Neuron got input of wrong size");
        }

        m_value = sigmoid(weigthed_sum(prev_layer));

        return m_value;
    }

    T compute(Values prev_values)
    {
        Layer temp_layer = make_wrap_layer(prev_values);
        return compute(temp_layer);
    }

    void update_delta(T target)
    {
        m_delta = (target - m_value) * m_value * (1 - m_value);
    }

    void update_delta(Layer& next_layer, int neuron_index)
    {
        m_delta = 0;

        for (auto& neuron : next_layer)
        {
            m_delta += neuron.weights(neuron_index) * neuron.delta();
        }

        m_delta *= m_value * (1 - m_value);
    }

    void update_weights(Layer& input_layer)
    {
        static const double learning_rate = 0.5;

        for (int i = 0; i < input_layer.size(); i++)
        {
            m_weights[i] += learning_rate * m_delta * input_layer[i].value();
        }
    }

    void learn(Values input_values, T target_value)
    {
        Layer temp_layer = make_wrap_layer(input_values);
        compute(temp_layer);
        update_delta(target_value);
        update_weights(temp_layer);
    }

    void reset(T value) { m_value = value; }
    T value() const { return m_value; }
    T delta() const { return m_delta; }
    const std::vector<T> weights() const { return m_weights; }

private:
    T weigthed_sum(Layer& input_layer)
    {
        auto sum = 0.0;
        for (int i = 0; i < m_weights.size(); i++)
        {
            sum += input_layer[i].value() * m_weights[i];
        }
        return sum;
    }

    double sigmoid(T val)
    {
        T exp = std::exp(val);
        return exp / (exp + 1);
    }

    Layer make_wrap_layer(Values values)
    {
        Layer layer;

        for (auto& value : values)
        {
            Neuron<T> neuron;
            neuron.reset(value);
            layer.push_back(neuron);
        }

        return layer;
    }

private:
    std::vector<T> m_weights;
    double m_bias;
    T m_value;
    T m_delta;
};

#endif // NEURON_H