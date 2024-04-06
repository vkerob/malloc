#include "../include/mem.h"

void print_data(t_data *data) {
    printf("Data tiny: %p\n", data->tiny_heap);
    printf("Data small: %p\n", data->small_heap);
    printf("Data large: %p\n", data->large_heap);
    printf("Data error: %d\n", data->error);
    printf("Data return_user_space: %p\n", data->user_space_pointer);
}

void print_user_space(t_user_space *user_space) {
	if (user_space == NULL)
		return ;
	while (user_space->next)
	{
		printf("User Space start_user_space: %p\n", user_space->start_user_space);
		printf("User Space size_allocated: %zu\n\n", user_space->size_allocated);
		printf("User Space parent_block: %p\n\n", user_space->parent_block);
		printf("User Space next: %p\n\n", user_space->next);
		printf("User Space prev: %p\n\n", user_space->prev);
		user_space = user_space->next;
	}
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_free_space(t_free_space *free_space) {
	if (free_space == NULL)
		return ;
	while (free_space->next)
	{
		printf("Free Space free_size: %zu\n", free_space->free_size);
		printf("Free Space start_free_space: %p\n\n", free_space->start_free_space);
		printf("Free Space next: %p\n\n", free_space->next);
		printf("Free Space prev: %p\n\n", free_space->prev);
		free_space = free_space->next;
	}
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_block(t_block *mem_block) {
	if (mem_block == NULL)
		return ;
	while (mem_block->user_space)
	{
    	printf("Mem Block user_space: %p\n\n", mem_block->user_space);
		printf("Mem Block next: %p\n\n", mem_block->next);
		printf("Mem Block prev: %p\n\n", mem_block->prev);
		print_user_space(mem_block->user_space);
		mem_block->user_space = mem_block->user_space->next;
	}
    // Vous devrez peut-être créer une fonction séparée pour imprimer les détails de free_space
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_heap(t_heap *heap) {
	if (heap == NULL)
		return ;
    printf("Heap size: %zu\n", heap->size);
	printf("Heap start_block: %p\n\n", heap->start_block);
	printf("Heap free_area: %p\n\n", heap->free_area);
	print_free_space(heap->free_area);
	while (heap->start_block)
	{
		print_block(heap->start_block);
		heap->start_block = heap->start_block->next;
	}

    // Vous devrez peut-être créer une fonction séparée pour imprimer les détails de mem_block
}

void print_heap_large(t_heap_large *heap_large) {
	if (heap_large == NULL)
		return ;
    printf("Heap Large start_user_space: %p\n", heap_large->start_user_space);
    printf("Heap Large size_allocated: %zu\n\n", heap_large->size_allocated);
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}



void print_all_structures()
{
    // Vous devrez passer les instances appropriées de vos structures à ces fonctions
    print_data(data);
	print_heap(data->tiny_heap);
	print_heap(data->small_heap);
}

int main()
{
	char *str1 = malloc(5000 * sizeof(char));
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	write(1, str1, 1);
	char *str2 = malloc(1 * sizeof(char));
	str2[0] = 'a';
	write(1, str2, 1);
	char * test = realloc(str1, 2 * sizeof(char));
	write(1, "\n", 1);
	write(1, test, 2);
	show_alloc_mem();
	free(str2);
	free(test);
	return (0);
}