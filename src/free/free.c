#include "../../include/mem.h"

void	free(void *ptr)
{
	t_chunk	*chunk;
	t_large_heap	*used_large_heap;
	t_heap			**heap_tmp;
	size_t			type = 0;

	pthread_mutex_lock(&lock);

	if (ptr == NULL)
	{
		pthread_mutex_unlock(&lock);
		return ;
	}

	data->chunk_start = NULL;
	find_chunk_ptr(&chunk, &used_large_heap, ptr, &type);

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
		delete_large_heap(used_large_heap);
	}
	else
	{
		ft_printf("Error: impossible to free this pointer\n");
		pthread_mutex_unlock(&lock);
		return ;
	}

	pthread_mutex_unlock(&lock);
}
