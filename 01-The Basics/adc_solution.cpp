#include <iostream>
#include <random>
#include <algorithm>
#include <string>

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
        cout << buffer[x] << "\n";
    }
    cout << '\n';
}

int minimum (int buffer[])
{
    int smallest = buffer[0];
    for (int x=1; x<buffer_size; x++)
    {
        smallest = min(smallest,buffer[x]);
    }
    return smallest;
}

int maximum (int buffer[])
{
    int biggest = buffer[0];
    for (int x=1; x<buffer_size; x++)
    {
        biggest = max(biggest, buffer[x]);
    }
    return biggest;
}

double average (int buffer[])
{
    int sum = buffer[0];
    for (int x=1; x<buffer_size; x++)
    {
        sum = sum + buffer[x];
    }
    return static_cast<double>(sum) / buffer_size;
}

void clamp (int buffer[])
{
    int value;
    cout << "Give the value for saturation: ";
    cin >> value;
    for (int x=0; x<buffer_size; x++)
    {
        if (buffer[x] > value) buffer[x] = value;
    }
    cout << "\nThe buffer is saturated.\n\n";
}

void reverse (int buffer[])
{
    int* n = buffer;
    int* p = buffer + buffer_size - 1;
    int temp;
    //while (n < p)
    
        temp = *n;
        n = p;
        *p = temp;
    
}

int main()
{
    int buffer[buffer_size];
    string input;

    for (auto& x : buffer)
    {
        x = adc_read();
    }

    while (true)
    {
        cout << "Select: \n"
             << "pri -> Print Samples\n"
             << "min -> Minimum Sample\n"
             << "max -> Maximum Sample\n"
             << "ave -> Average of Samples\n"
             << "cla -> Clamp\n"
             << "rev -> Reverse the Samples\n"
             << "exit -> Exit the Program\n\n";
        
        cin >> input;
        cout << "\n";

        if (input == "pri") print_buffer(buffer);
        else if (input == "min") cout << minimum(buffer) << "\n\n";
        else if (input == "max") cout << maximum(buffer) << "\n\n";
        else if (input == "ave") cout << average(buffer) << "\n";
        else if (input == "cla") clamp(buffer);
        else if (input == "rev") reverse(buffer);
        else if (input == "exit") break;
        else cout << "Unknown Choice. Choose again!\n";
    }  

    return 0;
}