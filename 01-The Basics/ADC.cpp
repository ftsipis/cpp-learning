#include <iostream>
#include <random>

using namespace std;

// Simulates one read from a 12-bit ADC: retuns raw counts in [0, 4095].
constexpr int adc_max_counts = 4095;    // 2^12 - 1

int adc_read()
{
    static mt19937 rng(random_device{});
    static uniform_int_distribution<int> dist(0,adc_max_counts);
    return dist(rng);
}

int main()
{
    cout << adc_read() <<"\n";
    return 0;
}