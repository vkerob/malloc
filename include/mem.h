#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <stdint.h>
#include "../libft/libft.h"

#define PAGE_SIZE getpagesize()

#define TINY_SIZE 				(size_t)(PAGE_SIZE * 4)		// 16384 bytes
#define SMALL_SIZE 				(size_t)(PAGE_SIZE * 64)	// 262144 bytes
#define LARGE 					1
// This implementation initializes a struct (data) at the beginning of 64 bytes. For example:
// Minimum allocation: 64 bytes (data) + 48 bytes (block size) + 48 bytes (user_space) = 160 bytes + size chosen by the user + alignment.
// If the user asks for 1 byte, the program will allocate 176 bytes (160 + 1 + 15) = 176 bytes because of alignment.


// Here we determine the maximum size of an allocation in each type of heap.
// We want to have a minimum of 100 allocations in each heap (trying to reproduce the behavior of the real malloc and respecting the 42 subject).
// How we calculate the maximum size of an allocation in each heap:
// For Tiny heap: (16384 - 48) / 100 = 115 bytes - 16 bytes (alignment) = 99 bytes.
// As a precaution, we subtract 16 bytes from the result to ensure that we can allocate 100 allocations because, for example,
// if we allocate 100 allocations of 113 bytes + 48 bytes (user_space) = 161 bytes, we are going to align the address to 176 bytes and
// we will not be able to allocate 100 allocations because 100 * 176 = 17600 > 16384.
// Same logic for the Small heap: (262144 - 48) / 100 = 2620 bytes - 16 bytes (alignment) = 2560 bytes.
// to sum up :
// TINY_MAX_SIZE_ALLOC = 99 bytes
// SMALL_MAX_SIZE_ALLOC = 2560 bytes
// LARGE_MAX_SIZE_ALLOC > 2560 bytes
#define TINY_MAX_SIZE_ALLOC		(size_t)((TINY_SIZE - ALLIGN_BLOCK) / 100) - MEN_ALLIGN		// 163 - 48 bytes = 115 bytes - 16 bytes (allign) = 99 bytes
#define SMALL_MAX_SIZE_ALLOC	(size_t)((SMALL_SIZE - ALLIGN_BLOCK) / 100) - MEN_ALLIGN	// 2620 - 48 bytes = 2576 bytes - 16 bytes (allign) = 2560 bytes

#define MEN_ALLIGN 				16
#define ALLIGN_DATA 			(size_t)align_address((void *)sizeof(t_data))
#define ALLIGN_BLOCK 			(size_t)align_address((void *)sizeof(t_block))
#define ALLIGN_USER_SPACE 		(size_t)align_address((void *)sizeof(t_user_space))
#define ALLIGN_HEAP 			(size_t)align_address((void *)sizeof(t_heap))
#define ALLIGN_LARGE_HEAP 		(size_t)align_address((void *)sizeof(t_large_heap))


extern pthread_mutex_t lock;


typedef struct	data // 56 bytes
{
	struct heap			*tiny_heap;
	struct heap			*small_heap;
	struct large_heap	*large_heap;
	struct rlimit		rlimit;
	void				*user_space_pointer;
	bool				error;
	//char				padding[7];	  gcc do this padding
}				t_data;

extern t_data *data;

typedef struct large_heap // 32 bytes
{
	struct large_heap	*next;
	struct large_heap	*prev;
	void				*start_user_space;
	size_t				size_allocated;
}				t_large_heap;

typedef struct heap // 16 bytes
{
	struct block		*start_block;
	size_t				size;
}				t_heap;

typedef struct block // 48 bytes
{
	struct block		*next;
	struct block		*prev;
	struct user_space	*used_user_space;
	struct heap			*parent_heap;
	size_t				free_size;
	size_t				size_after;
	
}				t_block;

typedef struct user_space // 48 bytes
{
	struct user_space	*next;
	struct user_space	*prev;
	struct block		*parent_block;
	void				*start_user_space;
	size_t				size_after;
	size_t				size_allocated;
}				t_user_space;


// general functions
void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

// init functions
void	initialize_data(t_data **data);
void	initialize_heap(t_heap **heap, size_t size);
void	initialize_large_heap(t_large_heap **new_large_heap, t_large_heap *large_heap_prev, size_t size);

// allocate functions
void	found_space_or_allocate(t_heap *heap, size_t size, int type);
void	allocate(t_heap *heap, size_t size, size_t type);
void	allocate_large(size_t size);
void	*align_address(void *ptr);

//  general utils functions
bool	search_free_space(t_heap *heap, size_t size);
void	find_used_user_space_ptr(t_user_space **user_space_tmp, t_large_heap **large_heap_tmp ,void *ptr, size_t *type);
// unlink functions
void	unlink_large_heap(t_large_heap *large_heap);
void	unlink_used_user_space(t_user_space *used_user_space);
void	unlink_block(t_block *block);

// link functions
void	link_used_user_space(t_user_space *user_space, t_user_space *user_space_prev);
void	link_large_heap(t_large_heap *new_large_heap, t_large_heap *large_heap_prev);

// realloc utils functions
void	find_old_area_copy_and_free(void *ptr, size_t size);

// free utils functions
// delete functions
void	check_if_block_is_unused(t_heap **heap, t_block **parent_block_used_user_space);
void	delete_large_heap(t_large_heap *large_heap);
// add functions
void	defragment(t_user_space *used_user_space);

// free functions
void	free_all(void);
#endif