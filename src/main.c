#include "../include/mem.h"

int main()
{
	char *str = malloc(1 * sizeof(char));
	str[0] = 'a';
	printf("%s\n", str);
	return (0);
}