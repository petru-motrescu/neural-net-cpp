// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>

namespace utils
{
    template<typename T>
    std::vector<T> read_digit_bitmap(std::string filename)
    {
        std::vector<T> pixels;
        std::ifstream file(filename);
        if (file.is_open())
        {
            char c;
            while (file >> c)
            {
                pixels.push_back(c == '.' ? 0.000001 : 0.999999);
            }
        }

        return pixels;
    }

    template<typename T>
    std::vector<T> make_digit_vector(int digit)
    {
        std::vector<T> v = std::vector<T>(10, 0);
        v[digit] = 1;
        return v;
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
                std::cout << "O";
            }
        }
        
        std::cout << std::endl;
        std::cout << std::endl;
    }

    template<typename T>
    int max(std::vector<T>& v)
    {
        int max_pos = 0;

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