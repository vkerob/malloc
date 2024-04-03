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
	void				*start_user_space;
	size_t				size_allocated;
	struct heap_large	*next;
	struct heap_large	*prev;
}				t_heap_large;

typedef struct user_space
{
	void				*start_user_space;
	size_t				size_allocated;
	struct user_space	*next;
	struct user_space	*prev;
	struct mem_block	*parent_block;
}				t_user_space;


typedef struct mem_block
{
	struct user_space	*user_space;		// user space
	struct free_space	*free_area;			// free space
	struct mem_block	*next;				// next block
	struct mem_block	*prev;				// previous block
	
}				t_mem_block;

// each block has a free space

typedef struct free_space
{
	size_t				free_size;
	void 				*start_free_space;
	struct free_space	*next;				// next free space
	struct free_space	*prev;				// previous free space
}				t_free_space;

typedef struct	data
{
	struct heap			*tiny;
	struct heap			*small;
	struct heap_large	*large;
	bool				error;
	void				*return_user_space;
}				t_data;

extern t_data *data;

 // general functions
void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

// init functions
void	initialize_data(t_data **data);
void	initialize_heap(t_heap *heap, size_t size);
void	initialize_block(t_heap **heap, t_mem_block *block, size_t size, t_mem_block *block_prev, size_t type);

// allocate functions
void	allocate(t_heap **heap, size_t size, size_t type);
void	allocate_large(size_t size);

//  general utils functions
bool	find_free_space(t_heap *heap, size_t size);
void	find_ptr(t_user_space **user_space_tmp, t_heap_large **heap_large_tmp ,void *ptr, size_t *type);


// realloc utils functions
void	find_old_area_copy_and_free(void *ptr, size_t size);
void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type);


#endif