#include <iostream>
#include <random>

using namespace std;

int adc()           // generate a random int from 0 to 4095
{
    static random_device dev;
    static mt19937 rng(dev());
    static uniform_int_distribution<mt19937::result_type> dist(0,4095); // distribution in range [1, 6]

    return dist(rng);
}

int main()
{
    cout << adc() <<"\n";
    return 0;
}