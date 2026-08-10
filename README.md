# C++ Learning

My journey through *A Tour of C++ (3rd edition)* by Bjarne Stroustrup —
one mini project per chapter, aimed at embedded systems and SoC.

Each project is built around a real embedded scenario, so the repo teaches
both the language and the engineering context behind it.

## Projects

| Chapter | Project | Concepts |
|---|---|---|
| 1 — The Basics | [Mini ADC Buffer Processor](01-The%20Basics) | functions, arrays, pointers, references, `constexpr` |

## Repository structure

Every chapter folder contains:

- `README.md` — the story behind the project, the task, and the theory
- a starter file — working skeleton to build on
- a solution file — one complete reference implementation

## Compile

Written and tested on Android (Termux):

```bash
g++ -std=c++20 -Wall -Wextra file.cpp -o file
./file
```
