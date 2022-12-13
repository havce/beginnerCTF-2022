# Secure login

## Description
> My employer asked me to create a secure login system for our company, it was super easy. Now we are protected... aren't we?

## Solution
The correct password to log-in is hardcoded in the binary file without any obfuscation.<br>
With the command `strings secure-login` you are able to print all the strings saved on the binary, including the flag. 

## Flag
`havceCTF{m4yb3_n0t_s0_s3cur3}`
