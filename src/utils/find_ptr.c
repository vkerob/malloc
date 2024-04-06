#include "../../include/mem.h"

// try to find the user_space in the heap tiny or small
static t_user_space	*find_in_heap(t_heap *heap, void *ptr)
{
	t_block		*block_tmp;
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

// try to find the user_space in the heap large
static t_heap_large	*find_in_heap_large(void *ptr)
{
	t_heap_large	*heap_large_tmp;
	
	heap_large_tmp = data->large_heap;
	while (heap_large_tmp)
	{
		if (heap_large_tmp->start_user_space == ptr)
			return (heap_large_tmp);
		heap_large_tmp = heap_large_tmp->next;
	}
	return (NULL);
}

// find the user_space in the heap tiny, small or large
void	find_ptr(t_user_space **user_space_tmp, t_heap_large **heap_large_tmp ,void *ptr, size_t *type)
{

	*user_space_tmp = find_in_heap(data->tiny_heap, ptr);
	if (*user_space_tmp)
	{
		*type = TINY;
		return ;
	}
	*user_space_tmp = find_in_heap(data->small_heap, ptr);
	if (*user_space_tmp)
	{
		*type = SMALL;
		return ;
	}
	*heap_large_tmp = find_in_heap_large(ptr);
	if (*heap_large_tmp)
	{
		*type = LARGE;
		return ;
	}
}