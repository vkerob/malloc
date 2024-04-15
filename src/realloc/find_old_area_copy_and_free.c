#include "../../include/mem.h"

void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type)
{
	bool	space_found = false;

	space_found = search_free_space(heap, size);
	if (space_found == false)
		allocate(&heap, size, type);
}

//-------------------------------find_old_area_copy_and_free--------------------------------//

static void	copy_and_free(t_user_space *user_space_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < user_space_tmp->size_allocated && i < size)
	{
		((char *)data->user_space_pointer)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
}

static void	copy_and_free_large(t_large_heap *large_heap_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < large_heap_tmp->size_allocated && i < size)
	{
		((char *)data->user_space_pointer)[i] = ((char *)ptr)[i];
		i++;
	}
	if (large_heap_tmp->prev != NULL)
		large_heap_tmp->prev->next = large_heap_tmp->next;
	if (large_heap_tmp->next != NULL)
		large_heap_tmp->next->prev = large_heap_tmp->prev;
	munmap(large_heap_tmp->start_user_space, large_heap_tmp->size_allocated);
}

void	find_old_area_copy_and_free(void *ptr, size_t size)
{
	t_user_space	*user_space_tmp;
	t_large_heap	*large_heap_tmp;
	size_t			type;

	find_ptr(&user_space_tmp, &large_heap_tmp, ptr, &type);
	if (user_space_tmp)
		copy_and_free(user_space_tmp, ptr, size);
	else
		copy_and_free_large(large_heap_tmp, ptr, size);
	(void)type;
}

//------------------------------------------------------------------------------------------//