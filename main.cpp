// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

int main()
{
    const int input_count = 36;
    const int hidden_count = 18;
    const int output_count = 10;

    Network net{input_count, hidden_count, output_count};
    
    for (int i = 0; i < 10; i++)
    {
        std::vector<double> pixels;
        std::vector<double> digit;
        std::string filename = "train-data/train-1/" + std::to_string(i) + ".txt";
        Utils::read_digit_bitmap(pixels, filename);
        Utils::make_digit_vector(digit, i);
        net.learn(pixels, digit);
    }
}
