#include "../../includes/malloc.h"

void	free(void *ptr)
{
	// try to find the chunk in the heap tiny, small or large
	// if the pointer is NULL, return
	// if the pointer is found, defragment the chunk, unlink the chunk, 
	// check if the block is unused and free the block only if it's not the last block

	t_chunk			*chunk;
	t_large_heap	*used_large_heap;
	t_heap			**heap_tmp;
	size_t			type = 0;

	initialize_mutex();
	pthread_mutex_lock(&lock);

	if (ptr == NULL)
	{
		pthread_mutex_unlock(&lock);
		return ;
	}

	data->chunk_start = NULL;
	find_chunk_ptr(&chunk, &used_large_heap, ptr, &type);

	// try to find the chunk in the heap tiny, small or large
	if (type == TINY_SIZE || type == SMALL_SIZE)
	{
		heap_tmp = (type == TINY_SIZE) ? &(data->tiny_heap) : &(data->small_heap);
		defragment(chunk);
		unlink_chunk(chunk);
		check_if_block_is_unused(heap_tmp, (&chunk->parent_block));
	}
	else if (type == LARGE)
	{
		unlink_large_heap(used_large_heap);
		munmap(used_large_heap, used_large_heap->size_allocated + ALIGN_LARGE_HEAP);
	}
	// if type is equal to 0, the pointer is not found so it's an error
	else
	{
		ft_printf("Error: impossible to free this pointer\n");
		pthread_mutex_unlock(&lock);
		return ;
	}

	pthread_mutex_unlock(&lock);
}
