#include "../../include/mem.h"

// allocates the heap passed as argument if it doesn't exist, a new block on him and allocates a new used user space on the block of the size passed as argument 
void	found_space_or_allocate(t_heap *heap, size_t size, int type_size)
{
	bool	is_space_found;

	is_space_found = search_free_space(heap, size);
	if (is_space_found == false)
		allocate(heap, size, type_size);
}


void	allocate_large(size_t size)
{
	t_large_heap	*new_large_heap;
	t_large_heap	*large_heap_prev = NULL;

	new_large_heap = data->large_heap;

	// find the last large heap
	if (new_large_heap != NULL)
	{
		while (new_large_heap->next)
			new_large_heap = new_large_heap->next;
		large_heap_prev = new_large_heap;
		new_large_heap = new_large_heap->next;
	}

	// allocate and initialize the new large heap
	initialize_large_heap(&new_large_heap, large_heap_prev, size);
	if (data->error == true)
		return ;

	data->user_space_pointer = new_large_heap->start_user_space;
}
