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

--- Compile Time Version ---

Compile Times:
o3 time      - 0.599s
time         - 0.558s
o3 constexpr - 0.475s
constexpr    - 0.470s

Timing: (o3)   (unoptimized)
100   - 0.003s  0.003s
1000  - 0.003s  0.003s
10000 - 0.003s  0.003s

The run times for the three programs have become constant because the expression has already been evaluated due to the nature of constexpr. More interestingly I had predicted that the compile times for the contexpr versions of the program would have increased inversly to the run time of the program because the expression needs to be evaluted at some point and that time would presumably be at compile for constexpr; however, as can be seen in the Compile Time table the compile times for the constexpr versions are actually significantly lower than those of the run time versions. I can only guess that this is due to the algorithm's behavior and that perhaps arrays can be made to perform better in compilation than in run time or that creating the assembly code necessary for arrays is time intensive.