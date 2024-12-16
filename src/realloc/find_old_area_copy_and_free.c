#include "../../includes/malloc.h"

static void	copy_and_free(t_chunk *chunk_tmp, void *ptr, size_t size)
{
	// copy the data from the old area to the new area
	size_t	i = 0;

	while (i < chunk_tmp->size_allocated && i < size)
	{
		((char *)data->chunk_start)[i] = ((char *)ptr)[i];
		i++;
	}
	void *tmp_chunk_start = data->chunk_start;
	free(ptr);
	data->chunk_start = tmp_chunk_start;
}

static void	copy_and_free_large(t_large_heap *large_heap_tmp, void *ptr, size_t size)
{
	// copy the data from the old area to the new area
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
	// find the chunk in the heap tiny, small or large
	// copy the data from the old area to the new area
	// free the old area

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
