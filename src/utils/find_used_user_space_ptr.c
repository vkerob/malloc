#include "../../include/mem.h"

// try to find the used_user_space in the heap tiny or small
static t_user_space	*find_in_heap(t_heap *heap, void *ptr)
{
	t_block		*block_tmp;
	t_user_space	*user_space_tmp;

	if (heap == NULL)
		return (NULL);
	block_tmp = heap->start_block;
	while (block_tmp)
	{
		user_space_tmp = block_tmp->used_user_space;
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

// try to find the used_user_space in the heap large
static t_large_heap	*find_in_large_heap(void *ptr)
{
	t_large_heap	*large_heap_tmp;
	
	large_heap_tmp = data->large_heap;
	while (large_heap_tmp)
	{
		if (large_heap_tmp->start_user_space == ptr)
			return (large_heap_tmp);
		large_heap_tmp = large_heap_tmp->next;
	}
	return (NULL);
}

// find the used_user_space in the heap tiny, small or large
void	find_used_user_space_ptr(t_user_space **user_space_tmp, t_large_heap **large_heap_tmp ,void *ptr, size_t *type)
{

	*user_space_tmp = find_in_heap(data->tiny_heap, ptr);
	if (*user_space_tmp)
	{
		*type = TINY_SIZE;
		return ;
	}
	*user_space_tmp = find_in_heap(data->small_heap, ptr);
	if (*user_space_tmp)
	{
		*type = SMALL_SIZE;
		return ;
	}
	*large_heap_tmp = find_in_large_heap(ptr);
	if (*large_heap_tmp)
	{
		*type = LARGE;
		return ;
	}
	else
		*type = 0;
}