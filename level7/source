#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char c[68];

void m() // 0x080484f4
{
  time_t tim;
  
  tim = time((time_t *)0x0);
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

  strcpy((char *)str1[1], argv[1]); // 20 -> puts
  strcpy((char *)str2[1], argv[2]); // puts -> m

  flag = fopen("/home/user/level8/.pass","r");

  fgets(c, 68, flag);

  puts("~~");
  return 0;
}