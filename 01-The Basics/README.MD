# Mini ADC Buffer Processor

A Chapter 1 practice project from *A Tour of C++ (3rd ed.)*.

## Description
Simulates processing a 16-sample ADC buffer using only C++ basics:
functions, arrays, pointers, references, and constexpr — no STL.

## Features
- min / max / average of samples
- clamp (saturation)
- in-place reverse using pointer arithmetic
- prints memory addresses to observe array layout

## Build & Run
```bash
g++ adc.cpp -o adc
./adc
```

## Concepts practiced
Functions · scope · constants · pointers · arrays · references · tests
