// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <vector>
#include "network.h"

using namespace std;

int main()
{
    const int input_count = 4;
    const int hidden_count = 4;
    const int output_count = 1;

    Network net{input_count, hidden_count, output_count};
    
    auto input = std::vector<double>{1, 1, 1, 1};
    auto output = net.compute(input);

    for (auto value : output)
    {
        std::cout << value << ", ";
    }

    std::cout << std::endl;
}