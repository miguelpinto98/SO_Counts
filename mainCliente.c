#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
	int pp = open("/tmp/options", O_WRONLY, 0700);

	write(pp, argv[1], strlen(argv[1])+1);

	return 0;
}