# Unzip pt.2
## Description
Let's Rock n Roll
## Solution
To solve this challenge you have use john_the_ripper that is a tool to brute force passwords.
One of the most famous wordlist for john_the_ripper is called Rock_you.txt.
You had to use `zip2john flag.zip > flah.hashes` then you had to use `john --wordlist=Rock_you.txt`.
Once you find the password just use `unzip flag.zip`.

**Flag: havceCTF{j0hn_th3_r1pp3r_p0w4!}**
