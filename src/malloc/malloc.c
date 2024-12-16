#include "../../includes/malloc.h"

t_data	*data = NULL;


void	*malloc(size_t size)
{
	t_heap	*heap_tmp;
	int		type_size;

	// this function allocates a block of memory, for more details of how many bytes are allocated check the mem.h
	// if the size is 0, return NULL else return the pointer to the start of the allocated memory for the user

	initialize_mutex();
	pthread_mutex_lock(&lock);

	if (size == 0)
	{
		pthread_mutex_unlock(&lock);
		return (NULL);
	}

	if (data == NULL)
	{
		initialize_data(&data);
		if (data->error == true)
		{
			free_all();
			return (NULL);
		}
	}

	data->chunk_start = NULL;

	if (size <= TINY_MAX_SIZE_ALLOC || size <= SMALL_MAX_SIZE_ALLOC)
	{
		heap_tmp = (size <= TINY_MAX_SIZE_ALLOC) ? data->tiny_heap : data->small_heap;
		type_size = (size <= TINY_MAX_SIZE_ALLOC) ? TINY_SIZE : SMALL_SIZE;
		found_space_or_allocate(heap_tmp, size, type_size);
	}
	else
		allocate_large(size);

	if (data->error == false)
	{
		pthread_mutex_unlock(&lock);
		return (data->chunk_start);
	}
	
	// if error
	free_all();
	pthread_mutex_unlock(&lock);
	return (NULL);
}
