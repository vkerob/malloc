#include "../include/mem.h"

int main()
{
	char *str1 = malloc(1 * sizeof(char));
	str1[0] = 'a';
	write(1, str1, 1);
	char *str2 = malloc(1 * sizeof(char));
	str2[0] = 'a';
	write(1, str2, 1);
	void * test = realloc(str1, 2 * sizeof(char));
	(void)test;
	return (0);
}