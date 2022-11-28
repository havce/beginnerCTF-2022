#!/usr/bin/python3

import os
from base64 import b64encode
from secret import flag

def xor(pt, key):
	NTIMES = int(len(pt) / len(key))+1
	return bytes([ x ^ y for x,y in zip(pt, key*NTIMES)])

# Look at how many combinations...
key = os.urandom(8)

with open("output", "w") as output_file:
	output_file.write(b64encode(xor(flag, key)).decode())

