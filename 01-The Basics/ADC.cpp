#include <iostream>
#include <random>

using namespace std;

void adc()           // generate a random int from 0 to 4095
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(0,4095); // distribution in range [1, 6]

    return dist(rng) << endl;
}

int main()
{
    cout << adc();
    return 0;
}