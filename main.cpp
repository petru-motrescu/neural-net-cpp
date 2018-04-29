// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

using namespace std;
using namespace utils;

int main()
{
    using Pixels = vector<double>;
    using Digit = vector<double>;
    using Neuron = Neuron<double>;
    using Layer = Network<double>::Layer;
    
    Layer input;
    Layer hidden;
    Layer output;

    for (int i = 0; i < 25; i++)
    {
        input.push_back(Neuron());
    };

    input.push_back(Neuron());
    
    for (int i = 0; i < 15; i++)
    {
        hidden.push_back(Neuron(input));
    };

    hidden.push_back(Neuron());

    for (int i = 0; i < 10; i++)
    {
        output.push_back(Neuron(hidden));
    };

    Network<double> net = { input, hidden, output };

    vector<Digit> outputs;
    for (int i = 0; i < 10; i++)
    {
        outputs.push_back(utils::make_digit_vector(i));
    }
    
    vector<string> train_set_paths = 
    {
        "train-data/train-1/",
    };

    for (auto& path : train_set_paths)
    {
        vector<Pixels> inputs;
        for (int i = 0; i < 10; i++)
        {
            string digit_file_path(path);
            digit_file_path += to_string(i);
            digit_file_path += ".txt";
            inputs.push_back(utils::read_digit_bitmap(digit_file_path));
        }

        for (int i = 0; i < 10000; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                net.learn(inputs[j], outputs[j]);
            }
        }

        for (int i = 0; i < 10; i++)
        {
            auto result = net.compute(inputs[i]);
            cout << i << " --> " << utils::max(result) << " : ";
            utils::log_nl(result);
        }
    }
}
