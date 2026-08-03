#include <iostream>
#include <random>

using namespace std;

// Simulates one read from a 12-bit ADC: returns raw counts in [0, 4095].
constexpr int adc_max_counts = 4095;    // 2^12 - 1
constexpr int buffer_size = 16;

int adc_read()
{
    static random_device dev;
    static mt19937 rng(dev());
    static uniform_int_distribution<int> dist(0,adc_max_counts);
    return dist(rng);
}

int main()
{
    // TODO: fill a 16-count buffer by calling adc_read(), then process it.
    int buffer[buffer_size];
    int *p = buffer;

    for (auto& x : buffer)
    {
        buffer[x] = adc_read();
    }

    for (auto& x : buffer_size)
    {
        cout << *p << '\n';
        ++p;
    }

    return 0;
}