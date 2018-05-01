// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

using namespace std;
using namespace utils;

using Pixel = long double;
using Bitmap = vector<Pixel>;
using BitmapSet = vector<Bitmap>;
using Digit = vector<Pixel>;
using DigitSet = vector<Digit>;

void log_result(Digit& v, int expected)
{
    cout << expected << " ---> " << utils::max(v) << " : ";

    for (int i = 0; i < v.size(); i++)
    {
        cout << "[" << i << " = " << fixed << setprecision(4) << v[i] << "] ";
    }

    cout << endl;
}

void log_results(Network<Pixel>& network, vector<BitmapSet>& sets)
{
    for (int set = 0; set < sets.size(); set++)
    {
        for (int digit = 0; digit < 10; digit++)
        {
            auto result = network.compute(sets[set][digit]);
            log_result(result, digit);
        }

        cout << endl;
    }
}

int main()
{
    vector<string> train_set_paths = 
    {
        "data/digits-10x10/1/",
        "data/digits-10x10/2/",
        "data/digits-10x10/3/",
        "data/digits-10x10/4/",
        "data/digits-10x10/5/",
    };

    vector<BitmapSet> train_sets;
    for (auto& path : train_set_paths)
    {
        BitmapSet set;
        for (int i = 0; i < 10; i++)
        {
            string digit_file_path(path);
            digit_file_path += to_string(i);
            digit_file_path += ".txt";
            set.push_back(utils::read_digit_bitmap<Pixel>(digit_file_path));
        }

        train_sets.push_back(set);
    }

    DigitSet digits;
    for (int digit = 0; digit < 10; digit++)
    {
        digits.push_back(utils::make_digit_vector<Pixel>(digit));
    }

    Network<Pixel> network;
    network.add_layers({100, 16, 10});
    network.set_learn_rate(0.025);

    for (int round = 0; round < 10; round++)
    {
        cout << endl << "### Round " << round << endl;

        for (int rep = 0; rep < 1000; rep++)
        {
            for (int set = 0; set < train_sets.size(); set++)
            {
                for (int digit = 0; digit < 10; digit++)
                {
                    network.learn(train_sets[set][digit], digits[digit]);
                }
            }
        }

        log_results(network, train_sets);
    }
}
