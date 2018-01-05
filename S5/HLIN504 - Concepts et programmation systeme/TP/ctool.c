#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char ch;
	printf("test\n");
	for(int i = -128 ; i < 128 ; i++)
		printf("%i : %c\n", i, i);

	getchar();
	return 0;
}