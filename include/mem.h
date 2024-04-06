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
	size_t				size;
	struct block		*start_block;		// start of the heap
	struct free_space	*free_area;			// free space
}				t_heap;

typedef struct heap_large
{
	void				*start_user_space;
	size_t				size_allocated;
	struct heap_large	*next;
	struct heap_large	*prev;				// needed for delink
}				t_heap_large;

typedef struct user_space
{
	void				*start_user_space;
	size_t				size_allocated;
	struct block		*parent_block;		// needed for realloc
	struct user_space	*next;
	struct user_space	*prev;
}				t_user_space;


typedef struct block
{
	struct user_space	*user_space;		// user space
	struct block		*next;				// next block
	struct block		*prev;				// previous block (needed for free_area)
	
}				t_block;


typedef struct free_space
{
	size_t				free_size;
	void 				*start_free_space;
	struct free_space	*next;				// next free space
	struct free_space	*prev;				// previous free space
}				t_free_space;

typedef struct	data
{
	struct heap			*tiny_heap;
	struct heap			*small_heap;
	struct heap_large	*large_heap;
	bool				error;
	void				*user_space_pointer;
}				t_data;

extern t_data *data;

 // general functions
void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

// init functions
void	initialize_data(t_data **data);
void	initialize_heap(t_heap **heap, size_t size);
void	initialize_block(t_heap *heap, t_block **block, size_t size, t_block *block_prev, size_t type);

// allocate functions
void	allocate_or_found_space_not_found(t_heap **heap, size_t size, int type);
void	allocate(t_heap **heap, size_t size, size_t type);
void	allocate_large(size_t size);

//  general utils functions
bool	search_free_space(t_heap *heap, size_t size);
void	find_ptr(t_user_space **user_space_tmp, t_heap_large **heap_large_tmp ,void *ptr, size_t *type);


// realloc utils functions
void	find_old_area_copy_and_free(void *ptr, size_t size);
void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type);

// free utils functions
// delink functions
void	delink_heap_large(t_heap_large *heap_large);
void	delink_user_space(t_user_space *user_space);
// delete functions
void	delete_user_space_or_block(t_heap *heap, t_user_space *user_space, size_t type, size_t page_size);
void	delete_heap_large(t_heap_large *heap_large, size_t page_size);
// add functions
void add_free_area_and_defragment(t_heap *heap, t_user_space *user_space);

// free functions
void	free_all(void);
#endif