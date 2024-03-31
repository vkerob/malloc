#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define TINY 1
#define SMALL 4
#define LARGE 8

// struct for each heap

typedef struct heap
{
	int					size;				// size of each block
	int					count_blocks;		// number of blocks
	struct mem_block	*start_block;		// start of the heap

}				t_heap;

typedef struct heap_large
{
	struct mem_block	*block;
	struct heap_large	*next;
}				t_heap_large;

typedef struct mem_block
{
	void				*start_user_space;	// start of the block
	int					free_size;			// size of the block
	struct free_space	*free_area;			// free space
	struct mem_block	*next;				// next block
	struct mem_block	*prev;				// previous block
	
}				t_mem_block;

typedef struct free_space
{
	void				*start;				// start of the free space
	size_t				size;				// size of the free space
	struct free_space	*next;				// next free space
	struct free_space	*prev;				// previous free space
}				t_free_space;

typedef struct	data
{
	struct heap			*tiny;
	struct heap			*small;
	struct heap_large	*large;
	bool				error;
	void				*start_user_space;
}				t_data;


void	show_alloc_mem();
// void	free(void *ptr);
void	*malloc(size_t size);
// void	*realloc(void *ptr, size_t size);

void	initialize_data(t_data **data);
void	initialize_heap(t_heap *heap, size_t size);
void	initialize_block(t_mem_block *block, size_t size, t_mem_block *block_prev);

void	allocate(t_data *data, t_heap **heap, size_t size, size_t type);
void	allocate_large(t_data *data, size_t size);

void	*find_free_space(t_heap *heap, size_t size);



#endif