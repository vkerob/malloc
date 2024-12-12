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

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

#define TINY_SIZE 				(size_t)(PAGE_SIZE * 4)		// 16384 bytes
#define SMALL_SIZE 				(size_t)(PAGE_SIZE * 128)	// 524288 bytes
#define LARGE 					1

#define MEN_ALLIGN 				16
#define ALLIGN_DATA 			(size_t)align_address((void *)sizeof(t_data))
#define ALIGN_BLOCK 			(size_t)align_address((void *)sizeof(t_block))
#define ALIGN_CHUNK 			(size_t)align_address((void *)sizeof(t_chunk))
#define ALIGN_HEAP 				(size_t)align_address((void *)sizeof(t_heap))
#define ALIGN_LARGE_HEAP 		(size_t)align_address((void *)sizeof(t_large_heap))
// This implementation initializes a struct (data) at the beginning of 64 bytes. For example:
// Minimum allocation: 64 bytes (data) + 16 bytes * 2 (heap) = 96 bytes + type_size (TINY_SIZE, SMALL_SIZE, LARGE)

// Here we determine the maximum size of an allocation in each type of heap.
// We want to have a minimum of 100 allocations in each block (trying to reproduce the behavior of the real malloc and respecting the 42 subject).
// How we calculate the maximum size of an allocation in each heap:
// For Tiny heap: (16384 - 48 (block)) / 100 = 163 bytes - 48 (chunk) = 115 - 16 bytes (alignment) = 99 bytes + 13 bytes (alignment) = 112 bytes
// As a precaution, we subtract 16 bytes from the result to ensure that we can allocate 100 allocations because, for example,
// if we allocate 100 allocations of 115 bytes + 48 bytes (chunk) = 163 bytes, we are going to align the address to 176 bytes and
// we will not be able to allocate 100 allocations because 100 * 176 = 17600 > 16384.
// So if a user tries to allocate 112 bytes, we will be sure that we can allocate 100 allocations of the same size because in the worst case we will have 100 * (112 + 48) = 16000 < 16384.
// 48 bytes are the size of the chunk metadata for each allocation.
// The same logic applies for the Small heap: (524288 - 48) / 100 = 5242 bytes - 48 (chunk) = 5194 - 16 bytes (alignment) = 5178 bytes + 6 bytes (alignment) = 5184 bytes
// To sum up:
// TINY_MAX_SIZE_ALLOC <= 112 bytes
// SMALL_MAX_SIZE_ALLOC > 112 and <= 5184 bytes
// LARGE_MAX_SIZE_ALLOC > 5184 bytes
#define TINY_MAX_SIZE_ALLOC		(size_t)align_address((void *)(size_t)((TINY_SIZE - ALIGN_BLOCK) / 100) - ALIGN_CHUNK - MEN_ALLIGN)		// (16384 - 48) / 100 = 163 bytes - 16 bytes (align) - 48 (chunk) = 99 bytes + 13 bytes (align) = 112 bytes
#define SMALL_MAX_SIZE_ALLOC	(size_t)align_address((void *)(size_t)((SMALL_SIZE - ALIGN_BLOCK) / 100) - ALIGN_CHUNK - MEN_ALLIGN)	// (524288 - 48) / 100 = 5242 bytes - 16 bytes (align) - 48 (chunk) = 5178 bytes + 6 bytes (align) = 5184 bytes



extern pthread_mutex_t lock;


typedef struct	data // 56 bytes
{
	struct heap			*tiny_heap;
	struct heap			*small_heap;
	struct large_heap	*large_heap;
	struct rlimit		rlimit;
	void				*chunk_start;
	bool				error;
	//char				padding[7];
}				t_data;

extern t_data *data;

typedef struct large_heap // 32 bytes
{
	struct large_heap	*next;
	struct large_heap	*prev;
	void				*start;
	size_t				size_allocated;
}				t_large_heap;

typedef struct heap // 16 bytes
{
	struct block		*start;
	size_t				size;
}				t_heap;

typedef struct block // 48 bytes
{
	struct block	*next;
	struct block	*prev;
	struct chunk	*chunk;
	struct heap		*parent_heap;
	size_t			free_size;
	size_t			size_after;
}				t_block;

typedef struct chunk // 48 bytes
{
	struct chunk	*next;
	struct chunk	*prev;
	struct block	*parent_block;
	void			*start;
	size_t			size_after;
	size_t			size_allocated;
}				t_chunk;


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
bool	set_after_chunk(t_block *block, size_t size);
bool	set_after_block(t_block *block, size_t size);
void	find_chunk_ptr(t_chunk **chunk_tmp, t_large_heap **large_heap_tmp ,void *ptr, size_t *type);
// unlink functions
void	unlink_large_heap(t_large_heap *large_heap);
void	unlink_chunk(t_chunk *chunk);
void	unlink_block(t_block *block);

// link functions
void	link_chunk(t_chunk *chunk, t_chunk *chunk_prev);
void	link_large_heap(t_large_heap *new_large_heap, t_large_heap *large_heap_prev);

// realloc utils functions
void	find_old_area_copy_and_free(void *ptr, size_t size);

// free utils functions
// delete functions
void	check_if_block_is_unused(t_heap **heap, t_block **parent_block_chunk);
// add functions
void	defragment(t_chunk *chunk);

// free functions
void	free_all(void);
#endif