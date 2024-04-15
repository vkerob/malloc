#include "../include/mem.h"

void	test_heap_tiny()
{
	char *str1 = malloc(1 * sizeof(char));
	char *str2 = malloc(1 * sizeof(char));
	char *str3 = malloc(4094 * sizeof(char));
	char *str4 = malloc(1 * sizeof(char));
	char *str5 = malloc(4097 * sizeof(char));
	int	 *tab1 = malloc(2500 * sizeof(int));
	char *str6 = malloc(20000 * sizeof(char));
	char *str7 = malloc(20000 * sizeof(char));
	show_alloc_mem();
	str1[0] = 'a';
	str2[0] = 'a';
	str3[0] = 'a';
	str4[0] = 'a';
	str5[0] = 'a';
	str6[0] = 'a';
	str7[0] = 'a';
	tab1[0] = 42;
	free(str7);
	free(str1);
	free(str2);
	free(str4);
	free(str5);
	free(str6);
	free(str3);
	free(tab1);
}

int main()
{
	test_heap_tiny();
	return (0);
}