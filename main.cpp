// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include "network.h"

using namespace std;

int main()
{
    const int input_count = 2;
    const int hidden_count = 3;
    const int output_count = 1;

    Network net{input_count, hidden_count, output_count};

    for (int i = 0; i < 10; i++)
    {
        net.learn({1, 1}, {0});
        net.learn({0, 0}, {0});
        net.learn({1, 0}, {1});
        net.learn({0, 1}, {1});
    }
    
    Output output = net.compute({1, 1});
}