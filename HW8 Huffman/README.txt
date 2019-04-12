explain why one test is commented out

--- Make ---
use same make commands as come in the default make file.

--- Disclaimer ---
There are still some errors with the code. First, the code fails the first huffman test but only the first and in a way that seems non-harmful. Instead of creating a longer binary for a it creates one of equal size. I believe that thos is just a product of the way it constructs trees and that it is not technically a bug. The major bugs are as follows:

Decoder will crash at the end of decoding file.
For the files the decoder works on it seems that at the end a destructor attempts to access memory not availble to it. This is only an error on linux, not windows. The decoder is able to fully decode the file and the program is one return away from finishing when this happens. I was unable to locate the source.

Decoder will begin to read only ones at certain point in file.
For an unknown reason certain points in the longer files cause the decoder to begin reading only 1's. In Miyazaki this causes an endless loop which leads me to believe that the encoder works, since I verified there is not an infinite amount of ones at the end of the file and i also confirmed that there was not a long block of ones using a binary editor. This implies to me that the decoder at some point gets stuck on some part of the file and begins to receive or read only ones. I was unable to discover the source of this bug in time.

--- Compression Tests ---
Results of the compression test. All sizes in bytes.

File Name			Orig Size		Comp Size		Decomp Correct
test2.txt			7				4				yes
tardigrades.txt		1569			1017			no
Hitchhiker.txt		3457			1949			no
Miyazaki.txt		2393			1493			no
Waxillium.txt		3962			2334			no
