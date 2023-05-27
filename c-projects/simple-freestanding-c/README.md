# Freestanding C Example/Demo

This is an example of a C program running without being linked to a libc. How
it does it is by using a syscall invoker written in assembly, which is then
imported into C and then used by whatever syscall wrapper you wanna use

This demo only implements `write` and `_exit`, and only implements the syscall
invoker in x86 (both 32-bit and 64-bit)

# Running the demo

To run the demo, run this:

```c
cc -nodefaultlibs -nostartfiles -fno-stack-protector -static main.c syscall-$(uname -m) -o test
./test
```

*On 32-bit systems, you may have to change `$(uname -m)` to `i686` (as that's
the actual name of the file)
