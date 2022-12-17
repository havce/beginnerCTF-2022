# Scope
## Description
> I wrote this oscilloscope readings manager, with a simple shell attached. It is really super secure.

## Solution
There is a command injection vulnerability in the change password function.
```c
// Check if user knows the old password.
if (strncmp(old_password, buf, strlen(buf)) != 0) {
  puts("Old password is wrong!");
  goto cleanup;
}

// Reuse buf buffer.
snprintf(buf, BUF_LEN, "echo -n \"%s\" > %s", user->password, path);
res = system(buf) == 0;
```
If you input `"; cat flag.txt #` you effectively execute `cat flag.txt`. 

In the original exploit, you didn't know the admin password, so you
couldn't trigger the command injection without knowing the password.

In this snippet there is another vulnerability: the check via the `strncmp` function is broken. 
If you send an empty string you can bypass the check and enable the command injection
vulnerability (`strncmp` called with len==0 always returns 0).

This vulnerability has been found in the wild in a oscilloscope running Linux.

## Flag
`havceCTF{1his_1s_4ctually_a_vuln_f00und_1n_th3_w1iiild}`

