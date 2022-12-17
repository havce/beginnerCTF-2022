# login
## Description
> You need just to login to read the flag.

## Solution
There are three buffer overflow vulnerabilities, when using the `"%s"` format string inside `scanf`.
The `"%s"` format string allows an attacker to input unlimited numbers of characters.

We can use the `scanf("%s", cf);` to fill the `cf` field of the struct and then overwrite the `auth` field
with something different from `0` (everything != 0 is *truthy* in C).

We could send something like this to retrieve the flag: `b"A" * 16 + b"Z"`. 
(Please note that `Z` in ASCII is `0x5a`, so the auth field would contain `0x5a`, which is different from `0`)

## Flag
`havceCTF{did_u_enjoy_th3_overlow?}`
