# Introduction

This project contains simple ARM64/ARM64EC project that can be used to test counting and sampling for WindowsPerf.

- `WindowsPerfSample` project: executable implementing `main()` and SIMD operations.
- `SampleHybridDLL` project: DLL with simple Fib code (based on [Walkthrough: Create and use your own Dynamic Link Library (C++)](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170) example).

# Usage

Build project with `Debug|ARM64` configuration. `SampleHybridDLL` project will be built as `Debug|ARM64EC` dependency:

```
>link -dump -headers SampleHybridDLL.dll
Dump of file SampleHybridDLL.dll

PE signature found

File Type: DLL

FILE HEADER VALUES
            AA64 machine (ARM64) (ARM64X)
               9 number of sections
        66683DBD time date stamp Tue Jun 11 13:06:21 2024
               0 file pointer to symbol table
               0 number of symbols
              F0 size of optional header
            2022 characteristics
                   Executable
                   Application can handle large (>2GB) addresses
                   DLL

```

## Sampling example output

```
>wperf record -e dp_spec -c 7 --timeout 3 -- WindowsPerfSample.exe
base address of 'WindowsPerfSample.exe': 0x7ff715334e58, runtime delta: 0x7ff5d5327e58
sampling ...... done!
======================== sample source: dp_spec, top 50 hot functions ========================
        overhead  count  symbol
        ========  =====  ======
           76.02    130  simd_hot:WindowsPerfSample.exe
           14.04     24  __CheckForDebuggerJustMyCode:SampleHybridDLL.dll
            5.85     10  std::swap<unsigned __int64,0>:SampleHybridDLL.dll
            3.51      6  fibonacci_next:SampleHybridDLL.dll
            0.58      1  main:WindowsPerfSample.exe
100.00%       171  top 5 in total
```

## Counting example output

```
>wperf stat -m Operation_Mix -c 7 --timeout 5 -- WindowsPerfSample.exe
counting ... done

Performance counter stats for core 7, multiplexed, kernel mode excluded, on Arm Limited core implementation:
note: 'e' - normal event, 'gN' - grouped event with group number N, metric name will be appended if 'e' or 'g' comes from it

         counter value  event name        event idx  event note                multiplexed    scaled value
         =============  ==========        =========  ==========                ===========    ============
        16,516,731,169  cycle             fixed      e                               55/55  16,516,731,169
        17,344,203,321  inst_spec         0x1b       g0,load_percentage              19/55  50,206,904,350
         4,628,222,709  ld_spec           0x70       g0,load_percentage              19/55  13,397,486,789
        17,344,203,321  inst_spec         0x1b       g1,store_percentage             19/55  50,206,904,350
         3,415,929,189  st_spec           0x71       g1,store_percentage             19/55   9,888,216,073
         6,747,098,140  dp_spec           0x73       g2,integer_dp_percentage        19/55  19,531,073,563
        17,344,203,321  inst_spec         0x1b       g2,integer_dp_percentage        19/55  50,206,904,350
           299,673,566  ase_spec          0x74       g3,simd_percentage              18/55     915,669,229
        16,488,901,462  inst_spec         0x1b       g3,simd_percentage              18/55  50,382,754,467
        16,488,901,462  inst_spec         0x1b       g4,scalar_fp_percentage         18/55  50,382,754,467
               497,683  vfp_spec          0x75       g4,scalar_fp_percentage         18/55       1,520,698
         1,474,327,796  br_immed_spec     0x78       g5,branch_percentage            18/55   4,504,890,487
           584,974,130  br_indirect_spec  0x7a       g5,branch_percentage            18/55   1,787,420,952
        16,062,470,387  inst_spec         0x1b       g5,branch_percentage            18/55  49,079,770,626
                     0  crypto_spec       0x77       g6,crypto_percentage            18/55               0
        16,062,470,387  inst_spec         0x1b       g6,crypto_percentage            18/55  49,079,770,626

Telemetry Solution Metrics:
        core  product_name  metric_name             value  unit
        ====  ============  ===========             =====  ====
           7  neoverse-n1   branch_percentage      12.821  percent of operations
           7  neoverse-n1   crypto_percentage       0.000  percent of operations
           7  neoverse-n1   integer_dp_percentage  38.901  percent of operations
           7  neoverse-n1   load_percentage        26.685  percent of operations
           7  neoverse-n1   scalar_fp_percentage    0.003  percent of operations
           7  neoverse-n1   simd_percentage         1.817  percent of operations
           7  neoverse-n1   store_percentage       19.695  percent of operations

               5.542 seconds time elapsed
```
