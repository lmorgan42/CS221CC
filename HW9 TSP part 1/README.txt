--- WARNING! ---
This program uses a linux-specific time function in cities.cpp on line 86 that retrieves milliseconds instead of seconds to seed the random function so that it can be called more than once per second. This will crash on windows and potentially on mac.

--- Making ---
use either "make" or "make random", both do the same thing. This will produce an executable called random which can then be run with the one file name argument.

--- Design ---
The design of this program is pretty strait forward. There is a test functions in tsp.cpp that can be called if necessary. The random permutation function is implemented with standard function random_shuffle which shuffles a container. It is seeded as quickly as possible using millisecond time as it will produce the same shuffle if the seed is not changed.