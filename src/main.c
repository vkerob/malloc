#include "../include/mem.h"

bool	test_tiny1(int show)
{
	char *str1 = malloc(1 * sizeof(char));
	char *str2 = malloc(1 * sizeof(char));
	char *str3 = malloc(4094 * sizeof(char));
	char *str4 = malloc(1 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);

}

bool	test_tiny2(int show)
{
	char *str3 = malloc(4094 * sizeof(char));
	char *str1 = malloc(1 * sizeof(char));
	char *str2 = malloc(1 * sizeof(char));
	char *str4 = malloc(1 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str1);
	free(str4);
	free(str3);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_tiny3(int show)
{
	char *str1 = malloc(1 * sizeof(char));
	free(str1);
	char *str2 = malloc(1 * sizeof(char));
	char *str3 = malloc(4094 * sizeof(char));
	char *str4 = malloc(1 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_tiny4(int show)
{
	char *str1 = malloc(1 * sizeof(char));
	char *str2 = malloc(1 * sizeof(char));
	free(str1);
	char *str3 = malloc(4094 * sizeof(char));
	free(str3);
	char *str4 = malloc(1 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_small1(int show)
{
	char *str1 = malloc(4097 * sizeof(char));
	char *str2 = malloc(4097 * sizeof(char));
	char *str3 = malloc(8190 * sizeof(char));
	char *str4 = malloc(4097 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_small2(int show)
{
	char *str3 = malloc(8190 * sizeof(char));
	char *str1 = malloc(4097 * sizeof(char));
	char *str2 = malloc(4097 * sizeof(char));
	char *str4 = malloc(4097 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str1);
	free(str4);
	free(str3);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_small3(int show)
{
	char *str1 = malloc(4097 * sizeof(char));
	free(str1);
	char *str2 = malloc(4097 * sizeof(char));
	char *str3 = malloc(8190 * sizeof(char));
	char *str4 = malloc(4097 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_small4(int show)
{
	char *str1 = malloc(4097 * sizeof(char));
	char *str2 = malloc(4097 * sizeof(char));
	free(str1);
	char *str3 = malloc(8190 * sizeof(char));
	free(str3);
	char *str4 = malloc(4097 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_large1(int show)
{
	char *str1 = malloc(16385 * sizeof(char));
	char *str2 = malloc(16385 * sizeof(char));
	char *str3 = malloc(32768 * sizeof(char));
	char *str4 = malloc(16385 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_large2(int show)
{
	char *str3 = malloc(32768 * sizeof(char));
	char *str1 = malloc(16385 * sizeof(char));
	char *str2 = malloc(16385 * sizeof(char));
	char *str4 = malloc(16385 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str1);
	free(str4);
	free(str3);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_large3(int show)
{
	char *str1 = malloc(16385 * sizeof(char));
	free(str1);
	char *str2 = malloc(16385 * sizeof(char));
	char *str3 = malloc(32768 * sizeof(char));
	char *str4 = malloc(16385 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str3);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

bool	test_large4(int show)
{
	char *str1 = malloc(16385 * sizeof(char));
	char *str2 = malloc(16385 * sizeof(char));
	free(str1);
	char *str3 = malloc(32768 * sizeof(char));
	free(str3);
	char *str4 = malloc(16385 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str4);
	if (data != NULL)
		return (false);
	return (true);
}

void	test_tiny()
{
	if (test_tiny1(0) == false)
		write(1, "test_tiny1 failed\n", 19);
	if (test_tiny2(0) == false)
		write(1, "test_tiny2 failed\n", 19);
	if (test_tiny3(0) == false)
		write(1, "test_tiny3 failed\n", 19);
	if (test_tiny4(0) == false)
		write(1, "test_tiny4 failed\n", 19);
}

void	test_small()
{
	if (test_small1(0) == false)
		write(1, "test_small1 failed\n", 20);
	if (test_small2(0) == false)
		write(1, "test_small2 failed\n", 20);
	if (test_small3(0) == false)
		write(1, "test_small3 failed\n", 20);
	if (test_small4(0) == false)
		write(1, "test_small4 failed\n", 20);
}

void	test_large()
{
	if (test_large1(0) == false)
		write(1, "test_large1 failed\n", 20);
	if (test_large2(0) == false)
		write(1, "test_large2 failed\n", 20);
	if (test_large3(0) == false)
		write(1, "test_large3 failed\n", 20);
	if (test_large4(0) == false)
		write(1, "test_large4 failed\n", 20);
}

void	test_heap_tiny()
{
	test_tiny();
	test_small();
	test_large();
}

int main()
{
	test_heap_tiny();
	return (0);
}