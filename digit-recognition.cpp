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
    using ValueType = double;
    using BitmapType = vector<ValueType>;
    using DigitType = vector<ValueType>;
    
    Network<ValueType> network;
    network.add_layers({100, 50, 25, 10});
    
    vector<string> train_set_paths = 
    {
        "data/digits-10x10/1/",
    };

    for (auto& path : train_set_paths)
    {
        vector<BitmapType> input_bitmaps;
        for (int i = 0; i < 10; i++)
        {
            string digit_file_path(path);
            digit_file_path += to_string(i);
            digit_file_path += ".txt";
            input_bitmaps.push_back(utils::read_digit_bitmap<ValueType>(digit_file_path));
        }

        vector<DigitType> output_digits;
        for (int digit = 0; digit < 10; digit++)
        {
            output_digits.push_back(utils::make_digit_vector<ValueType>(digit));
            log_nl(output_digits[digit]);
        } 

        for (int digit = 0; digit < 10; digit++)
        {
            auto result = network.compute(input_bitmaps[digit]);
            cout << digit << " --> ";
            log_nl(result);
        }

        for (int round = 0; round < 1000; round++)
        {
            for (int digit = 0; digit < 10; digit++)
            {
                network.learn(input_bitmaps[digit], output_digits[digit]);
            }
        }

        for (int digit = 0; digit < 10; digit++)
        {
            auto result = network.compute(input_bitmaps[digit]);
            cout << digit << " --> ";
            log_nl(result);
        }
    }
}
