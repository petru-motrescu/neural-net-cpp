// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

template<typename T>
class Neuron {

    typedef std::vector<Neuron<T>> Layer;
    typedef std::vector<T> Values;

public:
    Neuron() {
        // Bias neurons must have always the value 1
        m_value = 1;
    }

    Neuron(int weight_count) {
        for (int i = 0; i < weight_count; i++) {
            m_weights.push_back(1 / (T)rand());
        }
    }

    Neuron(std::initializer_list<T> weigths) {
        m_weights = weigths;
    }

    T compute(Layer& prev_layer) {

        if (is_bias()) { return m_value; }

        if (prev_layer.size() != m_weights.size()) {
            std::string msg = "Neuron got input of wrong size. Expected: ";
            msg += std::to_string(m_weights.size());
            msg += ", Actual: ";
            msg += std::to_string(prev_layer.size());
            throw std::length_error(msg);
        }

        m_value = sigmoid(weigthed_sum(prev_layer));
        return m_value;
    }

    void update_delta(T target) {
        if (is_bias()) { return; }
        m_delta = (target - m_value) * m_value * (1 - m_value);
    }

    void update_delta(Layer& next_layer, int neuron_index) {

        if (is_bias()) { return; }

        m_delta = 0;
        for (auto& neuron : next_layer) {
            if (!neuron.is_bias()) {
                m_delta += neuron.weights()[neuron_index] * neuron.delta();
            }
        }

        m_delta *= m_value * (1 - m_value);
    }

    void update_weights(Layer& prev_layer, T learn_rate) {
        if (!is_bias()) {
            for (int i = 0; i < m_weights.size(); i++) {
                T shift = learn_rate * m_delta * prev_layer[i].value();
                m_weights[i] += shift;
            }
        }
    }

    void reset(T value) { m_value = value; }

    T value() const { return m_value; }

    T delta() const { return m_delta; }

    bool is_bias() const { return m_weights.size() == 0; }

    const std::vector<T> weights() const { return m_weights; }

private:
    T weigthed_sum(Layer& input_layer) {
        T sum = 0;
        for (int i = 0; i < m_weights.size(); i++) {
            sum += input_layer[i].value() * m_weights[i];
        }
        return sum;
    }

    double sigmoid(T val) {
        T exp = std::exp(val);
        return exp / (exp + 1);
    }

private:
    std::vector<T> m_weights;
    T m_value = 1;
    T m_delta = 0;
};

#endif // NEURON_H