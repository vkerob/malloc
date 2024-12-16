#include "../../includes/malloc.h"

void	*realloc(void *ptr, size_t size)
{
	// realloc the memory area pointed to by ptr to size bytes
	// if ptr is NULL, the call is equivalent to malloc(size)
	t_heap	*heap_tmp;
	int		type;

	initialize_mutex();
	pthread_mutex_lock(&lock);

	if (size == 0)
	{
		pthread_mutex_unlock(&lock);
		return (NULL);
	}

	data->chunk_start = NULL;

	if (size <= TINY_MAX_SIZE_ALLOC || size <= SMALL_MAX_SIZE_ALLOC)
	{
		heap_tmp = (size <= TINY_MAX_SIZE_ALLOC) ? data->tiny_heap : data->small_heap;
		type = (size <= TINY_MAX_SIZE_ALLOC) ? TINY_MAX_SIZE_ALLOC : SMALL_MAX_SIZE_ALLOC;

		// find the area or allocate a new one
		found_space_or_allocate(heap_tmp, size, type);

		if (data->error == false)
			// copy the old data to the new area and free the old area
			find_old_area_copy_and_free(ptr, size);
	}
	else
	{
		allocate_large(size);
		if (data->error == false)
			find_old_area_copy_and_free(ptr, size);
	}

	if (data->error == false)
	{
		pthread_mutex_unlock(&lock);
		return (data->chunk_start);
	}

	// error detected, free all allocated memory
	free_all();
	pthread_mutex_unlock(&lock);
	return (NULL);
}
