#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>


// gcc src/test.c && strace --output=test.txt ./a.out && cat test.txt | grep "mmap" && cat test.txt | grep "munmap"


void	tiny_100()
{
	printf("\ntiny_100:\n");
	char **strs = malloc(100 * sizeof(char *));
	for (int i = 0; i < 100; i++)
	{
		strs[i] = malloc(112 * sizeof(char));
		(void)strs[i];
	}
	for (int i = 0; i < 100; i++)
	{
		free(strs[i]);
	}
	free(strs);
}

void	small_100()
{
	printf("\nsmall_100:\n");
	char **strs = malloc(100 * sizeof(char *));
	for (int i = 0; i < 100; i++)
	{
		strs[i] = malloc(2560 * sizeof(char));
		(void)strs[i];
	}
	for (int i = 0; i < 100; i++)
	{
		free(strs[i]);
	}
	free(strs);
}

void	alloacte_test_100()
{
	tiny_100();
	small_100();
}

// #include <pthread.h>
// #include <string.h>

// Taille de mémoire à allouer
#define ALLOCATION_SIZE 128
// Nombre de threads à lancer
#define NUM_THREADS 5

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d démarré\n", thread_id);

    char* ptr = malloc(ALLOCATION_SIZE);
    if (!ptr) {
        printf("Thread %d: malloc a échoué\n", thread_id);
        return NULL; // removed pthread_exit
    }
    printf("Thread %d: mémoire allouée à l'adresse %p\n", thread_id, (void*)ptr);

    // Build the string manually
    const char* prefix = "Thread ";
    int idx = 0;
    for (int i = 0; prefix[i] != '\0' && idx < ALLOCATION_SIZE - 1; i++) {
        ptr[idx++] = prefix[i];
    }
    // Convert thread_id to characters
    {
        int temp = thread_id, revIdx = 0;
        char revBuf[16]; // enough for digits
        if (temp == 0) {
            revBuf[revIdx++] = '0';
        } else {
            while (temp > 0 && revIdx < 15) {
                revBuf[revIdx++] = (char)('0' + (temp % 10));
                temp /= 10;
            }
        }
        // Copy reversed digits
        while (revIdx > 0 && idx < ALLOCATION_SIZE - 1) {
            ptr[idx++] = revBuf[--revIdx];
        }
    }
    const char* suffix = " test";
    for (int i = 0; suffix[i] != '\0' && idx < ALLOCATION_SIZE - 1; i++) {
        ptr[idx++] = suffix[i];
    }
    ptr[idx] = '\0';

    printf("Thread %d: mémoire initialisée avec contenu : %s\n", thread_id, ptr);

    free(ptr);
    printf("Thread %d: mémoire libérée\n", thread_id);

    return NULL;
}

void thread_test()
{
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) {
	    thread_ids[i] = i;
	    if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
	        printf("Erreur lors de la création du thread %d\n", i);
	        return;
	    }
	}

	for (int i = 0; i < NUM_THREADS; i++) {
	    pthread_join(threads[i], NULL);
	}
	printf("Tous les threads ont terminé.\n");

	return;

}

void test_strace()
{
	char *tab1[100];
	char *tab2[100];
	char *tab3[100];

	for (int i = 0; i < 100; i++)
	{
		tab1[i] = malloc(112 * sizeof(char));
		(void)tab1[i];
	}
	for (int i = 0; i < 100; i++)
	{
		tab2[i] = malloc(112 * sizeof(char));
		(void)tab2[i];
	}
	for (int i = 0; i < 100; i++)
	{
		tab3[i] = malloc(112 * sizeof(char));
		(void)tab3[i];
	}
	for (int i = 0; i < 100; i++)
	{
		free(tab1[i]);
	}
	for (int i = 0; i < 100; i++)
	{
		free(tab2[i]);
	}
	for (int i = 0; i < 100; i++)
	{
		free(tab3[i]);
	}
}

void	realloc_test()
{
	char *str1 = malloc(112 * sizeof(char));
	char *str2 = malloc(112 * sizeof(char));
	char *str3 = malloc(113 * sizeof(char));
	char *str4 = malloc(112 * sizeof(char));
	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	str1 = realloc(str1, 1);
	str2 = realloc(str2, 1);
	str3 = realloc(str3, 1);
	str4 = realloc(str4, 1);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

void	realloc_test_tiny_to_small()
{
    char *str = malloc(100);
    printf("\nTest: tiny to small realloc\n");
    str = realloc(str, 1000);
    free(str);
}

void	realloc_test_small_to_large()
{
    char *str = malloc(1000);
    printf("\nTest: small to large realloc\n");
    str = realloc(str, 10000);
    free(str);
}

void	realloc_test_large_to_small()
{
    char *str = malloc(10000);
    printf("\nTest: large to small realloc\n");
    str = realloc(str, 1000);
    free(str);
}

void	realloc_test_null_ptr()
{
    char *str = NULL;
    printf("\nTest: realloc with NULL pointer\n");
    str = realloc(str, 100);
    free(str);
}

void	realloc_test_zero_size()
{
    char *str = malloc(100);
    printf("\nTest: realloc with zero size\n");
    str = realloc(str, 0);
}

void	realloc_test_same_size()
{
    char *str = malloc(100);
    strcpy(str, "Test string");
    printf("\nTest: realloc with same size\n");
    str = realloc(str, 100);
    printf("Content after realloc: %s\n", str);
    free(str);
}

void	realloc_stress_test()
{
    char *ptrs[10];
    printf("\nTest: realloc stress test\n");
    
    // Initial allocations
    for (int i = 0; i < 10; i++) {
        ptrs[i] = malloc(50);
    }

    // Multiple reallocs
    for (int i = 0; i < 10; i++) {
        ptrs[i] = realloc(ptrs[i], 100 * (i + 1));
    }

    // Shrink some allocations
    for (int i = 0; i < 5; i++) {
        ptrs[i] = realloc(ptrs[i], 50);
    }

    // Free everything
    for (int i = 0; i < 10; i++) {
        free(ptrs[i]);
    }
}

void	extended_realloc_tests()
{
    realloc_test_tiny_to_small();
    realloc_test_small_to_large();
    realloc_test_large_to_small();
    realloc_test_null_ptr();
    realloc_test_zero_size();
    realloc_test_same_size();
    realloc_stress_test();
}

// make test && strace --output=test.txt ./test && cat test.txt | grep "mmap" && cat test.txt | grep "munmap"

int main()
{
	alloacte_test_100();
	realloc_test();
    extended_realloc_tests();
    thread_test();
    
    return (0);
}