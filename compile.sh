#!/bin/bash

gcc -O3 -DDSFMT_MEXP=521 -o test ~/Lib/dSFMT-src-2.2.3/dSFMT.c classical_ising_long.c -lm
