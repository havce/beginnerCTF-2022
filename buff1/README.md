# buff1
## Description
> can u call the win function?

*Author: [@Ferr0x](https://github.com/Ferr0x)*
## Solution
There is a buffer overflow vulnerability when using `gets`.

Since the binary is compiled without a stack canary and isn't position independent,
we can overwrite the return address of the `main` function with the address of `win`.

You can see a simple solve script in [exp.py](exp.py). 

## Flag
`havceCTF{ret2win_is_way_t0o_easy}`

