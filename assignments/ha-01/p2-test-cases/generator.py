# this script generates a binary file encoding 
# N consecutive pairs (IP addresses / subnet)
# usage: python3 generator <output_file_name> <N>

import sys 
from random import randint

fname = sys.argv[1]
n = int(sys.argv[2])

with open(fname, 'wb') as fid:
    for i in range(n):
        # write the IP (from 0x00000001 to 0xFFFFFFFE)        
        fid.write(randint(1,0xFFFFFFFE).to_bytes(4, 'big'))
        # write the # of bits for the subnet mask (from 1 to 30)
        fid.write(randint(1,30).to_bytes(1, 'big'))