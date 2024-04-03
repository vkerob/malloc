#include "../include/mem.h"

bool	find_free_space(t_heap *heap, size_t size)
{
	t_mem_block		*block;
	t_free_space	*free_area;
	t_user_space	*user_space;
	t_user_space	*user_space_prev = NULL;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		free_area = block->free_area;
		while (free_area)
		{
			if (free_area->free_size >= size)
			{
				if (free_area->free_size - size == 0)
				{
					free_area->prev->next = free_area->next;
					free_area->next->prev = free_area->prev;
					munmap(free_area, sizeof(t_free_space));
				}
				else
				{
					user_space = block->user_space;
					while (user_space)
					{
						if (user_space->next == NULL)
							user_space_prev = user_space;
						user_space = user_space->next;
					}
					user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
					user_space->start_user_space = free_area->start_free_space;
					user_space->size_allocated = size;
					free_area->start_free_space += size;
					free_area->free_size -= size;
					user_space->next = NULL;
					user_space->prev = user_space_prev;
					data->return_user_space = free_area->start_free_space;
				}
				return (true);
			}
			free_area = free_area->next;
		}
		block = block->next;
	}
	return (false);
}

static t_user_space	*find_in_heap(t_heap *heap, void *ptr)
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

static t_heap_large	*find_in_heap_large(void *ptr)
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

void	find_ptr(t_user_space **user_space_tmp, t_heap_large **heap_large_tmp ,void *ptr, size_t *type)
{

	*user_space_tmp = find_in_heap(data->tiny, ptr);
	if (*user_space_tmp)
	{
		*type = TINY;
		return ;
	}
	*user_space_tmp = find_in_heap(data->small, ptr);
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