#include "../../include/mem.h"

t_data	*data = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	t_heap	*heap_tmp;
	int		type_size;

	pthread_mutex_lock(&lock);
	if (data == NULL)
	{
		initialize_data(&data);
		if (data->error == true)
		{
			free_all();
			return (NULL);
		}
	}
	data->user_space_pointer = NULL;
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
		return (data->user_space_pointer);
	}
	
	// if error
	free_all();
	return (NULL);
}
