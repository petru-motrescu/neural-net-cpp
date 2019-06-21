// Petru Motrescu <petru.motrescu@gmail.com>, 2018

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <neural-net/network.h>
#include <samples/utils.h>

using namespace std;
using namespace utils;

using Pixel = long double;
using Bitmap = vector<Pixel>;
using BitmapSet = vector<Bitmap>;
using Digit = vector<Pixel>;
using DigitSet = vector<Digit>;

void log_train_results(Network<Pixel>& network, vector<BitmapSet>& sets) {
    for (int set = 0; set < sets.size(); set++) {
        for (int digit = 0; digit < 10; digit++) {
            auto result = network.compute(sets[set][digit]);
            cout << digit << " ---> ";
            cout << utils::max(result) << "  ";
            utils::log_details_nl(result);
        }
        cout << endl;
    }
}

int main() {

    utils::set_console_decimals(4);
    utils::log_colored_nl("Hi! Give me a few minutes to train!");

    vector<string> train_set_paths = {
        "train-sets/1/",
        "train-sets/2/",
        "train-sets/3/",
        "train-sets/4/",
        "train-sets/5/",
    };

    vector<BitmapSet> train_sets;
    for (auto& path : train_set_paths) {
        BitmapSet set;
        for (int i = 0; i < 10; i++) {
            string digit_file_path(path);
            digit_file_path += to_string(i);
            digit_file_path += ".txt";
            set.push_back(utils::read_digit_bitmap<Pixel>(digit_file_path));
        }
        train_sets.push_back(set);
    }

    DigitSet digits;
    for (int digit = 0; digit < 10; digit++) {
        digits.push_back(utils::make_digit_vector<Pixel>(digit));
    }

    Network<Pixel> network;
    network.add_layers({100, 55, 10});
    network.set_learn_rate(0.01);

    const int training_rounds = 5;
    for (int round = 1; round <= training_rounds; round++) {
        cout << "# Training round " << round << " out of " << training_rounds << endl;
        for (int rep = 0; rep < 1000; rep++) {
            for (int set = 0; set < train_sets.size(); set++) {
                for (int digit = 0; digit < 10; digit++) {
                    network.learn(train_sets[set][digit], digits[digit]);
                }
            }
        }
        log_train_results(network, train_sets);
    }

    cout << endl << endl;
    utils::log_colored_nl("Yay! I've completed my training!");

    while (true) {
        
        cout << "Input the path to a digit file (test-sets/1/0.txt): ";
        string path;
        cin >> path;
        cout << endl;

        if (path == "Q" || path == "q") {
            return 0;
        }

        auto bitmap = utils::read_digit_bitmap<Pixel>(path);
        log_digit_bitmap(bitmap, 10);

        auto result = network.compute(bitmap);
        log_colored_nl("I think that is a", utils::max(result));
        log_details_nl(result);
        cout << endl << endl;
    }
}
