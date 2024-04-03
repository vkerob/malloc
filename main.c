#include <stdio.h>
#include <stdlib.h>

int main()
{

	char *str2 = malloc(23 * sizeof(char));
	str2[0] = 'a';
	str2[1] = 'b';
	str2[2] = 'c';
	str2[3] = 'd';
	void * test = realloc(str2, 2 * sizeof(char));
	printf("%p\n", test);
	printf("%s\n", ((char *)test));
	(void)test;
	free(test);
	return (0);
}