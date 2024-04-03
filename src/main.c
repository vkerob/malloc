#include "../include/mem.h"

void print_data(t_data *data) {
    printf("Data tiny: %p\n", data->tiny);
    printf("Data small: %p\n", data->small);
    printf("Data large: %p\n", data->large);
    printf("Data error: %d\n", data->error);
    printf("Data return_user_space: %p\n", data->return_user_space);
}

void print_heap(t_heap *heap) {
	if (heap == NULL)
		return ;
    printf("Heap size: %d\n", heap->size);
    printf("Heap count_blocks: %d\n\n", heap->count_blocks);
    // Vous devrez peut-être créer une fonction séparée pour imprimer les détails de mem_block
}

void print_heap_large(t_heap_large *heap_large) {
	if (heap_large == NULL)
		return ;
    printf("Heap Large start_user_space: %p\n", heap_large->start_user_space);
    printf("Heap Large size_allocated: %zu\n\n", heap_large->size_allocated);
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_mem_block(t_mem_block *mem_block) {
	if (mem_block == NULL)
		return ;
    printf("Mem Block user_space: %p\n\n", mem_block->user_space);
    // Vous devrez peut-être créer une fonction séparée pour imprimer les détails de free_space
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_user_space(t_user_space *user_space) {
	if (user_space == NULL)
		return ;
    printf("User Space start_user_space: %p\n", user_space->start_user_space);
    printf("User Space size_allocated: %zu\n\n", user_space->size_allocated);
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_free_space(t_free_space *free_space) {
	if (free_space == NULL)
		return ;
    printf("Free Space free_size: %zu\n", free_space->free_size);
    printf("Free Space start_free_space: %p\n\n", free_space->start_free_space);
    // Vous devrez peut-être créer des fonctions séparées pour imprimer les détails des éléments suivants et précédents
}

void print_all_structures()
{
    // Vous devrez passer les instances appropriées de vos structures à ces fonctions
    print_data(data);
    print_heap(data->tiny);
    print_mem_block(data->tiny->start_block);
    print_user_space(data->tiny->start_block->user_space);
    print_free_space(data->tiny->start_block->free_area);

	print_heap(data->small);
	print_mem_block(data->small->start_block);
	print_user_space(data->small->start_block->user_space);
	print_free_space(data->small->start_block->free_area);

    print_heap_large(data->large);
}

int main()
{
	char *str1 = malloc(5000 * sizeof(char));
	print_all_structures();
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	write(1, str1, 1);
	free(str1);
	// char *str2 = malloc(1 * sizeof(char));
	// str2[0] = 'a';
	// write(1, str2, 1);
	// void * test = realloc(str1, 2 * sizeof(char));
	// write(1, test, 2);
	return (0);
}