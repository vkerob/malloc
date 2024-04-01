#include <stdio.h>
#include <stdlib.h>

int main()
{

	char *str2 = malloc(1 * sizeof(char));
	void * test = realloc(str2, 2 * sizeof(char));
	printf("%p\n", test);
	(void)test;
	free(test);
	return (0);
}