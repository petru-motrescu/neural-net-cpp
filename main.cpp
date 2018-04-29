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
    using Pixels = vector<long double>;
    using Digit = vector<long double>;
    using Neuron = Neuron<long double>;
    using Layer = Network<long double>::Layer;
    
    Layer input;
    Layer hidden1;
    Layer hidden2;
    Layer output;

    for (int i = 0; i < 25; i++)
    {
        input.push_back(Neuron());
    };

    input.push_back(Neuron());

    for (int i = 0; i < 16; i++)
    {
        hidden1.push_back(Neuron(input));
    };

    hidden1.push_back(Neuron());

    for (int i = 0; i < 16; i++)
    {
        hidden2.push_back(Neuron(hidden1));
    };

    hidden2.push_back(Neuron());

    for (int i = 0; i < 10; i++)
    {
        output.push_back(Neuron(hidden2));
    };

    Network<long double> net = { input, hidden1, hidden2, output };
    net.set_learn_rate(0.25);

    vector<Digit> outputs;
    for (int i = 0; i < 10; i++)
    {
        outputs.push_back(utils::make_digit_vector<long double>(i));
    }
    
    vector<string> train_set_paths = 
    {
        "data/digits-5x5/1/",
    };

    for (auto& path : train_set_paths)
    {
        vector<Pixels> inputs;
        for (int i = 0; i < 10; i++)
        {
            string digit_file_path(path);
            digit_file_path += to_string(i);
            digit_file_path += ".txt";
            inputs.push_back(utils::read_digit_bitmap<long double>(digit_file_path));
        }

        for (int round = 1; round <= 50; round++)
        {
            cout << "### Round " << round << " ### " << endl;

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
                cout << i << " --> " << utils::max<long double>(result) << " : ";
                utils::log_nl(result);
            }

            cout << endl;
        }
    }
}
