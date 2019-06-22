// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>

#include "neuron.h"

class Network {

public:
    Network() {
        m_learn_rate = 0.01;
    }

    void add_layers(std::vector<int> neuron_counts) {
        for (int i = 0; i < neuron_counts.size(); i++) {
            bool add_bias = (i < (neuron_counts.size() - 1));
            add_layer(neuron_counts[i], add_bias);
        }
    }

    void add_layer(int neuron_count, bool add_bias_neuron = true) {

        int last_layer_size = (m_layers.size() > 0) ?
            m_layers[m_layers.size() - 1].size() : 0;

        Neuron::Layer layer;
        for (int i = 0; i < neuron_count; i++, m_total_neuron_count++) {
            if (last_layer_size > 0) {
                srand(m_total_neuron_count);
                layer.push_back(Neuron(last_layer_size));
            } else {
                layer.push_back(Neuron());
            }
        };

        if (add_bias_neuron) {
            layer.push_back(Neuron());
            m_total_neuron_count++;
        }

        m_layers.push_back(layer);
    }

    void set_learn_rate(Neuron::ValueType rate) {
        m_learn_rate = rate;
    }

    Neuron::ValueType learn_rate() const { return m_learn_rate; }

    int total_neuron_count() const { return m_total_neuron_count; }

    Neuron::Values compute(Neuron::Values input_values) {

        // Copy the values into the input layer.
        Neuron::Layer& input_layer = m_layers[0];
        for (int i = 0; i < input_values.size(); i++) {
            input_layer[i].reset(input_values[i]);
        }

        // Compute the values in all layers.
        for (int li = 1; li < m_layers.size(); li++) {
            for (int ni = 0; ni < m_layers[li].size(); ni++) {
                m_layers[li][ni].compute(m_layers[li - 1]);
            }
        }

        // Copy the values from the output layer.
        Neuron::Values output_values;
        Neuron::Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int ni = 0; ni < output_layer.size(); ni++) {
            if (!output_layer[ni].is_bias()) {
                output_values.push_back(output_layer[ni].value());
            }
        }

        return output_values;
    }

    void learn(Neuron::Values input_values, Neuron::Values target_values) {

        compute(input_values);

        // Compute the deltas in the output layer.
        Neuron::Layer& output_layer = m_layers[m_layers.size() - 1];
        for (int ni = 0; ni < target_values.size(); ni++) {
            output_layer[ni].update_delta(target_values[ni]);
        }

        // Compute the deltas in hidden layers, backwards.
        for (int li = m_layers.size() - 2; li >= 1; li--) {
            Neuron::Layer& curr_layer = m_layers[li];
            Neuron::Layer& next_layer = m_layers[li + 1];
            for (int ni = 0; ni < curr_layer.size(); ni++) {
                curr_layer[ni].update_delta(next_layer, ni);
            }
        }

        // Adjust the weights in all layers.
        for (int li = 1; li < m_layers.size(); li++) {
            Neuron::Layer& curr_layer = m_layers[li];
            Neuron::Layer& prev_layer = m_layers[li - 1];
            for (int ni = 0; ni < curr_layer.size(); ni++) {
                curr_layer[ni].update_weights(prev_layer, m_learn_rate);
            }
        }
    }

private:
    std::vector<Neuron::Layer> m_layers;
    Neuron::ValueType m_learn_rate;
    int m_total_neuron_count;
};

#endif // NETWORK_H