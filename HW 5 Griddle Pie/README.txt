--- Run Time Version ---

Output values for:
10    - 2.96
100   - 3.116
1000  - 3.13916
10000 - 3.14136

Big O complexity:
O(n)
because the algorithm calculates the cut off points for each row and therefore only has to calculate n points.

Timing: (-o3)   (unoptimized)
100   - 0.004s  0.003s
1000  - 0.003s  0.004s
10000 - 0.003s  0.005s

The unoptimized timing seemed to match my expectations as they incresed by 0.001s with each increase of points. This isn't exactly linear but I assume that's due to fluctuations in the system and rounding of the time since even with 10,000 points this should be a very quick problem. I'm guessing that, when optimized, the assembler realises that you can basically just pre-calculate a lot of the values which is why the timing is fairly consistent.