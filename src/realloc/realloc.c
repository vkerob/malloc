#include "../../include/mem.h"
#include <unistd.h>




void	find_new_area_or_allocate(t_heap *heap, size_t size, size_t type)
{
	bool			space_found = false;

	space_found = find_free_space(heap, size);
	if (space_found == false)
		allocate(&heap, size, type);
}

t_user_space	*find_in_heap(t_heap *heap, void *ptr)
{
	t_mem_block		*block_tmp;
	t_user_space	*user_space_tmp;

	if (heap == NULL)
		return (NULL);
	block_tmp = heap->start_block;
	while (block_tmp)
	{
		user_space_tmp = block_tmp->user_space;
		while (user_space_tmp)
		{
			if (user_space_tmp->start_user_space == ptr)
				return (user_space_tmp);
			user_space_tmp = user_space_tmp->next;
		}
		block_tmp = block_tmp->next;
	}
	return (NULL);

}

t_heap_large	*find_in_heap_large(void *ptr)
{
	t_heap_large	*heap_large_tmp;
	
	heap_large_tmp = data->large;
	while (heap_large_tmp)
	{
		if (heap_large_tmp->start_user_space == ptr)
			return (heap_large_tmp);
		heap_large_tmp = heap_large_tmp->next;
	}
	return (NULL);
}

void	find_ptr(t_user_space **user_space_tmp, t_heap_large **heap_large_tmp ,void *ptr)
{

	*user_space_tmp = find_in_heap(data->tiny, ptr);
	if (*user_space_tmp)
		return ;
	*user_space_tmp = find_in_heap(data->small, ptr);
	if (*user_space_tmp)
		return ;
	*heap_large_tmp = find_in_heap_large(ptr);
	if (*heap_large_tmp)
		return ;
}

void	copy_and_free(t_user_space *user_space_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < user_space_tmp->size_allocated && i < size)
	{
		((char *)data->return_user_space)[i] = ((char *)ptr)[i];
		i++;
	}
	if (user_space_tmp->prev != NULL)
		user_space_tmp->prev->next = user_space_tmp->next;
	if (user_space_tmp->next != NULL)
		user_space_tmp->next->prev = user_space_tmp->prev;
	munmap(user_space_tmp->start_user_space, user_space_tmp->size_allocated);
}

void	copy_and_free_large(t_heap_large *heap_large_tmp, void *ptr, size_t size)
{
	size_t	i = 0;

	while (i < heap_large_tmp->size_allocated && i < size)
	{
		((char *)data->return_user_space)[i] = ((char *)ptr)[i];
		i++;
	}
	if (heap_large_tmp->prev != NULL)
		heap_large_tmp->prev->next = heap_large_tmp->next;
	if (heap_large_tmp->next != NULL)
		heap_large_tmp->next->prev = heap_large_tmp->prev;
	munmap(heap_large_tmp->start_user_space, heap_large_tmp->size_allocated);
}



void	find_old_are_copy_and_free(void *ptr, size_t size)
{
	t_user_space	*user_space_tmp;
	t_heap_large	*heap_large_tmp;

	find_ptr(&user_space_tmp, &heap_large_tmp, ptr);
	if (user_space_tmp)
		copy_and_free(user_space_tmp, ptr, size);
	else
		copy_and_free_large(heap_large_tmp, ptr, size);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		page_size = getpagesize();

	if (size <= page_size * TINY)
	{
		find_new_area_or_allocate(data->tiny, size, TINY);			// find the area or allocate a new one
		find_old_are_copy_and_free(ptr, size);
	}
	else if (size <= page_size * SMALL)
	{
		find_new_area_or_allocate(data->small, size, SMALL);
		find_old_are_copy_and_free(ptr, size);
	}
	else
	{
		allocate_large(size);
		find_old_are_copy_and_free(ptr, size);
	}
	if (data->error)
		return (NULL);
	return (data->return_user_space);
}