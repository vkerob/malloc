#include "../../include/mem.h"

void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type)
{
	bool			space_found = false;

	space_found = search_free_space(heap, size);
	if (space_found == false)
		allocate(&heap, size, type);
}

void	copy_and_free(t_user_space *user_space_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < user_space_tmp->size_allocated && i < size)
	{
		((char *)data->user_space_pointer)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
}

void	copy_and_free_large(t_heap_large *heap_large_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < heap_large_tmp->size_allocated && i < size)
	{
		((char *)data->user_space_pointer)[i] = ((char *)ptr)[i];
		i++;
	}
	if (heap_large_tmp->prev != NULL)
		heap_large_tmp->prev->next = heap_large_tmp->next;
	if (heap_large_tmp->next != NULL)
		heap_large_tmp->next->prev = heap_large_tmp->prev;
	munmap(heap_large_tmp->start_user_space, heap_large_tmp->size_allocated);
}

void	find_old_area_copy_and_free(void *ptr, size_t size)
{
	t_user_space	*user_space_tmp;
	t_heap_large	*heap_large_tmp;
	size_t			type;

	find_ptr(&user_space_tmp, &heap_large_tmp, ptr, &type);
	if (user_space_tmp)
		copy_and_free(user_space_tmp, ptr, size);
	else
		copy_and_free_large(heap_large_tmp, ptr, size);
	(void)type;
}