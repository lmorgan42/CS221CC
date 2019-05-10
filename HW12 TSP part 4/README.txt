--- Making ---
use "make" command

--- Design ---
The multi-threading is implemented pretty simply, all that is done is the original code that creates and runs through a deme is now assigned to an arbitrary number of threads and the code is slightly modified to be thread safe. I had to change the way the program prints to the console as well since the original version was not thread safe in my version.

--- Run Statistics ---
iterations (set in code): 100,000
population: 1,000
mutation rate: 0.3

best tour (found with 2 threads): 9159.03
-Time-
one thread: 20.291s
two threads: 11.418s