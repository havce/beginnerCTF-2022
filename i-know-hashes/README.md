# i-know-hashes
## Description
> Don't worry, I know how hashes work.

*Author: [@devgianlu](https://github.com/devgianlu)*
## Flag
`havceCTF{th4t_1s_n0t_h0w_h4sh3s_w0rk}`

## Solution 
This challenge shows poor handling of hashes, hashing one character at a time produces very week 
hashes that can be bruteforced very easily or looked up on sites that provide a table of known
hashes (e.g. https://crackstation.net/). By using one of the methods above you can fully recover
the flag.