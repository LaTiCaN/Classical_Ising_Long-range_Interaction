# Long-range interaction classical Ising model
## Code
Last edit -2024.03.31-  
Made by **C** code.  
**Compiler :** gcc
  
**Used external library :**  
- dSFMT (Double precision SIMD-oriented Fast Mersenne Twister) http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/#dSFMT  
- NRinC (Numerical-Recipies-in-C) https://github.com/saulwiggin/Numerical-Recipies-in-C  
  -> git: https://github.com/saulwiggin/Numerical-Recipies-in-C.git

**Useage**  
1. Execute the compile.sh
2. Make a runfile "run.sh" used by "makerun.awk"
     
   - Awk file executing process
     ```
     awk -f makerun.awk -> run.sh
     ```
   - If you want a check that the "makerun.awk" file give correct command.
     ```
     awk -f makerun.awk
     ```   
   
