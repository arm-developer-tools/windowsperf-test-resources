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

double df_sum = 789.123;
double df_hot(double input, int cond)
{
    double factor1 = 13.45;
    double factor2 = 13.45;
    df_sum /= factor1;
    df_sum += factor2 * factor2;
    df_sum *= (factor1 * 3.45 +  factor2 / 6.78);
    if (cond)
        return df_sum;
    for (int i = 0; i < 32; i++)
    {
        df_sum /= factor1;
        df_sum += factor2 * factor2;
        df_sum *= (factor1 * 3.45 +  factor2 / 6.78);
    }
    return df_sum;
}
#define SIMD_LOOP_LIMIT 10000
void simd_hot(unsigned int * __restrict a, unsigned int * __restrict b, unsigned int * __restrict c)
{
    for (int i = 0; i < SIMD_LOOP_LIMIT; i++)
        a[i] = b[i] + c[i];
}