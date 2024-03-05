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
