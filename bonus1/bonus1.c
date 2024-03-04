#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		number;
	char	s1[40];

	number = atoi(argv[1]);
	if (number < 10) {
		memcpy(s1, argv[2], number * 4);
		if (number == 0x574f4c46) {
			execl("/bin/sh", "sh", 0);
		}
	} else {
		return (1);
	}
	return (0);
}