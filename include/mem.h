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
	struct free_area	*free_area;			// free space
}				t_heap;

typedef struct large_heap
{
	void				*start_user_space;
	size_t				size_allocated;
	struct large_heap	*next;
	struct large_heap	*prev;				// needed for unlink
}				t_large_heap;

typedef struct user_space
{
	void				*start_user_space;
	void				*ptr_defragment;	// the start of the user space but he can't change
	size_t				size_allocated;
	struct block		*parent_block;		// needed for realloc
	struct user_space	*next;
	struct user_space	*prev;
}				t_user_space;

typedef struct block
{
	struct user_space	*user_space;		// user space
	struct heap			*parent_heap;
	struct block		*next;				// next block
	struct block		*prev;				// previous block (needed for free_area)
	
}				t_block;

typedef struct free_area
{
	size_t				free_size;
	void 				*start_free_area;
	void				*ptr_defragment;	// the start of the user space but he can't change
	struct heap			*parent_heap;
	struct free_area	*next;				// next free space
	struct free_area	*prev;				// previous free space
}				t_free_area;

typedef struct	data
{
	struct heap			*tiny_heap;
	struct heap			*small_heap;
	struct large_heap	*large_heap;
	bool				error;
	size_t				page_size;
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
void	initialize_block(t_heap *heap, size_t size, size_t type);
void	initialize_large_heap(t_large_heap **new_large_heap, t_large_heap *large_heap_prev, size_t size);

// allocate functions
void	found_space_or_allocate(t_heap **heap, size_t size, int type);
void	allocate(t_heap **heap, size_t size, size_t type);
void	allocate_large(size_t size);

//  general utils functions
bool	search_free_space(t_heap *heap, size_t size);
void	find_ptr(t_user_space **user_space_tmp, t_large_heap **large_heap_tmp ,void *ptr, size_t *type);
// unlink functions
void	unlink_large_heap(t_large_heap *large_heap);
void	unlink_user_space(t_user_space *user_space);
// link functions
void	link_user_space(t_user_space *user_space, t_user_space *user_space_prev);
void	link_large_heap(t_large_heap *new_large_heap, t_large_heap *large_heap_prev);

// realloc utils functions
void	find_old_area_copy_and_free(void *ptr, size_t size);
void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type);

// free utils functions
// delete functions
void	delete_user_space_or_block(t_heap **heap, t_user_space *user_space);
void	delete_large_heap(t_large_heap *large_heap);
// add functions
void add_free_area_and_defragment(t_user_space *user_space);

// free functions
void	free_all(void);
#endif