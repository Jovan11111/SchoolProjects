# Hamming Code Implementation

This program implements a Hamming code in C++. The Hamming code is a linear error-correcting code used for error detection and correction in digital communication. It operates by adding check bits to the data bits to form a codeword. 
Code was written for faculty course Principals of Modern Telecomunications

## Requirements

- C++ compiler

## Description

- The program generates a random input array of zeros and ones.
- It then generates a Hamming array by adding check bits to the input array.
- Errors are introduced into the Hamming array based on a specified probability.
- The program corrects errors in the Hamming array and generates the output array.
- It calculates the number of differing bits between the input and output arrays.
- It also determines the number of code words that differ between the input and output code.
