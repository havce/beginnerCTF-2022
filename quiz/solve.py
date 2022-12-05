from pwn import *

io = connect("quiz.chals.beginner.havce.it", 31339)

io.recvuntil(b"Let's start!\n")

for i in range(50):
    io.recvuntil(b"submit ")
    line = io.recvline().strip()
    
    io.sendlineafter(b"> ", str(eval(line)).encode())    
    
io.interactive()