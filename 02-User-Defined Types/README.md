# GPIO Register Simulator

A practice project for **Chapter 2 — "User-Defined Types"** of
*A Tour of C++ (3rd edition)* by Bjarne Stroustrup.

## What is a GPIO register?

Before the C++, a bit of embedded engineering — because this program
imitates something real.

On a microcontroller, a **GPIO pin is not an object — it is one bit in a
32-bit register** sitting at a fixed memory address. When firmware calls
something like `HAL_GPIO_WritePin()`, there is no magic under the hood:
the HAL computes a mask, shifts it into position, and performs one read or
write to a register. Change bit 5 of the **ODR** (Output Data Register) and
pin 5 of the port physically changes voltage. That's the whole trick.

This is called **memory-mapped I/O**: peripherals are just memory
locations, and a *driver* is nothing more than disciplined bit
manipulation that keeps the register in a valid state. Everything else —
UART, timers, SPI — is this same pattern repeated with more bits.

Two real-world rules shape this project:

- **The register is private state.** Nothing outside the driver may touch
  it directly, or the hardware ends up in an impossible configuration.
- **Every operation is one bit manipulation:** `|=` to set, `&= ~` to
  clear, `^=` to toggle, `&` to read — never a whole-register write from
  the outside.

## The exercise

The starter file provides a `main()` demo loop and empty method skeletons.
Everything the "driver" would do with the register is up to you.

Using only Chapter 2 — `struct`, `class` (encapsulation, constructors,
invariants), `enum class`, and `union` — build a class that simulates a
GPIO port's output register.

## What you need to do

1. An `enum class PinState` with values `low` and `high` — no naked ints
   for states.
2. A `struct PinConfig` describing one pin's configuration (number, mode,
   pull-up/pull-down — whatever you think a pin needs).
3. A `class GpioPort` holding **one private `uint32_t` register** that the
   outside world cannot touch.
4. Public operations, each a single bit manipulation with a shifted mask:
   `set(pin)`, `clear(pin)`, `toggle(pin)`, `read(pin)`.
5. A `print_binary()` that displays the register as
   `00000000 00100000 ...` so you can watch individual bits flip.
6. The union party trick: a `union` that views the same 32-bit register as
   one `uint32_t` *and* as four `uint8_t` bytes. Print both views, and
   watch the bytes come out "backwards" — congratulations, you've just seen
   **little-endian** with your own eyes.

   A reference solution (`gpio_solution.cpp`) is included. Try it yourself
   first — there is more than one correct way.

   ## Stretch goals

   - **BSRR semantics:** real STM32 ports have a Bit Set/Reset Register —
     write 1 to the lower half to *set* a pin, write 1 to the upper half to
     *reset* it. Why does this make writes atomic (interrupt-safe), unlike
     a read-modify-write?
   - Add a **second register** for pin modes (input/output), also private.

   ## Files

   - `gpio.cpp` — starter: class skeleton with empty methods and a demo
     `main()`.
   - `gpio_solution.cpp` — one complete solution, with binary register
     printing and the union byte view.

   ## Build & Run

   ```bash
   g++ -std=c++20 -Wall -Wextra gpio.cpp -o gpio
   ./gpio
