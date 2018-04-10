// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

using namespace std;
using namespace utils;

#define assert_equal(a, b) { cout << __FUNCTION__; assert_equal_impl(a, b); }

bool are_equal(double expected, double actual)
{
    const double threshold = 0.0001;
    auto diff = actual - expected;
    return (diff > -threshold && diff < threshold);
}

bool are_equal(vector<double> expected, vector<double> actual)
{
    if (expected.size() != actual.size()) { return false; }
    for (int i = 0; i < expected.size(); i++)
    {
        if (!are_equal(expected[i], actual[i])) { return false; }
    }
    return true;
}

void assert_equal_impl(double expected, double actual)
{
    if (are_equal(expected, actual))
    {
        cout << " : ok" << endl;
    }
    else
    {
        cout << " : FAILED! Expected:" << expected << " Actual:" << actual << endl;
    }
}

void assert_equal_impl(vector<double> expected, vector<double> actual)
{
    if (are_equal(expected, actual))
    {
        cout << " : ok" << endl;
    }
    else
    {
        cout << " : FAILED! Expected:{";
        log(expected);
        cout << "} Actual:{";
        log(actual);
        cout << "}" << endl;
    }
}

void test_neuron_compute_ah1()
{
    Neuron<double> neuron{0.15, 0.20, 0.35};
    assert_equal(0.59327, neuron.compute({0.05, 0.1, 1.0}));
}

void test_neuron_compute_ah2()
{
    Neuron<double> neuron{0.25, 0.30, 0.35};
    assert_equal(0.596884, neuron.compute({0.05, 0.1, 1.0}));
}

void test_neuron_compute_ao1()
{
    Neuron<double> neuron{0.40, 0.45, 0.60};
    assert_equal(0.751365, neuron.compute({0.59327, 0.596884, 1.0}));
}

void test_neuron_compute_ao2()
{
    Neuron<double> neuron{0.50, 0.55, 0.60};
    assert_equal(0.772928, neuron.compute({0.59327, 0.596884, 1.0}));
}

void test_neuron_learn_ao1()
{
    Neuron<double> neuron{0.40, 0.45, 0.60};
    neuron.learn({0.59327, 0.596884, 1.0}, 0.01);
    auto expected = {0.358916, 0.408666, 0.530751};
    assert_equal(expected, neuron.weights());
}

void test_neuron_learn_ao2()
{
    Neuron<double> neuron{0.50, 0.55, 0.60};
    neuron.learn({0.59327, 0.596884, 1.0}, 0.99);
    auto expected = {0.511301,0.56137,0.619049};
    assert_equal(expected, neuron.weights());
}

void test_neuron_compute_bo()
{
    Neuron<double> neuron{0.3, 0.5, 0.9};
    assert_equal(0.774692, neuron.compute({0.73, 0.79, 0.69}));
}

int main()
{
    // A: https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
    test_neuron_compute_ah1();
    test_neuron_compute_ah2();
    test_neuron_compute_ao1();
    test_neuron_compute_ao2();
    test_neuron_learn_ao1();
    test_neuron_learn_ao2();

    // B: http://stevenmiller888.github.io/mind-how-to-build-a-neural-network/
    test_neuron_compute_bo();
}
