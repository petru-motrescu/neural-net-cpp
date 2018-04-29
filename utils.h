// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>

namespace utils
{
    std::vector<double> read_digit_bitmap(std::string filename)
    {
        std::vector<double> pixels;
        std::ifstream file(filename);
        if (file.is_open())
        {
            char c;
            while (file >> c)
            {
                pixels.push_back(c == '.' ? 0.0 : 1.0);
            }
        }

        return pixels;
    }

    // Convert a digit (0 - 9) to a vector of 0s and a single 1:
    // 0 -> { 1,0,0,0,0,0,0,0,0,0 }
    // 1 -> { 0,1,0,0,0,0,0,0,0,0 }
    // 2 -> { 0,0,1,0,0,0,0,0,0,0 }
    std::vector<double> make_digit_vector(int digit)
    {
        std::vector<double> v = std::vector<double>(10, 0);
        v[digit] = 1.0;
        return v;
    }

    template<typename T>
    void log(const std::vector<T>& v)
    {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, ", "));
    }

    template<typename T>
    void log_nl(const std::vector<T>& v)
    {
        log(v);
        std::cout << std::endl;
    }

    template<typename T>
    void log_digit_bitmap(const std::vector<T>& v, int width)
    {
        for (int i = 0, j = 0; i < v.size(); i++, j++)
        {
            if (j == width)
            {
                std::cout << std::endl;
                j = 0;
            }

            if (v[i] == 0)
            {
                std::cout << ".";
            }
            else
            {
                std::cout << "X";
            }
        }
        
        std::cout << std::endl;
        std::cout << std::endl;
    }

    int max(std::vector<double>& v)
    {
        double max_pos = 0;

        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] > v[max_pos])
            {
                max_pos = i;
            }
        }

        return max_pos;
    }
}

#endif // UTILS_H