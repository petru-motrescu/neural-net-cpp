// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <fstream>
#include <vector>
#include "network.h"
#include "utils.h"

using namespace std;
using namespace utils;

#define pass() cout << __FUNCTION__ << ": ok" << endl;
#define fail() cout << __FUNCTION__ << ": FAILED!" << endl;
#define fail_equal(exp, act) cout << __FUNCTION__ << ": FAILED! Expected: " << exp << " Actual: " << act << endl;
#define assert(condition) if (condition) {pass();} else {fail();}
#define assert_equal(exp, act) if (are_equal(exp, act)) {pass();} else {fail_equal(exp, act);}

bool are_equal(double expected, double actual)
{
    const double threshold = 0.0001;
    auto diff = actual - expected;
    return (diff > -threshold && diff < threshold);
}

void test_neuron_compute_1()
{
    Neuron<double> neuron{0.15, 0.2, 0.35};
    assert_equal(0.59327, neuron.compute({0.05, 0.1, 1.0}));
}

void test_neuron_compute_2()
{
    Neuron<double> neuron{0.3, 0.5, 0.9};
    assert_equal(0.774692, neuron.compute({0.73, 0.79, 0.69}));
}

int main()
{
    test_neuron_compute_1();
    test_neuron_compute_2();
}
