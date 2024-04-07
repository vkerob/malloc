#include "../include/mem.h"

int main()
{
	char *str1 = malloc(3 * sizeof(char));
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	char *str2 = malloc(1 * sizeof(char));
	str2[0] = 'a';
	char * test = realloc(str1, 2 * sizeof(char));
	show_alloc_mem();
	free(test);
	free(str2);
	return (0);
}