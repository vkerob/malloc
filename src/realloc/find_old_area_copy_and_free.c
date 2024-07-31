#include "../../include/mem.h"

static void	copy_and_free(t_chunk *chunk_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < chunk_tmp->size_allocated && i < size)
	{
		((char *)data->chunk_start)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
}

static void	copy_and_free_large(t_large_heap *large_heap_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < large_heap_tmp->size_allocated && i < size)
	{
		((char *)data->chunk_start)[i] = ((char *)ptr)[i];
		i++;
	}
	if (large_heap_tmp->prev != NULL)
		large_heap_tmp->prev->next = large_heap_tmp->next;
	if (large_heap_tmp->next != NULL)
		large_heap_tmp->next->prev = large_heap_tmp->prev;
	munmap(large_heap_tmp->start, large_heap_tmp->size_allocated);
}

void	find_old_area_copy_and_free(void *ptr, size_t size)
{
	t_chunk			*chunk_tmp;
	t_large_heap	*large_heap_tmp;
	size_t			type;

	find_chunk_ptr(&chunk_tmp, &large_heap_tmp, ptr, &type);
	if (chunk_tmp)
		copy_and_free(chunk_tmp, ptr, size);
	else
		copy_and_free_large(large_heap_tmp, ptr, size);
	(void)type;
}
