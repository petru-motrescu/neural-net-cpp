// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>

namespace utils
{
    void read_digit_bitmap(std::vector<double>& pixels, std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            char c;
            while (file >> c)
            {
                pixels.push_back(c == '.' ? 0.0 : 1.0);
            }
        }
    }

    // Convert a digit (0 - 9) to a vector of 0s and a single 1:
    // 0 -> { 1,0,0,0,0,0,0,0,0,0 }
    // 1 -> { 0,1,0,0,0,0,0,0,0,0 }
    // 2 -> { 0,0,1,0,0,0,0,0,0,0 }
    void make_digit_vector(std::vector<double>& v, int digit)
    {
        v = std::vector<double>(10, 0);
        v[digit] = 1.0;
    }

    template<typename T>
    void log(const std::vector<T>& v)
    {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, ","));
    }

    template<typename T>
    void log_nl(const std::vector<T>& v)
    {
        log(v);
        std::cout << std::endl;
    }
}

#endif // UTILS_H