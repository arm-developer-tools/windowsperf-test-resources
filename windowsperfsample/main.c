// BSD 3-Clause License
//
// Copyright (c) 2023, Arm Limited
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include <stdio.h>
#include <stdlib.h>
#include "SampleHybridDLL.h"

double df_hot(double input, int cond);
void simd_hot(unsigned int * __restrict a, unsigned int * __restrict b, unsigned int * __restrict c);
#define SIZE 10000

static void init(int *a, int *b, int *c)
{
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }
}

int main(int argc, char **argv)
{
    unsigned int* a = malloc(sizeof(unsigned int) * SIZE);
    unsigned int* b = malloc(sizeof(unsigned int) * SIZE);
    unsigned int* c = malloc(sizeof(unsigned int) * SIZE);
    double df_sum = 789.123;

    init(a, b, c);

    // Initialize a Fibonacci relation sequence.
    fibonacci_init(1, 1);

    while (1)
    {
        for (int idx = 0; idx < 100; idx++)
            df_hot(df_sum, 1);
        for (int idx = 0; idx < 100; idx++)
            simd_hot(a, b, c);

        // Write out the sequence values until overflow.
        for (int idx = 0; idx < 100000; idx++)
            if (fibonacci_next() == false)
                fibonacci_init(1, 1);
    }

    free(a);
    free(b);
    free(c);
}