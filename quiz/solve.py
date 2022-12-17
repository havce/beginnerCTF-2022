from pwn import *

io = connect("quiz.chals.beginner.havce.it", 31339)

io.recvuntil(b"Let's start!\n")

for i in range(50):
    io.recvuntil(b"submit ")
    line = io.recvline().strip()
    
    # Actually dangerous. Run `eval` on user data only
    # when the user is at punch-in-the-face-able distance.
    # `eval` allows an user to execute arbitrary Python code.
    io.sendlineafter(b"> ", str(eval(line)).encode())    
    
io.interactive()
