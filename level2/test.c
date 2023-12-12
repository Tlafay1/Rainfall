#include <stdio.h>
#include <errno.h>
int main(int ac, char **av) 
{
    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", EACCES, EACCES, EACCES, EACCES, EAGAIN, EFAULT, EINVAL, EIO, EISDIR, ELIBBAD, ELOOP, ELOOP, EMFILE, ENAMETOOLONG, ENFILE, ENOENT, ENOEXEC, ENOMEM, ENOTDIR, EPERM, EPERM, EPERM, ETXTBSY);
}

