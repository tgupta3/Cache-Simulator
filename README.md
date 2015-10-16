This is a cache simulator project for ECE 521 (Computer Design and Techonology) by Tushar Gupta

To Execute
  1. Clone
  2. Make
  3. ./sim_cache BLOCKSIZE <L1_SIZE> <L1_ASSOC> <NUMBER OF VICTIM BLOCKS> <L2 SIZE> <L2 ASSOC> trace_file

Block size, l1_SIZE, L2_SIZE are in bytes

Trace file is a list of address along with whether they are read request or write request. A sample trace file has already been included

The output of individual set is displayed in from most recently used to least recently used. BLOCKS which have valid bit =0 are NOT displayed

Works well with two level of caches. Haven't tested it with more than two levels, will require some modification in 'main' to accomodate extra arguments and in the section which links these arguments to cache parameters. Victim Cache working great, have only tested it with L1 cache ! 

A python script was used to test different scenario to observe the effect of miss rate,AAT,presence and size of victim cache vs size of L1 cache or associativity.The script automatically writes the required dat into excel sheet which can tbe then plotted to observe the effect.

Debugging can be performed by comparing outputs with files in GCC_debug folder

To generate data for graphs, you need to have xlrd, xlrswriter python package. You can install them using pip or easy_install. 
