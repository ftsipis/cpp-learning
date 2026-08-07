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

void print_buffer(int buffer[])
{
    for (int x=0; x<buffer_size; x++)
    {
        cout << buffer[x] << '\n';
    }
}

/*int minimum (int buffer[])
{
    return min(buffer);
}*/

int main()
{
    // TODO: fill a 16-count buffer by calling adc_read(), then process it.
    int buffer[buffer_size];
    string input;

    for (auto& x : buffer)
    {
        x = adc_read();
    }

    while (1)
    {
        cout << "Select: \n"
             << "pri -> Print Samples\n"
             << "min -> Minimum Sample\n"
             << "max -> Maximum Sample\n"
             << "ave -> Average of Samples\n"
             << "cla -> Clamp\n"
             << "rev -> Reverse the Samples\n\n";
        
        cin >> input;
        cout << "\n";

        if (input == "pri") print_buffer(buffer);
        else if (input == "min")
        else if (input == "max")
        else if (input == "ave")
        else if (input == "cla")
        else if (input == "rev")
        else cout << "Unwoun Choice.\n";
    }  

    return 0;
}