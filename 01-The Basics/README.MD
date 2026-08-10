# Mini ADC Buffer Processor

A Chapter 1 practice project from *A Tour of C++ (3rd ed.)* - built around a
story every embedded engineer knows: processing a buffer of raw ADC samples.

## The story: where an ADC buffer comes from

A sensor (say, a temperature sensor) converts a physical quantity into a
voltage. The ADC - a peripheral that knows nothing about temperature, only
volts - samples that voltage and *quantizes* it into integer **counts**. A
12-bit ADC with a 3.3 V reference slices 0-3.3 V into 4096 steps of ~0.8 mV:

```
  25 °C  →  sensor  →  0.75 V  →  ADC  →  count 931
  ```

  Each conversion lands in the next slot of an array (often via DMA, no CPU
  involved) until a block of samples sits contiguously in memory. That array
  is the **ADC buffer**. Real firmware then processes it — averaging to kill
  noise, finding peaks, clamping glitches — and only at the very end converts
  counts back to meaningful units.

  ```
  analog → sample → quantize → buffer → process (ints!) → scale → use
  ```

  Two consequences shape this project:

  1. **The buffer holds counts (integers 0–4095), never volts.** The ADC
     cannot hand you 0.75 — it hands you 931.
     2. **Processing happens on integers**; floating point is used once, at the
        end, if at all. (Many small MCUs — like the Cortex-M0+ — have no FPU at
           all, so every `double` is emulated in software.)

           ## Files

           | File | What it is |
           |---|---|
           | `ADC.cpp` | **Starter** — a working `adc_read()` that simulates one 12-bit ADC read (random counts in [0, 4095]). Your job is everything else. |
           | `ADC_solution.cpp` | **One reference solution** — an interactive menu program built on the starter. Try it yourself first; compare after. |

           ## Your task

           1. Fill a 16-count buffer by calling `adc_read()`.
           2. Print the buffer.
           3. `minimum` / `maximum` — scan the buffer, keep the running champion.
           4. `average` — watch out for integer division (the truncation is a lesson,
              not a bug — see the solution for both views).
              5. `clamp` — saturate every sample above a ceiling, **in place**.
              6. `reverse` — reverse the buffer in place with two pointers walking
                 toward each other.

                 ## Features (solution)

                 - Interactive menu: `pri` print · `min` minimum · `max` maximum ·
                   `ave` average · `cla` clamp · `rev` reverse · `exit`
                   - Stats computed with hand-written scan loops (using `std::min`/`std::max`
                     only for the two-value comparison)
                     - `average` returns `double` via `static_cast` — the cast must reach the
                       division itself, not the result
                       - `clamp` and `reverse` mutate the caller's array through a pointer —
                         no copies, no returned arrays, exactly how C APIs (and DMA) work

                         ## Build & Run

                         ```bash
                         g++ ADC.cpp -o adc                    # starter (prints one sample)
                         g++ ADC_solution.cpp -o adc_solution  # reference solution
                         ./adc_solution
                         ```

                         Sample session:

                         ```
                         Select:
                         pri -> Print Samples
                         min -> Minimum Sample
                         ...
                         ave
                         2432.7
                         ```

                         ## Concepts practiced

                         | Book section | Where it shows up |
                         |---|---|
                         | §1.3 Functions | one responsibility per function; return values vs. in-place output |
                         | §1.4 Types, Arithmetic | integer division, `static_cast<double>` |
                         | §1.5 Scope and Lifetime | `static` locals in `adc_read()` — built once, reused |
                         | §1.6 Constants | `constexpr` for `adc_max_counts` and `buffer_size` (no magic numbers) |
                         | §1.7 Pointers, Arrays, References | array→pointer decay, pointer arithmetic, range-for by reference, dereferencing |
                         | §1.8 Tests | `if` chains, counting loops, `while` menu loop |
                         | §1.9 Mapping to Hardware | arrays are contiguous — the reason in-place processing and DMA work |

                         ## Stretch goals

                         1. **Counts → volts:** add `counts_to_volts(int)` and print stats in volts.
                            Scale *once*, at the end — like real firmware.
                            2. **See the memory (§1.9):** print `&buffer[x]` for every element and
                               confirm the addresses are contiguous, `sizeof(int)` bytes apart.
                               3. **Simulate the ADC itself:** write `quantize(double volts)` mapping
                                  [0, 3.3] → [0, 4095]; feed it random voltages, then compare original
                                     vs. reconstructed values to *see* quantization error (~0.8 mV steps).
                                     4. **(begin, end) variants:** rewrite the processing functions to take a
                                        pointer to the first element and one past the last — the style the
                                           standard library itself uses.
