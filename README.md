# GlobalOptimus - RSA & Drop-Wave Optimization

## Overview
This repository contains a custom optimization method and problem implemented for the open-source [GlobalOptimus](https://github.com/itsoulos/GlobalOptimus) framework. 
It implements the **Reptile Search Algorithm (RSA)** to solve the **Drop-Wave** benchmark function

## Files Included
- `usermethod.h` & `usermethod.cpp`: Implementation of RSA with dynamic parameters (alpha, beta)
- `userproblem.h` & `userproblem.cpp`: Implementation of the Drop-Wave objective function and its mathematical gradient

## Prerequisites
- [GlobalOptimus](https://github.com/itsoulos/GlobalOptimus) framework installed
- Qt Creator to recompile the project

## How to Run
1. Clone the original GlobalOptimus repository
2. Replace the default `usermethod` and `userproblem` files (both `.cpp` and `.h`) in the source tree with the files provided in this repository
3. Recompile the GlobalOptimus application
4. Launch the app and select **UserProblem** as the main problem and **UserMethod** as the optimizer

## Acknowledgments
- Built on top of the GlobalOptimus framework by [itsoulos](https://github.com/itsoulos)
- Developed as part of a university assignment