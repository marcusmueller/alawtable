/*
 * SPDX-License-Identifier: EUPL-1.2
 *
 * Copyright 2025 Marcus Müller
 */

#include <format>
#include <fstream>
#include <iostream>

extern "C" {
unsigned char linear2alaw(int pcm_val);
int alaw2linear(unsigned char a_val);
}

int main()
{
    std::ofstream linear_to_alaw("linear_to_alaw.csv");
    linear_to_alaw << std::format("{:>4}, {:>3}\n", "linear", "alaw");
    std::ofstream lin_to_lin("linear_to_linear.csv");
    lin_to_lin << std::format(
        "{:>4}, {:>4}, {:>2}\n", "linear", "reconstructed", "error");

    std::cout << "#!/usr/bin/python3\nlin_to_lin = [";
    for (signed int linear = -4096; linear < 4096; ++linear) {
        linear_to_alaw << std::format("{:>4d}, {:>3d}\n", linear, linear2alaw(linear));

        int reconstructed = alaw2linear(linear2alaw(linear));
        int error = reconstructed - linear;
        lin_to_lin << std::format(
            "{:>4d}, {:>4d}, {:>2d}\n", linear, reconstructed, error);

        if (linear < 4095) {
            std::cout << std::format("{:>4d}, ", reconstructed);
        } else {
            std::cout << std::format("{:>4d}]\n", reconstructed);
        }
    }
    linear_to_alaw.close();
    lin_to_lin.close();
}
