# Mini ADC Buffer Processor

A practice project for **Chapter 1 — "The Basics"** of
*A Tour of C++ (3rd edition)* by Bjarne Stroustrup.

## What is an ADC buffer processor?

Before the C++, a bit of embedded engineering — because this program
imitates something real.

Sensors measure the physical world and output a **voltage**. A temperature
sensor, for example, might output 0.75 V at 25 °C. But a microcontroller
can't store volts — it needs numbers. That's the job of the **ADC**
(Analog-to-Digital Converter): it samples the voltage and converts it into
an integer called a **count**. A 12-bit ADC with a 3.3 V reference slices
the range into 4096 steps (~0.8 mV each), so:

```
25 °C → sensor → 0.75 V → ADC → count 931
```

In real firmware, conversions arrive one after another and are stored in an
array — the **ADC buffer** — often by DMA, without the CPU doing anything.
Once a block of samples is collected, the firmware processes it: averaging
to reduce noise, finding minimum and maximum values, clamping out-of-range
readings (saturation), or reordering data. Only at the very end are counts
converted back into volts or degrees for a human to read.

Two real-world rules shape this project:

- **The buffer holds counts (integers 0–4095), never volts.**
- **Processing happens on integers**; floating point appears once, at the
  end, if at all — many small microcontrollers have no floating-point
    hardware at all.

    ## The exercise

    The starter file simulates the hardware part: `adc_read()` returns one
    random count in [0, 4095], like a 12-bit ADC would. Everything the firmware
    would do with those samples is up to you.

    Using only Chapter 1 — functions, basic types, `constexpr`, pointers,
    arrays, references, loops and `if`s (no STL containers) — build an
    interactive program that fills a 16-sample buffer and lets the user
    process it through a menu.

    ## What you need to do

    1. Declare a buffer of 16 `int`s and fill it by calling `adc_read()`.
    2. Print the buffer.
    3. `minimum` — the smallest sample.
    4. `maximum` — the largest sample.
    5. `average` — the mean of the samples (careful: integer division).
    6. `clamp` — pull every sample above a chosen ceiling down to it, in place.
    7. `reverse` — reverse the buffer in place (hint: two pointers walking
       toward each other).

       A reference solution (`ADC_solution.cpp`) is included. Try it yourself
       first — there is more than one correct way.

       ## Files

       - `ADC.cpp` — starter: `adc_read()` and nothing else.
       - `ADC_solution.cpp` — one complete solution, with a command menu:
         `pri` print · `min` · `max` · `ave` · `cla` clamp · `rev` reverse · `exit`

         ## Build & Run

         ```bash
         g++ ADC.cpp -o adc
         g++ ADC_solution.cpp -o adc_solution
         ./adc_solution
         ```
         