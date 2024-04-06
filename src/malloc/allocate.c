#include "../../include/mem.h"

// allocates the heap passed as argument if it doesn't exist, a new block on him and allocates a new user space on the block of the size passed as argument 

void	allocate_or_found_space_not_found(t_heap **heap, size_t size, int type)
{
	bool is_space_found = search_free_space(*heap, size);
	if (is_space_found == false && data->error == false)
		allocate(heap, size, type);
}

void	allocate(t_heap **heap, size_t size, size_t type)
{
	t_block		*block_tmp;
	t_block		*block_prev = NULL;

	write(1, "allocate\n", 9);
	if (*heap == NULL)
		initialize_heap(heap, type);
	initialize_block(*heap, &block_tmp, size, block_prev, type);			// send block address for initialization of user space parent block
}

void	allocate_large(size_t size)
{
	t_heap_large	*new_heap_large;
	t_heap_large	*heap_large_prev;

	new_heap_large = data->large_heap;
	// find the last large heap
	if (new_heap_large != NULL)
	{
		while (new_heap_large->next)
			new_heap_large = new_heap_large->next;
		heap_large_prev = new_heap_large;
		new_heap_large = new_heap_large->next;
	}
	// allocate the new large heap
	new_heap_large = mmap(NULL, sizeof(t_heap_large) + getpagesize() * LARGE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new_heap_large == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	// initialize the new large heap
	new_heap_large->start_user_space = new_heap_large + sizeof(t_heap_large);
	new_heap_large->size_allocated = size;
	new_heap_large->next = NULL;
	new_heap_large->prev = heap_large_prev;
	if (heap_large_prev != NULL)
		heap_large_prev->next = new_heap_large;
}