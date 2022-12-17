# Lottery
## Description
> This lottery is soooooo boring...

*Author: [@kriive](https://github.com/kriive)*
## Solution
The function `rand()` is called without calling `srand()` first, so the 
magic guess number is predictable. 

Per the man page of `rand(3)`:
> If no seed value is provided, the rand() function  is  automatically
> seeded with a value of 1.

One can copy the following to a new program:
```c
// exp.c
#include <stdio.h>
#include <stdlib.h>

int main() {
  long long result = 0;

  for (int i = 0; i < 1000; i++) {
    result += (long long)rand();
  }
  printf("%lld", result);
}
// ❯ gcc -o exp exp.c && ./exp
// 1091191137495
```
The result is the magic number and it can be submitted to the service to 
retrieve the flag.

## Flag
`havceCTF{th1s_is_wh4t_h3ppens_wh3n_u_d0nt_use_d3v_ur4nd0m}`
