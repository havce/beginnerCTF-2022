# Magic

## Description
> There seems to be no way to extract this zip... Maybe it's something else

*Author: [@samuelevalperta](https://github.com/samuelevalperta)*
## Solution
[Magic bytes](https://en.wikipedia.org/wiki/List_of_file_signatures) are the first few bytes of a file and are used to identify its content.
The `file magic.zip` command is able to read these bytes and tell us the real file format of `magic.zip` (which is `png`).<br>
We only have to rename `magic.zip` to `magic.png` and open it to get the flag.

## Flag
`havceCTF{m4g1c_byt3s_n3v3r_li3}`