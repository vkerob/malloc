#include "../include/mem.h"

bool	test_tiny1(int show)
{
	char *str1 = malloc(80 * sizeof(char));
	char *str2 = malloc(80 * sizeof(char));
	char *str3 = malloc(81 * sizeof(char));
	char *str4 = malloc(80 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str1);
	str1 = malloc(1 * sizeof(char));
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
		return (false);
	return (true);
}

bool	test_small1(int show)
{
	char *str1 = malloc(1999 * sizeof(char));
	char *str2 = malloc(1999 * sizeof(char));
	char *str3 = malloc(2001 * sizeof(char));
	char *str4 = malloc(1999 * sizeof(char));
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
		return (false);
	return (true);
}

bool	test_small2(int show)
{
	char *str3 = malloc(4000 * sizeof(char));
	char *str1 = malloc(1999 * sizeof(char));
	char *str2 = malloc(1999 * sizeof(char));
	char *str4 = malloc(1999 * sizeof(char));
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
		return (false);
	return (true);
}

bool	test_small3(int show)
{
	char *str1 = malloc(1999 * sizeof(char));
	free(str1);
	char *str2 = malloc(1999 * sizeof(char));
	char *str3 = malloc(4000 * sizeof(char));
	char *str4 = malloc(1999 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str3);
	free(str4);
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
		return (false);
	return (true);
}

bool	test_small4(int show)
{
	char *str1 = malloc(1999 * sizeof(char));
	char *str2 = malloc(1999 * sizeof(char));
	free(str1);
	char *str3 = malloc(4000 * sizeof(char));
	free(str3);
	char *str4 = malloc(1999 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	if (show)
		show_alloc_mem();
	free(str2);
	free(str4);
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
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
	if (data->large_heap != NULL && data->tiny_heap != NULL && data->small_heap != NULL)
		return (false);
	return (true);
}

void	test_tiny()
{
	ft_printf("test_tiny:\n");
	if (test_tiny1(1) == false)
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
	ft_printf("\ntest_small:\n");
	if (test_small1(1) == false)
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
	ft_printf("\ntest_large:\n");
	if (test_large1(1) == false)
		write(1, "test_large1 failed\n", 20);
	if (test_large2(0) == false)
		write(1, "test_large2 failed\n", 20);
	if (test_large3(0) == false)
		write(1, "test_large3 failed\n", 20);
	if (test_large4(0) == false)
		write(1, "test_large4 failed\n", 20);
}

void	test0()
{
    int   i;
    char  *addr;

    i = 0; 
    while (i < 1024) 
    {
        i++;
    } 
    return (0); 
}

void	test1()
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        if (addr == NULL)
        {
            ft_printf("Failed to allocate memory\n");
            return (1);
        }
        for (int j = 0; j < 1023; j++)
        {
            addr[j] = 42;
        }
        i++;
    }
    return (0);
}

void	test2()
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024) 
    {
        addr = (char*)malloc(1024);
        if (addr == NULL)
        {
            ft_printf("Failed to allocate memory\n");
            return (1);
        }
        addr[0] = 42;
        free(addr); 
        i++; 
    }
    return (0);
}


#define M (1024 * 1024)
void	test3()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char*)malloc(16*M);
    if (addr1 == NULL)
    {
        ft_printf("Failed to allocate memory\n");
        exit(1);
    }
    strcpy(addr1, "Hello world!\n");
    ft_printf(addr1);
    addr2 = (char*)malloc(16*M);
    if (addr2 == NULL)
    {
        ft_printf("Failed to allocate memory\n");
        exit(1);
    }
    addr3 = (char*)realloc(addr1, 128*M);
    if (addr3 == NULL)
    {
        ft_printf("Failed to reallocate memory\n");
        exit(1);
    }
    addr3[127*M] = 42;
    ft_printf(addr3);
    return (0);
}

void	test4()
{
    void* a = malloc(1);
    void* b = malloc(2);
    void* c = malloc(4);
    void* d = malloc(8);
    void* e = malloc(16);
    void* f = malloc(32);
    void* g = malloc(64);
    void* h = malloc(128);
    void* i = malloc(256);
    void* j = malloc(512);
    void* k = malloc(1024);
    void* l = malloc(1024 * 2);
    void* m = malloc(1024 * 4); 
    void* n = malloc(1024 * 32);
    void* o = malloc(M);
    void* p = malloc(16*M);
    void* q = malloc(128*M);
    show_alloc_mem(); 
    return (0); 
}

void	test5()
{
    int     i;
    int     alignment;
    char    *addr;

    i = 1;
    alignment = 2 * sizeof(size_t);
    while (i <= 100)
    {
        addr = (char*)malloc(i);
        if (addr == NULL)
        {
            ft_printf("Failed to allocate memory\n");
            exit(1);
        }
        if ((((unsigned long) (addr)) % alignment) != 0)
        {
            ft_printf("malloc returned a non aligned boundary\n");
            exit(1);
        }
        i++;
        free(addr);
    }
    ft_printf("Alignement OK\n");
}

void	test_heap()
{
	test_tiny();
	test_small();
	test_large();
}

void	test_rapide()
{
	int i = 0;
	char **str = malloc(120 * sizeof(char *));

	while (i < 101)
	{
		str[i] = malloc(99);
		i++;
	}
	show_alloc_mem();
}

int main()
{
	test1();
	//test_rapide();
	return (0);
}